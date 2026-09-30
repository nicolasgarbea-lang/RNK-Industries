# Brain panel schematic v0.2 (Tinkered export)

Generated with [Tinkered](https://www.tinkered.ai/) (v0.1), then edited by hand:

- `RPRE` (edge pre-test resistor): 4.7 k -> **470 ohm, 1 W**. With 4.7 k, a neighbour's 220 uF input capacitor only reaches about 1 V after 50 ms and was rejected as a short.

Not re-simulated in Tinkered after this change (no credits left). The firmware logic is covered by the host tests in `firmware/proto-brain-panel/test/`.

Placeholders used by Tinkered: Arduino Nano instead of CH32V003, ESP32-C3-DevKitM-1 instead of ESP32-C3 SuperMini, voltage source instead of the edge Hall sensor.
