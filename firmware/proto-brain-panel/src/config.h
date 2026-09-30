#pragma once

#include <Arduino.h>

// Pin map
static const uint8_t PIN_EDGE_PRE_EN_DRV = 9;
static const uint8_t PIN_P_RXD = 8;
static const uint8_t PIN_P_TXD = 7;

static const uint8_t PIN_SLOT_B_DATA_DRV = 6;
static const uint8_t PIN_SLOT_A_DATA_DRV = 5;

static const uint8_t PIN_EDGE_EN_DRV   = 4;
static const uint8_t PIN_SLOT_B_EN_DRV = 3;
static const uint8_t PIN_SLOT_A_EN_DRV = 2;

static const uint8_t PIN_SLOT_A_ID     = A0;
static const uint8_t PIN_SLOT_B_ID     = A1;
static const uint8_t PIN_EDGE_R_SENSE  = A2;
static const uint8_t PIN_EDGE_R_HALL   = A3;

// ADC / voltage conversion (Nano: 10-bit ADC, 5V ref)
static const uint16_t ADC_MAX_COUNTS = 1023;
static const float ADC_REF_V = 5.0f;

// Slot ID behavior
static const uint16_t SLOT_ID_SAMPLE_MS      = 50;
static const uint16_t SLOT_ID_STABLE_MS      = 200;
static const uint16_t SLOT_SHORT_LOCKOUT_MS  = 2000;

static const uint16_t SLOT_EMPTY_MIN_COUNTS  = 922; // >4.5V
static const uint16_t SLOT_SHORT_MAX_COUNTS  = 41;  // <0.2V
static const uint16_t SLOT_LED_MIN_COUNTS    = 72;  // 0.35V
static const uint16_t SLOT_LED_MAX_COUNTS    = 113; // 0.55V

// WS2812 settings
static const uint16_t SLOT_LED_COUNT    = 10;
static const uint8_t SLOT_BRIGHTNESS    = 80;
static const uint16_t ANIM_INTERVAL_MS  = 30;

// Edge behavior
// Edge Hall "nothing attached" value is calibrated once and stored in EEPROM
// (send 'c' on Serial at 115200 with NOTHING attached to the edge).
static const uint16_t CAL_MAGIC = 0xCA1B;
static const uint16_t EDGE_HALL_THRESHOLD_COUNTS = 35;
static const uint16_t EDGE_HALL_HOLD_MS          = 200;
static const uint16_t EDGE_PRETEST_MS            = 20;   // with RPRE = 470 ohm
static const uint16_t EDGE_RETRY_MS              = 2000; // after a short
static const uint16_t EDGE_OPEN_IGNORE_MS        = 1000; // after "nothing connected"

// A2 divider: RSEN1=100k, RSEN2=22k
static const float EDGE_SENSE_DIVIDER_RATIO = (100.0f + 22.0f) / 22.0f;
// Pre-test window (voltage on EDGE_R_20V after EDGE_PRETEST_MS):
//   < 0.5 V        short circuit          -> reject, retry after EDGE_RETRY_MS
//   1.5 .. 15 V    neighbour caps charging -> accept, close main switch
//   > 18 V         nothing connected       -> reject, ignore triggers EDGE_OPEN_IGNORE_MS
static const float EDGE_SHORT_MAX_V         = 0.5f;
static const float EDGE_NEIGH_MIN_V         = 1.5f;
static const float EDGE_NEIGH_MAX_V         = 15.0f;
static const float EDGE_OPEN_MIN_V          = 18.0f;
