# Mini Pal: shopping list

> Prices are rough estimates, **not verified**. Many parts overlap with [Pal's shopping list](../pal/shopping-list.md): buy once, use for both.

## Phase 1: breadboard prototype, 1 unit (~20-25 CHF): order now

The search terms are exact enough to paste into AliExpress / Amazon / Galaxus. Small modules are often sold only in packs of 3-10; that's fine, they cost cents each.

| ✓ | Search term | Qty | Pick this variant | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|---|
| ☐ | `ESP32-C3 SuperMini` | 1 | **Pins already soldered** ("welded" / "soldered" option), pins pointing down | Brain | ~1-3 | |
| ☐ | `2.0 inch IPS TFT LCD module 240x320 ST7789V SPI` | 1 | **8-pin SPI version with pins** (GND VCC SCL SDA RES DC CS BLK), **not** the bare FPC panel | Face | ~4 | |
| ☐ | `KY-040 rotary encoder module` | 1 | With push button (all KY-040 have one) | Scroll wheel | ~1 | |
| ☐ | `KY-018 photoresistor module` | 1 | Resistor already on the module | Auto-dim at night | ~1 | |
| ☐ | `KY-006 passive buzzer module` | 1 | **Passive**, not active (passive can play different chirp tones) | Notification chirp | ~1 | |
| ☐ | `400 point breadboard` | 1 | Half size | Wiring | ~2 | |
| ☐ | `dupont jumper wire 20cm` | ~20 | Male-male + male-female (sets of 40+) | Wiring | ~3 | |
| ☐ | `USB-C data cable` | 1 | Data cable, not charge-only | Programming + power | ~3 | |

### Tools (only if a part arrives with loose pins)

| ✓ | Search term | Qty | Pick this variant | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|---|
| ☐ | `soldering iron kit adjustable temperature 60W` | 1 | With stand + tips (or a Pinecil, ~30 CHF, much better) | Solder pin headers | ~15-30 | |
| ☐ | `solder wire 0.8mm rosin core` (Sn63/Pb37 or lead-free) | 1 roll | – | – | ~5 | |
| ☐ | `digital multimeter` | 1 | Any basic one (optional) | Check wiring and voltages | ~15 | |

Free: the **nRF Connect** app (iPhone / Android) to test Bluetooth before the NRX app exists. Skip the screen and breadboard if they're already ordered for Pal.

## Phase 3: box prototypes

Same as Pal: black PETG, sandpaper, primer, soft-touch paint, black acrylic, M2 screws, silicone pads ([Pal list](../pal/shopping-list.md#phase-3-enclosure-prototypes-95-chf)). Extra:

| ✓ | Item | Qty | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|
| ☐ | Black acrylic 2 mm, small sheet | 1 | Front glass for several prototypes | ~5 | |

## Phase 4: custom PCB (~50 CHF)

| ✓ | Item | Qty | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|
| ☐ | PCB fab + assembly (JLCPCB / PCBWay) | 5 | First real boards | ~40 | |
| ☐ | Bare 2.0" ST7789V panels + FPC connectors | 5 | Screen without module board | ~15 | |
