# Pal: firmware (PROPOSAL v0.1)

Runs on the ESP32-S3 inside Pal. Hardware: [`../electronics/architecture.md`](../electronics/architecture.md).

Toolchain: **ESP-IDF** (needed for ESP-SR wake word) through PlatformIO, or the Arduino-ESP32 core on top of IDF. To be decided after the breadboard test.

## Modules

| Module | Role |
|---|---|
| `face/` | Draws the face (eyes + banana smile) and the animations from [`../design/`](../design/README.md#expressions-to-design-screen-animations). LVGL or TFT_eSPI sprites, 30 fps target |
| `audio/` | I2S in (2 mics) and I2S out (amp). Volume, play a sound or a speech stream |
| `voice/` | Wake word on the device (ESP-SR WakeNet, e.g. "Hey Pal"), then streams audio to the app. See [voice pipeline](#voice-pipeline) |
| `reminders/` | Local copy of today's to-dos and habits, with timers. Reminders still fire if the app is closed |
| `link/` | Talks to the NRX app: USB serial (CDC) first, Wi-Fi later. Protocol in [`../app/README.md`](../app/README.md#pal--app-protocol) |
| `input/` | Head-pat touch (tap = snooze, double-tap = done, long press = talk), mic mute switch |
| `power/` | Boot, PC-gone detection → sleep, screen brightness, quiet hours |
| `storage/` | NVS: settings, Wi-Fi credentials, cached reminders |
| `ota/` | Firmware updates through the app |

## States

```
 BOOT ──> HELLO ──> IDLE <──────────────┐
                    │  │                │
       reminder due ┘  └ wake word / long press
                    ▼          ▼        │
                REMINDER    LISTENING ──> THINKING ──> SPEAKING
                    │                                    │
     pat / done ────┴────────────────────────────────────┘
 PC off / no host ──> SLEEPY ──> SCREEN OFF
```

## Voice pipeline

1. **On Pal:** the wake word or a long press opens the mic. Pal streams 16 kHz audio to the app.
2. **In the app (PC):** speech-to-text → understand the request (add a to-do, "what's on my list?", "I drank water") → write the answer → text-to-speech.
3. **On Pal:** plays the answer audio while showing the **Speaking** face.

The heavy work runs on the PC/cloud, so Pal stays cheap. Which STT/LLM/TTS service to use is still to be decided (cost per user per month, privacy, offline mode).

Without the app, Pal still: shows faces, fires cached reminders with pre-recorded sounds, and reacts to the head pat.
