# Pal: to-do list

> Everything that needs to be done, grouped by the [roadmap](roadmap.md) phases. Tick items off as you go and put your initials after the ones you take.
> What to buy: [shopping-list.md](shopping-list.md).

## 0. Decisions (do first)

- [ ] Confirm the envelope orientation: 60 W x **90 H** x 60 D, or 60 W x 60 H x **90 D**? ([README](README.md#open-questions))
- [ ] Confirm: local-first desktop app, no server for the MVP
- [ ] Confirm: voice runs on the PC (local), cloud "smart mode" later
- [ ] Final name and logo ("pal" in lowercase?)
- [ ] Decide who owns what: mechanical / electronics + firmware / app / business
- [ ] Order phase 1 parts ([shopping list](shopping-list.md#phase-1-breadboard-proof-45-chf))

## 1. Breadboard proof

- [ ] Set up the toolchain (ESP-IDF or PlatformIO + Arduino-ESP32) and flash a "blink" on the ESP32-S3
- [ ] Wire the 2.0" screen (SPI) and draw a test image
- [ ] Draw the basic face (eyes + banana smile) and add blinking
- [ ] Measure the face animation frame rate (target 30 fps)
- [ ] Wire 1 mic (I2S in), record a few seconds, play it back over USB to check quality
- [ ] Wire the amp + speaker (I2S out) and play a sound
- [ ] Test the 2-mic setup
- [ ] Test the wake word (ESP-SR WakeNet) at 50 cm, 80 cm and with music on
- [ ] Test the capacitive touch pad through 2 mm of PETG
- [ ] Make the mute switch cut the mic power, and check that it really stops the mic
- [ ] Measure current draw (idle, Wi-Fi on, speaker at max) with the USB meter. Check it against USB 2.0's 500 mA
- [ ] Test PC on/off behaviour: does Pal turn off, or does USB stay powered? Implement "PC gone" detection
- [ ] Write down results in `firmware/` and update [electronics/architecture.md](electronics/architecture.md)

## 2. Desktop app MVP

- [ ] Choose the stack (Tauri or Electron) and set up `app/desktop/`
- [ ] Data model + local SQLite storage (tasks, habits, habit logs, settings)
- [ ] UI: to-do list (add, edit, tick off, due time)
- [ ] UI: habits (water glasses/day, breaks, stretch, custom) + reminder schedule
- [ ] UI: Pal settings (volume, brightness, quiet hours, wake word on/off)
- [ ] USB serial link: find Pal, `hello` / `info` / `ping` ([protocol](app/README.md#pal--app-protocol))
- [ ] Send `sync` + `remind`, receive `ack` (done / snooze)
- [ ] Daily summary at PC boot
- [ ] Start with Windows (autostart setting)
- [ ] Firmware update for Pal from the app
- [ ] Installer for Windows

## 3. Enclosure prototypes

- [ ] Measure the real screen module, speaker, dev board and mics with a caliper
- [ ] CAD the head: 60 x 44 x 32 mm, chamfered corners, screen pocket, mic pinholes, inner frame
- [ ] CAD the body: belly, arms leaning back, legs hanging, split line, speaker pocket + vents, USB-C exit
- [ ] Print proto-1 and check the fit of all parts
- [ ] Stability test on a thin (~10 mm) and a thick monitor bezel. Place the ballast
- [ ] Speaker test inside the body (loudness, rattles)
- [ ] Check that the speaker sound does not leak into the mics inside the shell
- [ ] Heat check after 1 h on
- [ ] Finish test: sanding + primer + soft-touch paint. Compare with a resin print
- [ ] Save files as `mechanical/prototypes/pal-<part>_proto-<n>` + notes
- [ ] Promote approved parts to `mechanical/final/`

## 4. Local voice

- [ ] Stream mic audio from Pal to the app (binary frames, 16 kHz)
- [ ] Add local speech-to-text (Whisper / whisper.cpp) to the app. Test speed on an average PC
- [ ] Add local text-to-speech (Piper). Pick Pal's voice
- [ ] Commands: "what's on my list?", "add …", "I drank water", "snooze", "done"
- [ ] Stream the answer audio back to Pal + **Speaking** face
- [ ] Offline fallback: pre-recorded reminder sounds stored on Pal

## 5. Custom PCB

- [ ] Schematic: ESP32-S3-WROOM-1, USB-C (CC resistors + ESD), 3.3 V regulator, MAX98357A, mic + screen connectors, mute switch, touch pad
- [ ] PCB layout sized for the body (+ head board / flex through the neck)
- [ ] Review against the CAD (holes, connector positions)
- [ ] Order 5 sets ([shopping list](shopping-list.md#phase-5-custom-pcb-120-chf-order-later)), assemble, test
- [ ] Update [electronics/bom.md](electronics/bom.md) with real prices

## 6. Design + firmware polish

- [ ] Draw all expressions at 320 x 240 ([design](design/README.md#expressions-to-design-screen-animations)): idle, hello, reminder, listening, speaking, proud, sleepy, muted
- [ ] Reminder icons (water drop, check box, break, stretch)
- [ ] Sounds: boot, reminder, done, snooze
- [ ] Quiet hours + "do not disturb" when a full-screen game or call is running (later)

## 7. Certification + legal

- [ ] Ask 2-3 test labs for a quote: CE (radio/RED, EMC, LVD, RoHS) for Switzerland + EU
- [ ] Use a pre-certified ESP32-S3 module and keep its antenna area clear
- [ ] Privacy statement (nFADP / GDPR): what is recorded, where it goes, mute switch
- [ ] User manual + safety info + CE declaration of conformity
- [ ] Check the WEEE / battery-free disposal rules

## 8. Small batch + business

- [ ] Build 20-50 units for beta testers
- [ ] Collect feedback (form + interviews)
- [ ] Fix the cost per unit and the selling price ([business](business/README.md))
- [ ] Packaging design
- [ ] Product photos / video (real unit on a monitor)
- [ ] Add Pal to the website and the product catalog
