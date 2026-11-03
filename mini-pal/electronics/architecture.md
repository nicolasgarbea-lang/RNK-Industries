# Mini Pal: electrical architecture (PROPOSAL v0.1)

> Status: proposal, nothing tested.

## Overview

```
 USB-C 5 V ──> [3.3 V regulator] ──> [ESP32-C3] ── SPI ──> [2.0" IPS 320x240 screen]
 (any charger)                           │  ├─ GPIO <── [scroll wheel: rotary encoder + push]
                                         │  ├─ ADC <── [light sensor]  (auto-dim at night)
                                         │  └─ PWM ──> [buzzer] (chirp)
                                         └─ BLE <── NRX phone app (time, widgets, weather, notifications)
```

## Blocks

| Block | Choice | Why |
|---|---|---|
| Microcontroller | **ESP32-C3** (the pegboard BOM lists 5x ESP32-C3 Super Mini Plus as bought: check with the team) | BLE (phone link) + Wi-Fi (later extras), cheap. ANCS (iPhone notifications) runs over its BLE. Enough power for the face at 20 fps if only the changed parts of the screen are redrawn. If it's too tight, switch to the ESP32-S3 (same code as Pal) |
| Screen | **2.0" IPS 320 x 240, ST7789V, SPI** (same as Pal) | Shared parts and face code. Option: 1.69" 280 x 240 for a smaller box |
| Scroll wheel | **Rotary encoder with push button** (prototype: KY-040 / EC11 module; product: a low-profile side thumbwheel encoder, e.g. Alps EC10 / mouse-wheel style) | Turn = scroll widgets, press = select. Uses 3 GPIOs (A, B, push) |
| Light sensor | Phototransistor or LDR (e.g. ALS-PT19) | Dims the screen at night, sleeps in the dark |
| Sound | Small passive buzzer, 12 mm | Notification chirp, volume via PWM, can be muted |
| Power | USB-C receptacle (5.1 kΩ CC resistors, so it works with C-to-C chargers) + 3.3 V LDO (≥ 500 mA) | Any phone charger or PC USB port |

## Power budget (estimate)

| Consumer | Typical |
|---|---|
| ESP32-C3 (BLE connected, light sleep) | 15-40 mA |
| Screen + backlight | 30-60 mA |
| **Total at 5 V** | **~0.5 W**, so any USB port works |

## Pin budget (ESP32-C3 SuperMini)

The SuperMini exposes ~13 usable GPIOs. Mini Pal needs 11:

| Function | Pins |
|---|---|
| Screen (SCK, MOSI, CS, DC, RST, backlight) | 6 (RST can be tied to the board's reset to save 1) |
| Scroll wheel (A, B, push) | 3 |
| Light sensor (ADC) | 1 |
| Buzzer (PWM) | 1 |

Avoid the boot/strapping pins (GPIO 2, 8, 9) for the wheel and buzzer.

## RAM note (ESP32-C3)

The C3 has ~400 KB of RAM. A full 320 x 240 frame is 150 KB, which fits, but keeping two full frames would not. Plan to redraw **only the changed areas** (the eyes when blinking, the clock digits). This is what most face/clock projects do, and it is enough for smooth 20 fps.

## Prototype plan

1. ESP32-C3 SuperMini + 2.0" ST7789 module + KY-040 rotary encoder + KY-018 light sensor + KY-006 buzzer on a breadboard.
2. Test: face at 20 fps, BLE link with a phone, iPhone notifications (ANCS), chirp, scroll wheel (smooth counting, no skipped steps).
3. Then a small custom PCB that fits behind the screen.

BOM: [`bom.md`](bom.md).
