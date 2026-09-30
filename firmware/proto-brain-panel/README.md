# Brain panel prototype firmware (panel MCU)

Target for the prototype: **Arduino Nano** (placeholder for the CH32V003). Schematic: [`../../electronics/tinkered/brain-panel-v0.2/`](../../electronics/tinkered/brain-panel-v0.2/).

## What it does

- **Slots**: reads the module ID resistor on pin 3 (DATA). Empty / short / LED module (10 k). Turns the slot on after 200 ms of stable ID, cuts it within one LED frame (30 ms) when the module is removed or shorted. 2 s lockout after a short.
- **Edge (right)**: Hall trigger, then current-limited pre-test (470 ohm, 20 ms). Accepts only a neighbour whose input capacitors are charging (1.5-15 V). Rejects a short (< 0.5 V) and an open edge (> 18 V).

## Calibration (required once per panel)

With **nothing attached to the edge**, open the serial monitor at 115200 and send `c`. The edge Hall "empty" value is stored in EEPROM.
Without calibration, a neighbour attached at power-up is not detected (the test suite checks this).

## Build

```
pio run
```

## Host tests (no hardware needed)

```
g++ -std=c++17 -Wall -Itest/mock -include test/mock/Arduino.h -o test/sim test/sim.cpp src/main.cpp
./test/sim cal        # full scenario suite, calibrated
./test/sim cal wrap   # same, with millis() about to overflow
```

Scenarios: boot state, module insert / remove, screwdriver short (off and while on), lockout, tool on the edge magnet (open), edge short, real neighbour, neighbour removed, neighbour at boot, millis() overflow.

Limit found: the pre-test accepts a neighbour with up to about 545 uF on its 20 V input. Keep each panel's input capacitance below 470 uF.
