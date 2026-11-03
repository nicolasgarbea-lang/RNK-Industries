# Mini Pal: mechanical (the box)

> Status: proposal. No CAD yet. Check every size against the real parts.

## Size

| Part | Size (mm, W x H x D) | Notes |
|---|---|---|
| Box | 60 x 46 x 32 | Same shape as Pal's head: chamfered edges, ~3 mm chamfer |
| Foot / stand | ~40 x 4 x 30 | Tilts the box back ~10° so the face looks up at you. Non-slip pad underneath |
| **Total** | **~60 x 50 x 36** | |

The 2.0" screen module is ~50 x 36 mm, which gives a ~5 mm bezel. With the smaller 1.69" option the box could shrink to ~48 x 40 x 30 mm.

## Parts

| # | Part | Material (proto → production) | Notes |
|---|---|---|---|
| 1 | Front glass / bezel | Black acrylic 2 mm or cover glass | Hides the screen edges. Only the face glows |
| 2 | Front shell | PETG → ABS | Holds the screen |
| 3 | Back shell | PETG → ABS | Holds the PCB. USB-C opening at the back, light sensor window |
| 4 | Scroll wheel | Encoder wheel sticking out of a slot on the **right side** (~2-3 mm out), knurled black wheel | Like a watch crown / mouse wheel. Must turn smoothly with clear clicks without moving the box: check foot grip and weight |
| 5 | Foot | PETG + silicone pad | Could be clip-on, with optional mounts later (monitor clip, pegboard slot) |

The shells close with a snap fit or 2x M2 screws hidden under the foot.

## Checks for the first prototype

- [ ] The screen fits with an even bezel
- [ ] Scroll wheel: easy to reach, turns without the box sliding, slot hides the encoder body
- [ ] The light sensor sees the room through a small window
- [ ] The USB-C cable doesn't tip the box over (weight, foot size)
- [ ] Heat after a few hours on (ESP32 + Wi-Fi + backlight)
- [ ] Finish: same matte black process as Pal (sanding, primer, soft-touch paint)

## Files

| Folder | Contents |
|---|---|
| [`prototypes/`](prototypes/) | `mini-pal-<part>_proto-<n>.<ext>` + `mini-pal-<part>-notes.md` |
| [`final/`](final/) | `mini-pal-<part>_v<major>.<minor>.<ext>` + editable source (STEP / F3D) |
