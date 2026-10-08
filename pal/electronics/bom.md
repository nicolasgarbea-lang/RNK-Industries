# Pal: bill of materials (proposal)

Architecture: [`architecture.md`](architecture.md).

> Prices are rough estimates for small quantities (AliExpress / LCSC), **not verified**. Get real quotes before fixing the selling price.

## Breadboard prototype (to buy)

| Part | Qty | Role | Est. price (CHF) |
|---|---|---|---|
| ESP32-S3 DevKitC-1 N16R8 | 1 | Main controller | ~8 |
| 2.0" IPS 240 x 320 ST7789V SPI module | 1 | Face | ~4 |
| INMP441 I2S MEMS mic module | 2 | Voice input | ~2 each |
| MAX98357A I2S amp module | 1 | Audio out | ~2 |
| Speaker Ø20-28 mm, 4-8 Ω, 1-2 W | 1 | Voice output | ~1.5 |
| Mini slide switch | 1 | Mic mute | ~0.2 |
| Copper tape | 1 | Head-pat touch pad | ~1 |
| USB-C cable | 1 | Power + data from the PC | ~2 |

## Per unit (custom PCB, estimate)

| Part | Qty | Est. price (CHF) |
|---|---|---|
| ESP32-S3-WROOM-1 N16R8 | 1 | ~3.5 |
| 2.0" IPS ST7789V screen (bare panel, FPC) | 1 | ~3 |
| ICS-43434 MEMS mic | 2 | ~1 each |
| MAX98357A | 1 | ~0.8 |
| Speaker Ø20 mm 1 W | 1 | ~0.8 |
| USB-C receptacle + CC resistors + ESD protection | 1 | ~0.4 |
| 3.3 V regulator (≥ 600 mA) | 1 | ~0.3 |
| Slide switch, passives | – | ~0.5 |
| PCB (main + head board / flex), assembled | 1 | ~4 |
| Ballast weight | 1 | ~0.3 |
| Enclosure (printed proto / moulded later) | 1 | TBD |
| Cable, packaging | 1 | ~3 |
| **Electronics total** | | **~19 CHF + enclosure** |
