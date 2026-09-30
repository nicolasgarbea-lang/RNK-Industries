# Firmware

Code running on the pegboard electronics. See [`../electronics/architecture.md`](../electronics/architecture.md).

| Folder (to create) | Target | Role |
|---|---|---|
| `brain/` | ESP32-C3 (brain panel) | WiFi/BLE, app connection, modes, bus master, layout map |
| `panel/` | CH32V003 (every panel) | Slot and edge detection (Hall), power switching, LED data per slot, LIN bus |
| `screen-module/` | ESP32 in the screen module | Display (round 1.28"), receives content over WiFi |

Toolchain: to be decided (PlatformIO suggested).

Prototype firmware (Arduino Nano placeholder, tested): [`proto-brain-panel/`](proto-brain-panel/).
