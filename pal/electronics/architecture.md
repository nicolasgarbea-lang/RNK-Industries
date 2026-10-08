# Pal: electrical architecture (PROPOSAL v0.1)

> Status: proposal, nothing tested. Parts chosen to fit the 60 x 90 x 60 mm envelope.

## Overview

```
 PC USB ──5 V + data──> [USB-C] ──> [ESP32-S3]  (body, main PCB)
                                       │  ├─ I2S out ──> [MAX98357A amp] ──> [speaker Ø20-23 mm]
                                       │  ├─ touch pin ──> [head-pat pad]
                                       │  └─ GPIO <── [mic mute switch]
                         flex cable through the neck
                                       │
                         [head board] ─┼─ SPI ──> [2.0" IPS 320x240 screen]
                                       └─ I2S in <── [2x MEMS mic] (top of head)
```

- **One main PCB** in the body. A small **head board** (or just a flex) carries the screen connector and the mics.
- **Power** comes only from USB-C (5 V, < 500 mA). No battery: Pal is on when the PC is on.
- **Data** goes over the same USB cable: the ESP32-S3 has native USB, so it shows up on the PC as a serial device (CDC) and talks to the NRX app.

## Blocks

| Block | Choice | Why |
|---|---|---|
| Microcontroller | **ESP32-S3-WROOM-1 N16R8** (16 MB flash, 8 MB PSRAM) | Native USB, Wi-Fi + BLE, enough PSRAM for the screen buffer and the on-device wake word (ESP-SR). The ESP32-C3 used in the pegboard is too small for voice |
| Screen | **2.0" IPS, 320 x 240, ST7789V, SPI** | Matches the head size (see [mechanical](../mechanical/README.md)). Backlight dimmed by PWM |
| Microphones | **2x I2S MEMS** (ICS-43434 or INMP441) | Two mics allow noise reduction and beamforming in ESP-SR. Pinholes on top of the head |
| Audio out | **MAX98357A** I2S class-D amp + **Ø20-23 mm, 1 W** speaker | Simple, cheap, runs from 5 V |
| Touch | ESP32-S3 capacitive touch pin + copper pad inside the top of the head | "Pat the head" = snooze / done. No hole in the shell |
| Mic mute | **Physical slide switch** that cuts the mics' power | Privacy: the user can trust it, because software cannot override it |
| Status | Mic-active LED next to the switch (optional) | Shows when Pal is listening |
| Power | USB-C receptacle (5.1 kΩ CC resistors) → 3.3 V LDO or buck (≥ 600 mA) | The PC USB port gives 500 mA (USB 2) or 900 mA (USB 3) |

## Power budget (estimate)

| Consumer | Typical | Peak |
|---|---|---|
| ESP32-S3 (Wi-Fi on) | 100 mA | 350 mA |
| Screen + backlight | 40 mA | 60 mA |
| Amp + speaker (5 V) | 20 mA | 250 mA |
| Mics | 2 mA | 2 mA |
| **Total at 5 V** | **~170 mA** | **~550 mA** |

The peak is above USB 2.0's 500 mA. Limit speaker volume in firmware, or ask the PC for more current (USB 3 = 900 mA). Measure on the prototype.

## "Turns on with the PC"

- When the PC boots, USB 5 V comes on and Pal boots (~1-2 s), then shows the **Hello** face.
- When the PC shuts down, 5 V goes off and Pal turns off. Many PCs keep USB powered while asleep or even when off, so Pal must also **watch the USB data link**: if the NRX app or USB host is gone for N seconds, Pal shows **Sleepy** and turns the screen off.

## Prototype plan

1. **Breadboard:** ESP32-S3 DevKitC-1 (N16R8) + 2.0" ST7789 module + INMP441 + MAX98357A + small speaker.
2. Test: face animation frame rate, wake-word accuracy at 50-80 cm, speaker loudness inside a printed body.
3. Then a custom PCB sized for the body.

BOM: [`bom.md`](bom.md).
