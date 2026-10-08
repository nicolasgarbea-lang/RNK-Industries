# NRX app (Pal companion app) (PROPOSAL v0.1)

The in-house app where users manage what Pal reminds them of. Users type in their own to-dos and habits, and Pal reads them out and reminds them.

## Platforms

1. **Desktop (Windows first, then macOS)**: required, because it talks to Pal over USB and runs the voice pipeline. Suggested stack: **Tauri** (small, Rust + web UI) or Electron.
2. **Mobile (later)**: edit to-dos away from the desk. Needs cloud sync.

## Features

| Feature | MVP | Later |
|---|---|---|
| To-do list: add, edit, tick off, due time | ✅ | Recurring tasks, priorities |
| Habits: water (glasses/day), breaks, posture, stretch, custom | ✅ | Streaks, weekly stats |
| Reminder schedule: interval or fixed times, quiet hours | ✅ | Smart timing (not during calls / full-screen games) |
| Pal settings: voice, volume, brightness, wake word on/off | ✅ | Custom faces, personality |
| Voice: "what's on my list?", "add …", "I drank water" | ✅ | Small talk |
| Daily summary read out at PC boot | ✅ | |
| Account + cloud sync | | ✅ |
| Integrations (Google Tasks, Outlook, Todoist) | | ✅ |
| Firmware update for Pal | ✅ | |

## Data model (first draft)

```
Task      { id, title, notes?, due_at?, done_at?, created_at, order }
Habit     { id, name, icon, target_per_day, interval_min?, times[]?, active }
HabitLog  { id, habit_id, at }
Settings  { quiet_hours, volume, brightness, voice, wake_word_enabled }
```

Stored locally (SQLite) in the MVP.

## Pal ↔ app protocol

Transport: **USB serial (CDC)**, one JSON message per line. Wi-Fi later, with the same messages.

| Direction | Message | Meaning |
|---|---|---|
| app → Pal | `{"t":"hello","ver":1}` | App connected, so Pal knows the PC is on |
| Pal → app | `{"t":"info","fw":"0.1.0","id":"…"}` | Pal identity |
| app → Pal | `{"t":"sync","tasks":[…],"habits":[…]}` | Today's list, cached on Pal |
| app → Pal | `{"t":"remind","kind":"habit","id":"water","text":"Time for some water!"}` | Show reminder face + speak |
| Pal → app | `{"t":"ack","id":"water","action":"done\|snooze"}` | Head pat or voice answer |
| Pal → app | `{"t":"audio_start"}` + binary frames + `{"t":"audio_end"}` | Voice request |
| app → Pal | `{"t":"say","audio":"…"}` (stream) | Answer to play |
| app → Pal | `{"t":"face","name":"proud"}` | Show an expression |
| both | `{"t":"ping"}` / `{"t":"pong"}` | Keep-alive, used for PC-gone detection |

Audio uses binary frames (16 kHz, 16-bit mono), not JSON.

## Folder plan

```
app/
  desktop/      Tauri/Electron app (UI + USB link + voice pipeline)
  shared/       Protocol definitions, data model
  mobile/       later
```
