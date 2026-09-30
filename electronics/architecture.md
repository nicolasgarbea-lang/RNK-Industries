# Electrical architecture (PROPOSAL v0.2)

> Status: architecture agreed in principle by both founders. Nothing is tested yet.
> All numbers are estimates to be measured on the prototypes.

## Decisions taken

- Brand: **NRX Industrie**. Name of the RGB pegboard product: **to be decided**.
- Panel size: **200 x 170 mm** (printer bed 240 x 240 x 240, so there is margin), **2 slots per panel**.
- Sold in **kits** (several sizes / prices). Every kit contains exactly **1 brain panel**, which is never sold alone. Extra standard panels can be bought separately.
- **Plug and play**: customers assemble panels freely, on any side.
- Power in: **USB-C PD, 20 V**, on the brain panel.
- Slots (panel <-> module) and edges (panel <-> panel) both use the **5-pin magnetic pogo connector**.
- Every mount has an LED strip at the bottom. Some mounts have a round screen.

## Overview

```
 [Panel]==[BRAIN]==[Panel]
    ||       ||
 [Panel]==[Panel]==[Panel]

 == and || : edge link (5-pin magnetic connector, 20 V + bus)
```

Power and data are **shared by all panels** (a network, not a chain): a panel can be attached on any side of any other panel.

## One PCB for every panel

The brain panel is a **standard panel + extra parts**. One PCB design, one assembly process, lower cost.

| Block | Standard panel | Brain panel adds |
|---|---|---|
| Microcontroller | CH32V003, powered at **5 V**: it drives the WS2812B directly (no level shifter needed) | ESP32-C3 (WiFi / Bluetooth, app, modes, bus master) |
| Power | 20 V bus -> 5 V buck (3 A) for its 2 slots | USB-C PD sink (e.g. CH224K) asking for 20 V + input protection |
| Bus | LIN transceiver (single wire, many panels on the same wire, runs from the 20 V bus; check datasheet limits) | A second LIN transceiver for the ESP32 |
| Detection | Slots: module ID read on the DATA pin (no sensor). Edges: 4 linear Hall sensors + current-limited pre-test | |

## Slot connector (panel <-> module): 5 pins, symmetric

**This pinout becomes frozen as soon as the first modules are sold.** Changing it later makes every sold module incompatible.

| Pin | Signal | Notes |
|---|---|---|
| 1 | GND | |
| 2 | +5 V (switched) | Live only when a module is detected |
| 3 | LED DATA + module ID | From the panel MCU, one line per slot. Each module has an ID resistor from this pin to GND |
| 4 | +5 V (switched) | Same net as pin 2 |
| 5 | GND | Same net as pin 1 |

- Module rotated by 180 degrees = same signals, **no reverse-polarity risk**, and 2 pins each for power and ground.
- Female (flat) on the panel, male (pins) on the module.

## Module detection and ID (no Hall sensor on slots)

Every module contains **one ID resistor between pin 3 (DATA) and GND**. The panel has a **100 k pull-up** from pin 3 to 5 V and reads pin 3 with an ADC.

| Voltage read on pin 3 | Meaning | Action |
|---|---|---|
| About 5 V (nothing pulls it down) | Empty slot | Stay OFF |
| A known level (see table below) | **Real module, and its type** | Switch ON |
| Below about 0.2 V | **Short circuit** (tool across the pins) | Stay OFF, retry after 2 s |

| Module type | ID resistor | Voltage read (100 k pull-up, 5 V) |
|---|---|---|
| LED module | 10 k | ~0.45 V |
| Screen module | 15 k | ~0.65 V |
| Controller dock | 22 k | ~0.90 V |
| Sound-reactive / other premium | 33 k | ~1.24 V |

Rules:

- **All ID levels stay below 1.5 V** (the WS2812B "low" threshold at 5 V), so reading pin 3 between LED frames does not disturb the LEDs.
- While the slot is ON, the MCU re-reads pin 3 between LED frames (about every 20 ms). If it jumps to 5 V, the module has been removed: **cut the slot power immediately**.
- A steel tool cannot fake a precise resistor value, unlike a Hall sensor (which a screwdriver stuck on the connector magnet can trigger).
- A tool across +5 V and GND only: pin 3 still reads "empty", so the slot never turns on.
- Optional: a plastic cap on empty slots, for dust and looks only (not a safety feature).
- To test on prototype 1: signal quality with the ID resistor on the data line, and the tiny current fed into an unpowered strip during detection.
- Open question: 3 data lines instead (idea from Ramy). A screen module receives its content over WiFi, so 1 data line is enough today. 3 data lines would leave only 1 pin for +5 V and 1 for GND: no symmetry, polarity keying needed, half the current per slot.

## Edge connector (panel <-> panel): same 5-pin connector

| Pin | Signal |
|---|---|
| 1 | GND |
| 2 | +20 V bus |
| 3 | BUS (LIN, single wire) |
| 4 | +20 V bus |
| 5 | GND |

- On **each edge: 1 female + 1 male, placed point-symmetric** (seen from outside: female on the left, male on the right). Any edge then mates any edge of another panel, in any orientation.
- 4 edges = **4 female + 4 male per panel**. 2 connectors per edge = 4 power pins per link.

**Danger: the edge connector is the same part as the slot connector but carries 20 V.** A 5 V module placed on an edge would be destroyed. So:

1. Edge connectors sit **on the panel sides**, where a module cannot reach them.
2. Edge ports stay **OFF until a neighbour panel is detected**.

## Safety: everything is OFF by default

The magnets attract screws, tools and filings. No exposed contact may be live without reason.

- **Slots**: the module ID resistor is read on pin 3 (see above) -> 5 V switch on only for a valid ID. Polyfuse about 1.5 A per slot.
- **Edges**: a Hall sensor detects the neighbour's connector, then a **current-limited pre-test** (20 V through about 470 ohm / 1 W for 20 ms, voltage measured on the edge): below 0.5 V = short (reject), above 18 V = nothing connected (reject), 1.5-15 V = a neighbour's input capacitors charging (accept). Rule: keep each panel's 20 V input capacitance below 470 uF (above about 545 uF the pre-test rejects it). Two panels that are both already powered from other sides see each other as "nothing connected" and keep that edge OFF (no power loop). Current limit about 3 A per edge. A Hall sensor alone is not enough: a steel tool on the magnet can trigger it.
- A new panel does not need power to be detected: the powered neighbour sees its edge Hall sensor change and switches its edge port on, which boots the new panel.
- **Edge switches must block current in both directions.** Power can arrive from any side: a single P-MOSFET would leak 20 V to the other edges through its body diode. Use back-to-back MOSFETs or a load switch with reverse blocking.
- Brain input: TVS diode + fuse.

## Automatic layout detection (selling point)

Each panel reports to the brain which of its edges has a neighbour (with its unique chip ID). The brain rebuilds the map of the wall:

- LED effects can flow across the whole wall in the right order.
- The app shows the real layout.

## Power budget (estimates)

- USB-C PD: 20 V x 3 A = **60 W** with a standard cable.
- Worst link: up to 3 A at 20 V next to the brain, over 4 power pins = **0.75 A per pin**. Pins must be rated 1 A or more (check the bought part).
- Per panel: 2 slots x up to 1.5 A at 5 V = 15 W -> 3 A buck.
- WS2812B: up to about 60 mA per LED at full white. **The firmware caps brightness** so a full kit stays under about 45 W.

## Modules

| Module | Contents | Notes |
|---|---|---|
| LED module | LED strip + 1 male connector. **No electronics** | Cheapest to build, main source of margin |
| Screen module | Round 1.28" display (GC9A01, 240 x 240) + ESP32-C3 + male connector | Premium. Content over WiFi, not through the pogo pins |

## Premium modules (ideas)

Premium modules use all 5 pins: 4 for power (2 x +5 V, 2 x GND) and the DATA line for their LEDs.
Their "intelligence" is an ESP32-C3 inside the module, talking to the brain over WiFi / ESP-NOW (not through the pogo pins).

| Module | What it does | Extra parts | Limit |
|---|---|---|---|
| Controller charging dock | Charges the controller over USB-C, LED charging animation | USB-C cable / port | Check the controller's charging current vs the 1.5 A slot limit |
| Sound-reactive module | A microphone makes **the whole wall** pulse with music or game sound | ESP32-C3 + I2S MEMS mic (e.g. INMP441) | Latency: use ESP-NOW |
| Macro pad / mini stream deck | 4-6 RGB buttons: Discord mute, OBS scenes, shortcuts. Seen by the PC as a Bluetooth keyboard | ESP32-C3 (Bluetooth LE) + switches | |
| Desk air-quality module | CO2 / temperature on the screen, LEDs turn orange when it is time to ventilate | ESP32-C3 + CO2 sensor | CO2 sensors are the expensive part |
| Wireless phone stand (Qi) | Charges the phone | Qi transmitter board | Only about 5 W from a 5 V slot: slow. Fast charging needs 9 V+ |
| Screen module | See above | | |

## Screen modes (product idea)

- Music: album art of the current track, all LEDs take the cover's colours.
- Rest: clock + weather, dimmed LEDs.
- Live: "ON AIR" + viewer count for streamers.
- Gaming: GPU temperature / load as a gauge, LEDs from blue to red. Needs a companion app on the PC, so later.

## Open questions

- [ ] Product name for the RGB pegboard
- [ ] 1 or 3 data lines on the slot connector (see above)
- [ ] Current rating per pin of the bought connector
- [ ] Stable supplier for the connector before freezing the standard (the AliExpress listing may disappear)
- [ ] Edge 20 V switch design (reverse blocking, current limit)
- [ ] Edge detection: Hall sensor tuning (panel-side connector already has a magnet) and pre-test design. Could the edges use a signature resistor too, without loading the LIN bus?
- [ ] Validate the module ID resistor values on the real LED strip
- [ ] Kits: contents and prices
- [ ] Conformity rules for selling electronics in CH/EU: find out before selling

## Prototype plan

1. **Proto 1**: 1 brain panel (2 slots) + 1 LED module. Validates slot detection, slot switching, LEDs, USB-C PD.
2. **Proto 2**: brain + 1 standard panel. Validates edge link, 20 V switching, LIN bus, layout detection.
3. **Proto 3**: screen module.

Bill of materials: [`bom.md`](bom.md).
