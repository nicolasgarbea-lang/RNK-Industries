# Pal: shopping list

> Prices are rough estimates (AliExpress / LCSC / local shops), **not verified**. Tick items off when ordered (☐ → ☑) and note the real price.
> Order phase 1 first. The rest can wait until the breadboard test works ([roadmap](roadmap.md)).

## Phase 1: breadboard proof (~45 CHF)

| ✓ | Item | Qty | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|
| ☐ | ESP32-S3 DevKitC-1 **N16R8** (16 MB flash, 8 MB PSRAM) | 2 | Main controller (1 spare) | ~16 | |
| ☐ | 2.0" IPS 240 x 320 screen, **ST7789V**, SPI | 2 | Face (1 spare) | ~8 | |
| ☐ | INMP441 I2S MEMS mic module | 3 | 2 for Pal + 1 spare | ~6 | |
| ☐ | MAX98357A I2S amplifier module | 2 | Audio out (1 spare) | ~4 | |
| ☐ | Mini speakers Ø20-28 mm, 4-8 Ω, 1-2 W (assorted) | 3 | Compare loudness and sound | ~5 | |
| ☐ | Breadboard (full size) + jumper wires (M-M, M-F) | 1 set | Wiring | ~6 | |
| ☐ | Mini slide switch | 5 | Mic mute | ~1 | |
| ☐ | Copper tape (adhesive) | 1 roll | Head-pat touch pad test | ~2 | |
| ☐ | USB-C data cable (not charge-only!) | 1 | Power + data from the PC | ~3 | |

## Phase 3: enclosure prototypes (~95 CHF)

| ✓ | Item | Qty | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|
| ☐ | Black PETG filament | 1 kg | Body/head prototypes | ~22 | |
| ☐ | Black TPU filament (85A-95A) | 0.5 kg | Softer arms/legs test | ~15 | |
| ☐ | Sandpaper set (240 → 1000 grit) | 1 | Smooth out print lines | ~6 | |
| ☐ | Filler primer spray | 1 | Fill layer lines before paint | ~12 | |
| ☐ | Matte black / soft-touch spray paint | 1 | "Seamless matte" finish | ~15 | |
| ☐ | Black acrylic sheet 2 mm (small) or cover glass 50 x 36 mm | 1 | Screen front | ~5 | |
| ☐ | M2 heat-set inserts + M2 screws (assorted) | 1 set | Close the shells | ~8 | |
| ☐ | Steel/zinc weights (fishing sinkers or washers) | ~10 | Ballast tests | ~4 | |
| ☐ | Silicone non-slip pads (adhesive) | 1 sheet | Base on the monitor | ~4 | |
| ☐ | Digital caliper | 1 | Measure screen/PCB/speaker (skip if you have one) | ~15 | |
| ☐ | *Optional:* resin printing service for a demo unit | 1 | Best "real product" finish | ~30-60 | |

## Phase 5: custom PCB (~120 CHF, order later)

| ✓ | Item | Qty | Why | Est. CHF | Real CHF |
|---|---|---|---|---|---|
| ☐ | PCB manufacturing + assembly (JLCPCB / PCBWay), main board + head board | 5 sets | First real boards | ~60-100 | |
| ☐ | Bare 2.0" ST7789V panels with FPC + matching FPC connectors | 5 | Screen without the module board | ~15 | |
| ☐ | ICS-43434 bare mics (if not assembled by the fab) | 10 | Smaller than the INMP441 module | ~10 | |

## Already owned / check first

- [ ] Soldering iron + solder
- [ ] 3D printer (240 x 240 x 240 bed)
- [ ] Multimeter
- [ ] USB power meter (USB-C inline), to measure Pal's current draw (~10 CHF if missing)

## Budget summary

| Phase | Est. CHF |
|---|---|
| 1: breadboard | ~45 |
| 3: enclosure | ~95 (+ optional resin demo) |
| 5: PCB | ~120 |
| 6: certification testing | a few thousand (get quotes) |
