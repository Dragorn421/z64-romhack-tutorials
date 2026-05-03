# Viewing game logs

Viewing game logs depends on the emulator you're using.

## ares

In ares (https://ares-emu.net/), viewing the game logs is a built-in feature. Logs are written to standard output (run the emulator from a terminal).

## gopher64

In gopher64 (https://loganmc10.itch.io/gopher64), viewing the game logs is a built-in feature. Logs are written to standard output (run the emulator from a terminal).

## mupen64plus

If you use mupen64plus, this is a built-in feature.

### Rosalie's Mupen GUI

In RMG (https://github.com/Rosalie241/RMG) you can open a window with the emulator logs with `View` > `Log`. Emulator logs include the game logs, prefixed by `[CORE]  [INFO]    IS64: `.

## Project64

If using Project64, you can use a set of scripts to view the game logs: https://github.com/Dragorn421/IS64-logging

Feel free to tell me about other emulators!

# Printing logs to console

Logs are written with `osSyncPrintf` / `PRINTF`, which you can use too. `PRINTF()` is a macro that expands to `osSyncPrintf()` in debug versions (if `DEBUG_FEATURES` is set to 1), and to nothing otherwise.

For colored output, check out `include/terminal.h` (https://github.com/zeldaret/oot/blob/main/include/terminal.h)

Look for `PRINTF` usage in decomp for examples, it's pretty straightforward.

# Printing logs in English

The game prints most log messages in japanese. Decomp provides English translations (that are not part of the base roms) that you can enable in `include/translation.h` (https://github.com/zeldaret/oot/blob/main/include/translation.h) by changing `#define T(jp, en) jp` to `#define T(jp, en) en`.
