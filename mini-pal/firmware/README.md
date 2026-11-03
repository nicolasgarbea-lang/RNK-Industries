# Mini Pal: firmware (PROPOSAL v0.1)

Runs on the ESP32-C3. Hardware: [`../electronics/architecture.md`](../electronics/architecture.md).

**Shared with Pal:** the face engine (eyes, banana smile, blinking, expressions). Plan to put it in one shared library that both products use, so improvements go to both.

Toolchain: PlatformIO + Arduino-ESP32, with LovyanGFX or TFT_eSPI for the screen.

## Screens

The user's **widgets rotate automatically** in a loop, e.g. face → clock → weather → calendar → face… The user sets which widgets, their order and how long each one shows (default: face 20 s, others 8 s) in the [phone app](../app/README.md#widgets). Screens change with a short transition: the eyes slide or blink away.

- **Notification:** interrupts the rotation, stays until the wheel is pressed (or for 30 s), then the rotation continues.
- **Turn the wheel:** previous / next widget. The auto-rotation pauses and resumes 30 s after the last turn.
- **Press:** dismiss a notification, or pause on the current widget (press again to resume). **Long press:** Bluetooth pairing mode.
- **Night:** the rotation stops and the sleeping face shows.

| Screen | Shows |
|---|---|
| **Face** (default) | Idle face: blinks, looks around, sometimes yawns. Mood follows the weather (happy in the sun, sleepy eyes when it rains…) |
| **Time** | Big clock + date. The face shrinks into a corner or the eyes become the clock's colon |
| **Weather** | Today: icon + temperature + min/max + rain chance. Optional: the next 3 hours |
| **Calendar** | Next event + "in 10 min" countdown |
| **Notification** (pops up) | Face reacts (surprised eyes) + icon + short text. Press the wheel = dismiss |
| **Night** | Screen off or a very dim sleeping face (light sensor + quiet hours) |

## Modules

| Module | Role |
|---|---|
| `face/` | Shared face engine, 20 fps, redraws only changed areas |
| `clock/` | Keeps time locally; synced from the phone over BLE |
| `widgets/` | One layout per widget (clock, weather, calendar…), filled with data from the app. Caches the last data |
| `notify/` | Notifications: reads iPhone ANCS directly, receives Android notifications from the app. Plays the chirp |
| `rotation/` | Screen loop: order, time per screen, transitions, pause/resume, notification interrupts |
| `input/` | Scroll wheel: rotary encoder (debounced, interrupt-driven), press, long press |
| `light/` | Auto-brightness, night mode |
| `ble/` | Pairing + messages with the NRX phone app (see [app](../app/README.md#ble-messages-first-draft)) |
| `ota/` | Firmware updates through the phone app (BLE) or Wi-Fi |

## Weather data

Mini Pal does not fetch weather itself: the **phone app** fetches it and sends a short summary over BLE. Sources and licences: [app](../app/README.md#weather-cant-we-just-use-the-phones-weather-app).
