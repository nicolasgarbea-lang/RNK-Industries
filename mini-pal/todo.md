# Mini Pal: to-do list

> Grouped by the [roadmap](roadmap.md) phases. Put your initials after the tasks you take. What to buy: [shopping-list.md](shopping-list.md).

## 0. Decisions

- [x] Screen: same 2.0" as Pal
- [x] Notifications from the phone, widgets chosen in the app, chirp: yes
- [ ] Phone app stack (Flutter or React Native) and who builds it
- [ ] Apple Developer Program account (99 USD/year)
- [ ] Weather source for Android
- [ ] Launch Mini Pal before Pal?
- [ ] Order the missing parts ([shopping list](shopping-list.md))

## 1. Breadboard proof

- [ ] Flash an ESP32-C3 Super Mini
- [ ] Wire the 2.0" screen and draw the face (eyes + banana smile)
- [ ] Face at 20 fps with partial redraws (measure it)
- [ ] BLE link with a phone (test app such as nRF Connect): send the time
- [ ] Read iPhone notifications over ANCS
- [ ] Chirp on the buzzer (volume levels)
- [ ] Scroll wheel (KY-040): count steps reliably, press + long press
- [ ] Light sensor: auto-dim and night mode
- [ ] Check RAM use on the C3. If it's too tight, try the ESP32-S3

## 2. Firmware MVP

- [ ] Put the face engine in a shared library (used by Pal too)
- [ ] Widgets: face, clock, weather, calendar, notification, night
- [ ] Automatic widget rotation (order and time set from the app, transitions)
- [ ] Notifications interrupt the rotation, then it continues
- [ ] Wheel: turn = previous / next widget, press = dismiss / pause, long press = pairing
- [ ] Weather mood (sunny = happy face, rain = sleepy…)
- [ ] BLE messages: time, widgets, weather, event, notify, settings ([draft](app/README.md#ble-messages-first-draft))
- [ ] Firmware update through the phone app
- [ ] Keep working when the phone is away (keep the last data, show a small icon)

## 2b. NRX phone app MVP

- [ ] Set up the project (Flutter or React Native) + BLE plugin
- [ ] Pairing screen
- [ ] Widget picker: choose, reorder, set duration
- [ ] Weather: Apple WeatherKit (iPhone), weather API (Android), every 30-60 min
- [ ] Calendar: next event (with permission)
- [ ] Notification filters (which apps may notify Mini Pal)
- [ ] Android: forward notifications (notification access permission)
- [ ] Settings: brightness, night hours, chirp volume
- [ ] Firmware update for Mini Pal
- [ ] Test builds: TestFlight (iPhone) + Google Play internal test

## 3. Box prototypes

- [ ] Measure the screen module and boards
- [ ] CAD the box (60 x 46 x 32 mm, chamfered) + foot
- [ ] Print proto-1, check bezel, fit, wheel slot, light window
- [ ] Stability with the USB-C cable plugged in
- [ ] Heat check after a few hours
- [ ] Finish test (same process as Pal)

## 4. Custom PCB

- [ ] Schematic: ESP32-C3 module, USB-C, LDO, screen FPC, side encoder wheel, light sensor, chirp buzzer
- [ ] Layout to fit behind the screen
- [ ] Order 5, assemble, test
- [ ] Update the [BOM](electronics/bom.md) with real prices

## 5. Certification + legal

- [ ] Ask the test lab if Mini Pal and Pal can share testing
- [ ] Weather licence (WeatherKit terms + attribution, Android source)
- [ ] Privacy policy for the app (notifications, calendar and location stay on the phone and device)
- [ ] App Store + Google Play review
- [ ] Manual + CE declaration

## 6. Small batch

- [ ] Build 20-50 units, collect feedback
- [ ] Final price, packaging, photos
- [ ] Add Mini Pal to the website
