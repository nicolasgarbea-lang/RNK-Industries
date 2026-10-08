# Design

| File | What it is |
|---|---|
| [`pal-concept-sheet_v1.webp`](pal-concept-sheet_v1.webp) | **Reference concept (v1)**: hero shot on a monitor, front/side/top/bottom views, key components, details |

Naming: `pal-<subject>_v<n>.<ext>`, e.g. `pal-faces_v1.png`.

## Design rules (from concept v1)

- **Colour / finish:** matte black, soft-touch, seamless. No visible screws or grilles from the front.
- **Head:** a rectangular block with **chamfered (angled) corners, not rounded**. It sits on a short round neck.
- **Screen:** a black glass panel with a thin bezel. The face is drawn in **cold white with a slight glow**.
- **Face:** **two round eyes plus a banana-shaped smile** (a thin curved line), nothing else. No cheeks, nose or extra details.
- **Body:** smooth with a small belly. Arms and legs are short and chubby, and they flow into the body (seamless).
- **Pose:** sits on the monitor edge, leans back on its hands, legs hang over the front.

## Expressions to design (screen animations)

| State | Face | When |
|---|---|---|
| Idle | Eyes + smile, blinks every 3-8 s, eyes drift a little | Default |
| Hello | Eyes curve into happy arcs (^ ^) | PC boot, user comes back |
| Reminder | Eyes + a small icon (water drop, check box…) below the mouth | Habit or to-do due |
| Listening | Eyes bigger, the mouth turns into a small level meter | After the wake word |
| Speaking | The smile opens and closes with the audio level | Text-to-speech |
| Proud | Eyes as stars or arcs, short bounce | Task or habit done |
| Sleepy | Eyes as flat lines, then the screen turns off | PC shutting down, quiet hours |
| Muted | Normal face + a small crossed-out mic icon in the corner | Mic mute switch on |

To do: draw each one at the real screen resolution (320 x 240) so firmware can use them directly.
