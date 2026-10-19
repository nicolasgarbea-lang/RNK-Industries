# Pal: roadmap (PROPOSAL v0.1)

> What we need to make Pal feasible, in order. Durations are rough guesses.

## Proposed decisions

| Topic | Proposal | Why |
|---|---|---|
| App hosting | **Local-first desktop app, no server for the MVP.** Data stays on the user's PC. Optional cloud sync later (for a phone app) | No server costs, no accounts, no security/privacy burden at launch, and Pal keeps working if our servers are down |
| Voice | **Runs on the user's PC** (local speech-to-text, e.g. Whisper, and text-to-speech, e.g. Piper), with simple commands. An optional cloud "smart mode" later, as a paid add-on | Cloud AI costs money for every user every month; local voice is free and private |
| Integrations | Import from Google Tasks / Outlook / Todoist later | Users don't have to switch to-do apps |

## Phases

| # | Phase | Goal / done when | Est. |
|---|---|---|---|
| 1 | **Breadboard proof** | ESP32-S3 + 2.0" screen + mic + amp + speaker on a breadboard ([BOM](electronics/bom.md), ~25 CHF). Face animation is smooth, "Hey Pal" works at 50-80 cm, the speaker is loud enough | 2-4 weeks |
| 2 | **Desktop app MVP** (can run in parallel with 3) | Windows app: to-dos, habits, reminder times, Pal settings. Talks to Pal over USB ([protocol](app/README.md#pal--app-protocol)). Data stored locally | 4-8 weeks |
| 3 | **Enclosure prototypes** | CAD + print iterations until it looks like the [concept](design/pal-concept-sheet_v1.webp): seamless matte black finish, sits stably on a thin monitor bezel, ballast placed | 4-8 weeks |
| 4 | **Local voice** | Speech-to-text and text-to-speech run in the desktop app. Commands: "what's on my list?", "add …", "I drank water", "snooze" | 3-6 weeks |
| 5 | **Custom PCB** | Main board + head board sized for the body. Power budget measured (USB 2.0 = 500 mA) | 4-6 weeks |
| 6 | **Certification + legal** | CE marking (radio, EMC, RoHS) for Switzerland/EU, using a pre-certified ESP32 module. Privacy rules (nFADP / GDPR) because of the microphone. Budget: a few thousand CHF for testing | 1-3 months |
| 7 | **Small batch** | 20-50 units for friends/beta testers, collect feedback, fix the price | – |

## Later

- Account + cloud sync, phone app
- Cloud "smart mode" voice (subscription)
- To-do app integrations
- Pegboard mount for Pal (fits the NRX pegboard system)

## Biggest risks

1. **Enclosure finish and balance:** seamless matte black is hard with FDM printing, and the heavy head has to balance on a thin bezel.
2. **Voice quality on the PC:** local models must run well on an average office PC.
3. **Certification cost and time:** plan the budget early.
