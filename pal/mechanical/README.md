# Mechanical (enclosure)

> Status: proposal. No CAD yet. Dimensions are targets to check against the real parts (screen, PCB, speaker).

## Envelope

The whole robot, in its sitting pose, must fit in a **60 x 90 x 60 mm** box (orientation to confirm, see the [main README](../README.md#open-questions)).

Proposed split (60 W x 90 H x 60 D):

| Part | Size (mm, W x H x D) | Notes |
|---|---|---|
| Head | 60 x 44 x 32 | Chamfered edges, ~3 mm chamfer. Holds the screen |
| Neck | Ø 12 x 4 | Hides the cable between head and body |
| Body | 46 x 32 x 36 | Belly. Holds the main PCB, speaker and ballast |
| Arms | Ø ~8 | Reach back and down. The hands rest on the monitor behind the body |
| Legs | Ø ~10 | Hang over the front edge of the monitor |

The 2.0" screen module is about 50 x 36 mm with a 40.8 x 30.6 mm active area. That leaves a bezel of about 5 mm on the sides and 4 mm top/bottom inside a 60 x 44 mm head, which matches the concept image.

## Parts (from concept v1)

| # | Part | Material (proto → production) | Notes |
|---|---|---|---|
| 1 | Screen bezel / front glass | Black acrylic or glass | Glued or clipped onto the head front |
| 2 | Head shell (front + back) | PETG → ABS | Splits behind the screen. Mic pinholes on top |
| 3 | Inner frame | PETG → ABS | Holds the screen, the head board and the neck screw |
| 4 | Body shell (left + right, or top + bottom) | PETG → recycled ABS, soft-touch paint | The seam must be almost invisible (concept: "seamless") |
| 5 | Arms and legs | PETG → ABS, or TPU for a softer feel | Part of the body shells, or clipped in |
| 6 | Base / bottom cover | ABS + silicone non-slip pad | Speaker vents and the USB-C port hidden at the back or bottom |
| 7 | Ballast | Steel or zinc weight (~25-40 g) | Low and to the back, so the heavy head does not tip Pal forward |

## Mechanical checks for the first prototype

- [ ] **Stability:** does it stay put on the edge of a monitor? Test on a thin modern bezel (~10 mm) and on a thick one.
- [ ] **Centre of gravity:** the head is the heaviest part (screen). Where does the ballast need to go?
- [ ] **Heat:** the ESP32-S3 with Wi-Fi uses ~0.5 W. Does the body get warm?
- [ ] **Sound:** the speaker needs a small sealed back volume and an outlet (bottom or back vents).
- [ ] **Mics:** pinholes on top of the head, with a gasket to stop the speaker sound reaching them through the inside.
- [ ] **Cable:** the USB-C cable leaves from the back or bottom and must not pull Pal off the monitor.
- [ ] Print finish: how close can FDM get to "seamless matte"? Sanding + soft-touch paint? Resin print for the demo unit?

## Files

| Folder | Contents |
|---|---|
| [`prototypes/`](prototypes/) | Work in progress: `pal-<part>_proto-<n>.<ext>` + `pal-<part>-notes.md` |
| [`final/`](final/) | Approved parts: `pal-<part>_v<major>.<minor>.<ext>`, with the editable source (STEP / F3D) next to it |
