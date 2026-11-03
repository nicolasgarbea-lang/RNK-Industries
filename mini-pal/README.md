# Mini Pal: just the face

> Status: **concept**. Nothing is designed or tested yet. All numbers are proposals.

Mini Pal is Pal's little sibling: **only the head**. It's a small black box with the same cute digital face, and it sits on your desk or shelf. It is mostly decorative, but it does a few small useful things:

- shows the **time**
- shows **today's weather**
- reacts to **notifications** (an icon + a little face reaction)
- has a little **scroll wheel** on the side to flip through widgets

There is no body, mic, speaker or voice, so it is cheaper, simpler and has fewer privacy concerns than [Pal](../pal/README.md).

## Product in one look

| | |
|---|---|
| Size | ~**60 x 46 x 36 mm** (W x H x D), the size of Pal's head (see [mechanical](mechanical/README.md)) |
| Look | Matte black box with chamfered (angled) corners, a black glass front, and a small foot that tilts it back ~10° |
| Face | Same as Pal: two round eyes + a banana-shaped smile, cold white. Shared animations |
| Widgets | The user **picks the widgets** in the phone app (face, clock, weather, calendar, notifications, more later). They **rotate automatically**, with adjustable order and time per widget. Notifications interrupt the rotation |
| Interaction | **Scroll wheel** on the right side (like a watch crown): turn = previous / next widget, press = dismiss notification or pause, long press = Bluetooth pairing. Auto-rotation resumes 30 s after the last turn |
| Connection | **Bluetooth to the NRX phone app.** The phone sends time, weather, calendar and notifications. No PC needed. Wi-Fi only for later extras |
| Sound | A small **chirp** for notifications (volume adjustable, can be muted) |
| Power | USB-C 5 V from any phone charger or PC. No battery |

## How it compares to Pal

| | Mini Pal | Pal |
|---|---|---|
| Body, arms, legs | No | Yes |
| Face screen | Yes (same) | Yes |
| Mic + speaker, voice | No (just a chirp buzzer) | Yes |
| To-dos and habits | Later, as a widget | Full (NRX app) |
| Needs | The NRX phone app (Bluetooth) | The NRX desktop app (USB) |
| Est. electronics cost | **~11 CHF** | ~19 CHF |
| Target price | **29-39 CHF** | 59-89 CHF |

Mini Pal is a good **first product**. It is simpler, it proves the face, the screen, the case finish and the phone app, and its code is reused in Pal.

## Folder layout

| Folder / file | Purpose |
|---|---|
| [`design/`](design/) | Concept images, widget screens (face, clock, weather, calendar, notification) |
| [`mechanical/`](mechanical/README.md) | The box: size, parts, CAD, prints |
| [`electronics/`](electronics/architecture.md) | Electrical architecture and [BOM](electronics/bom.md) |
| [`firmware/`](firmware/README.md) | Code on the ESP32 |
| [`app/`](app/README.md) | The NRX phone app: widgets, notifications, weather, Bluetooth link |
| [`business/`](business/README.md) | Pitch, cost, price |
| [`roadmap.md`](roadmap.md) | Phases, in order |
| [`todo.md`](todo.md) | Everything that needs to be done |
| [`shopping-list.md`](shopping-list.md) | What to buy |

## Decisions

- [x] Screen: **same 2.0" as Pal** (shared parts and face code)
- [x] Notifications come **from the phone** (iPhone via ANCS, Android via the NRX app). See [app](app/README.md#notifications)
- [x] Users **choose their widgets** in the phone app. See [app](app/README.md#widgets)
- [x] **Chirp:** yes, a small buzzer
- [x] Weather comes **through the NRX phone app** (Apple WeatherKit on iPhone, a weather API on Android). It can't be read from the phone's own weather app. See [app](app/README.md#weather-cant-we-just-use-the-phones-weather-app)

## Open questions

- [ ] We now need a **phone app for iPhone + Android**. Who builds it, and in Flutter or React Native?
- [ ] Apple Developer Program (99 USD/year) is needed for the iPhone app and WeatherKit. OK?
- [ ] Which weather source on Android (check price per user)?
- [ ] Colours: black only, or also white?
