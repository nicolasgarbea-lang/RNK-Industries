# Bill of materials (proposal)

Architecture: [`architecture.md`](architecture.md).

> Prices are rough estimates for small quantities (AliExpress / LCSC), **not verified**. Get real quotes before fixing selling prices.

## Already bought

| Part | Qty | Price paid (CHF) | Notes |
|---|---|---|---|
| WS2812B LED strip, 5 V, black PCB | 1 roll | 5.43 | LED density per metre to check |
| Magnetic pogo connector, 5 pins, 2.5 mm pitch (male + female pair) | 3 pairs | 2.41 each | Current rating per pin to check. Also available in multi-packs at about 0.90 CHF per pair |
| ESP32-C3 Super Mini Plus | 5 | 2.37 each | Brain + screen modules. Test WiFi early (weak on some batches) |

## Per standard panel

| Part | Qty | Role | Est. price (CHF) |
|---|---|---|---|
| CH32V003 microcontroller | 1 | Panel brain, powered at 5 V | ~0.20 |
| Buck converter 20 V -> 5 V, 3 A (proto: MP1584 module) | 1 | 5 V for the 2 slots | ~1 |
| Linear Hall sensor SS49E | 4 | Edges only (slots use the module ID resistor) | ~0.10 each |
| Resistor 100 k | 2 | Pull-up on pin 3 of each slot (module detection) | |
| Resistor 1 k-10 k + small transistor | 4 | Current-limited pre-test on each edge | |
| P-MOSFET AO3401 + small NPN / N-MOSFET driver | 2 each | Slot 5 V on/off | ~0.10 each |
| Edge 20 V switch with reverse blocking (2 back-to-back P-MOSFETs rated 30 V or more, or a load switch IC) | 4 | Edge on/off | ~0.30-0.50 each |
| Polyfuse about 1.5 A | 2 | Slot current limit | ~0.10 each |
| Polyfuse / eFuse about 3 A | 4 | Edge current limit | ~0.20 each |
| LIN transceiver (e.g. TJA1021) | 1 | Bus between panels | ~0.50-1 |
| Resistors 330-470 ohm | 2 | In series on each LED data line | |
| Capacitors (decoupling + about 470-1000 uF on 5 V) | a few | | |
| Magnetic connector, female side | 2 | Slots | |
| Magnetic connector, female + male | 4 + 4 | Edges | |
| PCB (proto: perfboard) | 1 | | |

Slots and edges need **6 connector pairs per panel** (the 2 spare male halves go into modules): about 6 x 0.90 = **~5.40 CHF per panel** when bought in packs.

## Brain panel = 1 standard panel + these parts

| Part | Qty | Role | Est. price (CHF) |
|---|---|---|---|
| USB-C PD trigger board, 20 V (e.g. CH224K) | 1 | Power input | ~1-2 |
| ESP32-C3 Super Mini | 1 | WiFi / Bluetooth, app, modes, bus master | already bought |
| LIN transceiver (e.g. TJA1021) | 1 | ESP32 <-> bus | ~0.50-1 |
| TVS diode about 24 V (e.g. SMBJ24A) + fuse about 3.5 A | 1 each | Input protection | ~0.30 |
| Bulk capacitor 100-470 uF, 35 V or more | 1 | Input | ~0.20 |
| NRX logo / branding | | The brain panel carries the brand | |

For testing: a USB-C PD charger of **60 W or more** that supports 20 V.

## Per LED module

| Part | Qty |
|---|---|
| WS2812B strip segment | N LEDs (length of the mount) |
| Magnetic connector, male side | 1 |
| Capacitor about 100 uF | 1 |
| ID resistor 10 k (pin 3 to GND) | 1 |

No microcontroller, no converter.

## Per screen module

| Part | Qty | Est. price (CHF) |
|---|---|---|
| Round display 1.28", GC9A01, 240 x 240 | 1 | ~3-5 |
| ESP32-C3 Super Mini | 1 | already bought |
| Magnetic connector, male side | 1 | |
| ID resistor 15 k (pin 3 to GND) | 1 | |
| WS2812B strip segment (optional) | N LEDs | |

## Tools (buy once)

| Tool | Why |
|---|---|
| WCH-LinkE programmer (~5-8 CHF) | Required to program the CH32V003 |
| USB-C PD charger 60 W+ | Power the prototypes |

## Shopping list for proto 1 + proto 2

Brain panel + 1 standard panel + 2 LED modules, with spares for mistakes.

| Part | Need | Buy (with spares) |
|---|---|---|
| CH32V003 | 2 | 10 |
| WCH-LinkE programmer | 1 | 1 |
| MP1584 buck modules | 2 | 4 |
| SS49E (edges only) | 8 | 10 |
| Resistors 10 k, 15 k, 22 k, 33 k, 100 k | a few each | resistor assortment kit |
| AO3401 + small NPN | 4 each | 10 each |
| P-MOSFETs 30 V+ for edge switches | 16 | 20 |
| Polyfuses 1.5 A | 4 | 10 |
| Polyfuses / eFuses 3 A | 8 | 10 |
| TJA1021 (LIN) | 3 | 5 |
| USB-C PD trigger 20 V | 1 | 2 |
| TVS SMBJ24A | 1 | 5 |
| Magnetic connector pairs | 6 (4 slots + 1 edge link) | **at least 6 more** (only 3 in hand) |
| Resistors, capacitors, perfboard, wires | | assortment kits |
| USB-C PD charger 60 W+ | 1 | 1 (if not owned) |

Not needed any more: 74AHCT125 level shifter (the CH32V003 runs at 5 V). Only needed if a prototype drives the LEDs directly from an ESP32.
