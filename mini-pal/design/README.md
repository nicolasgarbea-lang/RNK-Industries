# Mini Pal: design

Same design rules as [Pal](../../pal/design/README.md#design-rules-from-concept-v1): matte black, chamfered (not rounded) corners, black glass front, a face with only two round eyes and a banana smile in cold white.

## Screens to design (320 x 240)

The user's widgets rotate automatically (e.g. face → clock → weather → calendar → face…), so also design the **transitions** between them, e.g. the eyes blink shut, then the clock fades in.

| Screen | Content |
|---|---|
| Face | Pal's idle face + blink + look around |
| Time | Big clock + date. The eyes could become the clock's colon |
| Weather | Icon + temperature + min/max + rain %. Plus face moods per weather (sun, cloud, rain, snow, storm) |
| Notification | Surprised eyes + icon (mail, calendar, chat, alert, heart) + short text |
| Calendar | Next event title + time, "in 10 min" countdown |
| Pairing | "Open the NRX app" + Bluetooth icon |
| Night | Sleeping face, very dim |

Naming: `mini-pal-<subject>_v<n>.<ext>`. Add a concept image here when ready.
