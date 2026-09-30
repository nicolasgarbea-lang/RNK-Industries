# Components (final versions)

Production-ready 3D printing files. Only parts that are print-tested and approved live here. Work in progress goes in [`../prototypes/`](../prototypes/), which mirrors this structure.

## Categories

| Folder | Contents |
|---|---|
| `panels/` | Base panel tiles/sections (pegboard grid, edge frames, corner joints) |
| `mounts/` | Holders and shelves: keyboard, controller, headset, mouse, phone, bottle, pen cup, cable hook, monitor shelf |
| `accessories/` | Small add-ons: plant pot holder, figurine shelf, storage bin, clips |
| `rgb-lighting/` | Diffusers, LED strip channels, controller housings (Arduino / embedded) |

## Naming convention

`<category>-<part-name>_v<major>.<minor>.<ext>`, e.g. `mounts-headset-hook_v1.2.stl`

- Keep the editable source (STEP / F3D / etc.) next to the printable file.
- Print settings (material, layer height, infill, supports, print time, weight) go in a `<part>.md` note or in the product catalog.
