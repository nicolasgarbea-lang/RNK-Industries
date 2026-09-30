#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include "config.h"

enum SlotState : uint8_t {
  SLOT_OFF = 0,
  SLOT_ON,
  SLOT_LOCKOUT
};

enum EdgeState : uint8_t {
  EDGE_WAIT_TRIGGER = 0,
  EDGE_PRETEST,
  EDGE_MAIN_ON,
  EDGE_RETRY
};

struct SlotChannel {
  uint8_t enPin;
  uint8_t dataPin;
  uint8_t idPin;
  Adafruit_NeoPixel* strip;

  SlotState state;
  unsigned long lastSampleMs;
  unsigned long stableSinceMs;
  unsigned long lockoutStartMs;
};

struct EdgeControl {
  EdgeState state;
  int baseline;
  unsigned long triggerSinceMs;
  unsigned long pretestStartMs;
  unsigned long retryStartMs;
  unsigned long retryDurationMs;
};

Adafruit_NeoPixel stripA(SLOT_LED_COUNT, PIN_SLOT_A_DATA_DRV, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB(SLOT_LED_COUNT, PIN_SLOT_B_DATA_DRV, NEO_GRB + NEO_KHZ800);

SlotChannel slotA{PIN_SLOT_A_EN_DRV, PIN_SLOT_A_DATA_DRV, PIN_SLOT_A_ID, &stripA, SLOT_OFF, 0, 0, 0};
SlotChannel slotB{PIN_SLOT_B_EN_DRV, PIN_SLOT_B_DATA_DRV, PIN_SLOT_B_ID, &stripB, SLOT_OFF, 0, 0, 0};

EdgeControl edge{EDGE_WAIT_TRIGGER, 0, 0, 0, 0, 0};

struct Calibration {
  uint16_t magic;
  int16_t edgeHallEmpty;
};

unsigned long lastAnimMs = 0;
uint8_t rainbowBase = 0;

static int readBaseline(uint8_t pin, uint8_t samples = 16) {
  uint32_t acc = 0;
  for (uint8_t i = 0; i < samples; i++) {
    acc += analogRead(pin);
    delay(2);
  }
  return static_cast<int>(acc / samples);
}

static float adcToVolts(uint16_t counts) {
  return (static_cast<float>(counts) * ADC_REF_V) / static_cast<float>(ADC_MAX_COUNTS);
}

static bool isSlotEmpty(uint16_t counts) {
  return counts >= SLOT_EMPTY_MIN_COUNTS;
}

static bool isSlotShort(uint16_t counts) {
  return counts <= SLOT_SHORT_MAX_COUNTS;
}

static bool isLedModuleId(uint16_t counts) {
  return (counts >= SLOT_LED_MIN_COUNTS) && (counts <= SLOT_LED_MAX_COUNTS);
}

static void slotDataInput(SlotChannel &slot) {
  pinMode(slot.dataPin, INPUT); // no pull-up
}

static void slotDataOutput(SlotChannel &slot) {
  pinMode(slot.dataPin, OUTPUT);
  digitalWrite(slot.dataPin, LOW);
}

static uint16_t readSlotIdCounts(SlotChannel &slot) {
  slotDataInput(slot);
  return static_cast<uint16_t>(analogRead(slot.idPin));
}

static uint32_t wheel(Adafruit_NeoPixel &strip, uint8_t pos) {
  pos = 255 - pos;
  if (pos < 85) {
    return strip.Color(255 - pos * 3, 0, pos * 3);
  }
  if (pos < 170) {
    pos -= 85;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
  pos -= 170;
  return strip.Color(pos * 3, 255 - pos * 3, 0);
}

static void showRainbow(Adafruit_NeoPixel &strip, uint8_t base) {
  for (uint16_t i = 0; i < SLOT_LED_COUNT; i++) {
    uint8_t hue = base + static_cast<uint8_t>((i * 256UL) / SLOT_LED_COUNT);
    strip.setPixelColor(i, wheel(strip, hue));
  }
  strip.show();
}

static void processSlotOffOrLockout(SlotChannel &slot, unsigned long nowMs) {
  digitalWrite(slot.enPin, LOW);

  if (slot.state == SLOT_LOCKOUT) {
    if ((nowMs - slot.lockoutStartMs) < SLOT_SHORT_LOCKOUT_MS) {
      return;
    }
    slot.state = SLOT_OFF;
    slot.stableSinceMs = 0;
    slot.lastSampleMs = 0;
  }

  if ((nowMs - slot.lastSampleMs) < SLOT_ID_SAMPLE_MS) {
    return;
  }
  slot.lastSampleMs = nowMs;

  uint16_t idCounts = readSlotIdCounts(slot);

  if (isSlotShort(idCounts)) {
    slot.state = SLOT_LOCKOUT;
    slot.lockoutStartMs = nowMs;
    slot.stableSinceMs = 0;
    return;
  }

  if (isLedModuleId(idCounts)) {
    if (slot.stableSinceMs == 0) {
      slot.stableSinceMs = nowMs;
    } else if ((nowMs - slot.stableSinceMs) >= SLOT_ID_STABLE_MS) {
      digitalWrite(slot.enPin, HIGH);
      slotDataOutput(slot);
      slot.state = SLOT_ON;
      slot.stableSinceMs = 0;
    }
  } else {
    slot.stableSinceMs = 0;
  }
}

static void processSlotOn(SlotChannel &slot, unsigned long nowMs, bool animTick, uint8_t base) {
  if (!animTick) {
    return;
  }

  uint16_t idCounts = readSlotIdCounts(slot); // between frames

  if (isSlotEmpty(idCounts) || isSlotShort(idCounts)) {
    digitalWrite(slot.enPin, LOW);
    if (isSlotShort(idCounts)) {
      slot.state = SLOT_LOCKOUT;
      slot.lockoutStartMs = nowMs;
    } else {
      slot.state = SLOT_OFF;
    }
    slot.stableSinceMs = 0;
    return; // do not clear LEDs
  }

  slotDataOutput(slot);
  showRainbow(*slot.strip, base);
}

static void edgeAllOff();

static void calibrateEdgeHall() {
  // Must be called with NOTHING attached to the edge.
  edgeAllOff();
  edge.state = EDGE_WAIT_TRIGGER;
  edge.triggerSinceMs = 0;
  Calibration cal{CAL_MAGIC, static_cast<int16_t>(readBaseline(PIN_EDGE_R_HALL))};
  EEPROM.put(0, cal);
  edge.baseline = cal.edgeHallEmpty;
  Serial.print(F("Edge Hall calibrated, empty value = "));
  Serial.println(edge.baseline);
}

static void loadEdgeCalibration() {
  Calibration cal;
  EEPROM.get(0, cal);
  if (cal.magic == CAL_MAGIC) {
    edge.baseline = cal.edgeHallEmpty;
    Serial.print(F("Edge Hall calibration loaded, empty value = "));
    Serial.println(edge.baseline);
  } else {
    // Fallback: boot value. Wrong if a neighbour is attached at boot.
    edge.baseline = readBaseline(PIN_EDGE_R_HALL);
    Serial.println(F("WARNING: edge Hall not calibrated. Remove any neighbour and send 'c'."));
  }
}

static void edgeAllOff() {
  digitalWrite(PIN_EDGE_PRE_EN_DRV, LOW);
  digitalWrite(PIN_EDGE_EN_DRV, LOW);
}

static void processEdge(unsigned long nowMs) {
  const int hallNow = analogRead(PIN_EDGE_R_HALL);
  int delta = hallNow - edge.baseline;
  if (delta < 0) delta = -delta;
  const bool hallOver = (delta > EDGE_HALL_THRESHOLD_COUNTS);

  switch (edge.state) {
    case EDGE_WAIT_TRIGGER:
      edgeAllOff();
      if (hallOver) {
        if (edge.triggerSinceMs == 0) {
          edge.triggerSinceMs = nowMs;
        } else if ((nowMs - edge.triggerSinceMs) >= EDGE_HALL_HOLD_MS) {
          digitalWrite(PIN_EDGE_PRE_EN_DRV, HIGH);
          edge.pretestStartMs = nowMs;
          edge.triggerSinceMs = 0;
          edge.state = EDGE_PRETEST;
        }
      } else {
        edge.triggerSinceMs = 0;
      }
      break;

    case EDGE_PRETEST:
      if ((nowMs - edge.pretestStartMs) >= EDGE_PRETEST_MS) {
        const uint16_t senseCounts = static_cast<uint16_t>(analogRead(PIN_EDGE_R_SENSE));
        const float senseV = adcToVolts(senseCounts) * EDGE_SENSE_DIVIDER_RATIO;

        if (senseV < EDGE_SHORT_MAX_V) {
          // Short circuit (tool across the pins)
          edgeAllOff();
          edge.retryStartMs = nowMs;
          edge.retryDurationMs = EDGE_RETRY_MS;
          edge.state = EDGE_RETRY;
        } else if (senseV >= EDGE_NEIGH_MIN_V && senseV <= EDGE_NEIGH_MAX_V) {
          // Neighbour input capacitors charging: a real panel
          digitalWrite(PIN_EDGE_EN_DRV, HIGH);
          digitalWrite(PIN_EDGE_PRE_EN_DRV, LOW);
          edge.state = EDGE_MAIN_ON;
        } else if (senseV > EDGE_OPEN_MIN_V) {
          // Nothing connected (or a neighbour already powered from another side)
          edgeAllOff();
          edge.retryStartMs = nowMs;
          edge.retryDurationMs = EDGE_OPEN_IGNORE_MS;
          edge.state = EDGE_RETRY;
        } else {
          // Ambiguous reading: stay safe
          edgeAllOff();
          edge.state = EDGE_WAIT_TRIGGER;
          edge.triggerSinceMs = 0;
        }
      }
      break;

    case EDGE_MAIN_ON:
      digitalWrite(PIN_EDGE_EN_DRV, HIGH);
      digitalWrite(PIN_EDGE_PRE_EN_DRV, LOW);
      if (!hallOver) {
        edgeAllOff();
        edge.state = EDGE_WAIT_TRIGGER;
        edge.triggerSinceMs = 0;
      }
      break;

    case EDGE_RETRY:
      edgeAllOff();
      if ((nowMs - edge.retryStartMs) >= edge.retryDurationMs) {
        edge.state = EDGE_WAIT_TRIGGER;
        edge.triggerSinceMs = 0;
      }
      break;
  }
}

void setup() {
  // Keep required outputs LOW at boot
  digitalWrite(PIN_SLOT_A_EN_DRV, LOW);
  digitalWrite(PIN_SLOT_B_EN_DRV, LOW);
  digitalWrite(PIN_EDGE_EN_DRV, LOW);
  digitalWrite(PIN_EDGE_PRE_EN_DRV, LOW);

  pinMode(PIN_SLOT_A_EN_DRV, OUTPUT);
  pinMode(PIN_SLOT_B_EN_DRV, OUTPUT);
  pinMode(PIN_EDGE_EN_DRV, OUTPUT);
  pinMode(PIN_EDGE_PRE_EN_DRV, OUTPUT);

  pinMode(PIN_SLOT_A_ID, INPUT);
  pinMode(PIN_SLOT_B_ID, INPUT);
  pinMode(PIN_EDGE_R_HALL, INPUT);
  pinMode(PIN_EDGE_R_SENSE, INPUT);

  stripA.begin();   // begin() sets the data pins as OUTPUT...
  stripB.begin();
  stripA.setBrightness(SLOT_BRIGHTNESS);
  stripB.setBrightness(SLOT_BRIGHTNESS);
  slotDataInput(slotA); // ...so switch them back to INPUT for ID detection
  slotDataInput(slotB);   // (no show() here: slots are unpowered)

  Serial.begin(115200);
  loadEdgeCalibration();
}

void loop() {
  if (Serial.available() > 0 && Serial.read() == 'c') {
    calibrateEdgeHall();
  }

  const unsigned long now = millis();
  const bool animTick = (now - lastAnimMs) >= ANIM_INTERVAL_MS;

  if (animTick) {
    lastAnimMs = now;
    rainbowBase++;
  }

  if (slotA.state == SLOT_ON) {
    processSlotOn(slotA, now, animTick, rainbowBase);
  } else {
    processSlotOffOrLockout(slotA, now);
  }

  if (slotB.state == SLOT_ON) {
    processSlotOn(slotB, now, animTick, rainbowBase);
  } else {
    processSlotOffOrLockout(slotB, now);
  }

  processEdge(now);
}
