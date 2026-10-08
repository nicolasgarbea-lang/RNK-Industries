# NRX Industrie

*Next Robotique eXploration*

Brand: **NRX Industrie**. Product name for the RGB pegboard: _to be decided_.

Customizable, modular 3D-printed pegboard panels with integrated RGB lighting, for storing gaming and work gear (keyboard, controllers, headset, mouse, tools, plants, etc.). Customers design their own panel on our website and add the components they want.

> Build. Organize. Play. Better.

Services: CAD design · Arduino / embedded · 3D printing · maker solutions

## Repository layout

| Folder | Purpose |
|---|---|
| [`components/`](components/) | **Final** printable parts (STL / 3MF / STEP), production-ready |
| [`prototypes/`](prototypes/) | **Prototype** versions of the same parts: work in progress, tests, iterations |
| [`electronics/`](electronics/) | Electrical architecture, schematics, PCB (powered slots, pogo pins, LEDs) |
| [`firmware/`](firmware/) | Code for the brain panel, the panels and the screen modules |
| [`business/`](business/) | Idea and story, pricing and product details, business process |
| [`pal/`](pal/) | **Pal**, the desktop companion robot (sub-project, self-contained: design, mechanical, electronics, firmware, app, business) |

The folders above are for the pegboard. Pal lives entirely in `pal/`.

## Workflow

1. Design/iterate a part in `prototypes/<category>/`.
2. Once print-tested and approved, copy it to `components/<category>/` with the final naming (no `_proto` suffix).
3. Update pricing/weight in [`business/pricing&product details/`](business/pricing&product%20details/).

See the README in each folder for naming conventions.
