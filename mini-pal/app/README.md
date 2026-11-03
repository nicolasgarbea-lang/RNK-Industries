# Mini Pal: phone app (PROPOSAL v0.2)

Mini Pal is driven by the **NRX phone app** (iPhone + Android). The phone is the hub: it pairs with Mini Pal over **Bluetooth (BLE)** and sends everything it needs.

```
 [Phone: NRX app] ── BLE ──> [Mini Pal]
   ├─ widget setup (which widgets, order, duration)
   ├─ time sync
   ├─ weather (fetched by the app, see below)
   └─ notifications (from the phone)
```

**Why BLE-first:** setup is just "pair with the app", with no Wi-Fi passwords or hotspot. Mini Pal keeps time on its own between syncs. Wi-Fi (already built into the ESP32-C3) stays available later for firmware updates or for working without the phone.

Stack suggestion: **Flutter** or **React Native** with a BLE plugin: one codebase for iPhone and Android. The same app can later also manage Pal.

## Widgets

The user builds their own rotation in the app: pick widgets, drag them into order, set how long each one shows.

| Widget | Data from | MVP? |
|---|---|---|
| Face (idle) | Mini Pal itself | ✅ |
| Clock + date | Phone time sync | ✅ |
| Weather today | Phone app (see below) | ✅ |
| Next calendar event | Phone calendar (with permission) | ✅ |
| Notifications | Phone (see below) | ✅ |
| Timer / pomodoro | Started from the app or by tapping Mini Pal | Later |
| Phone battery | Phone | Later |
| Habits / to-dos | NRX app (shared with Pal) | Later |
| Countdown (birthday, holiday…) | App | Later |
| Quote / message of the day | App | Later |
| Stocks / crypto prices, sports scores | Internet via app | Later, maybe |

Each widget is a small screen layout in the firmware. The app only sends **data + configuration**, so adding widgets later is a firmware + app update.

## Notifications

| Phone | How | Phone app needed? |
|---|---|---|
| **iPhone** | iOS shares notifications with paired Bluetooth devices (Apple **ANCS**, the same mechanism smartwatches use). The ESP32 can read them | Only for setup and filters |
| **Android** | The NRX app reads notifications (Android "notification access" permission) and forwards them | Yes, must run in the background |

In the app, the user chooses **which apps** may notify Mini Pal (e.g. WhatsApp, Discord, Calendar), so it doesn't chirp for everything. Each notification shows an icon + short text + a face reaction + an optional **chirp**.

## Weather: "can't we just use the phone's weather app?"

**Not directly.** Apps on iPhone and Android are sealed off from each other, so no app can read what the Apple/Google weather app shows. But our own app can **fetch the weather itself** and pass it on:

| Phone | Weather source | Cost / licence |
|---|---|---|
| **iPhone** | **Apple WeatherKit**, the same data as Apple's Weather app | Included with the Apple Developer Program (99 USD/year) up to a large monthly call quota. Licensed for commercial apps; the Apple Weather attribution must be shown (check current terms) |
| **Android** | A weather API called from the app: Open-Meteo (commercial plan), MeteoSwiss open data (CH only) or similar | Check price per user |

The app fetches the forecast every 30-60 min for the phone's location and sends a compact summary to Mini Pal (icon, temperature, min/max, rain chance).

## BLE messages (first draft)

| Direction | Message | Meaning |
|---|---|---|
| app → Mini Pal | `time` | Current time + time zone |
| app → Mini Pal | `widgets [{id, seconds}, …]` | Rotation order and durations |
| app → Mini Pal | `weather {icon, t, tmin, tmax, rain}` | Today's weather |
| app → Mini Pal | `event {title, start}` | Next calendar event |
| app → Mini Pal | `notify {app, icon, text, chirp}` | Notification (Android; iPhone uses ANCS directly) |
| app → Mini Pal | `settings {brightness, night, chirp_volume}` | Settings |
| Mini Pal → app | `input {action}` | Wheel pressed or turned (e.g. dismiss a notification) |
