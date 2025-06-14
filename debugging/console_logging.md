# Viewing game logs

Viewing game logs depends on the emulator you're using.

## ares

In ares (https://ares-emu.net/), viewing the game logs is a built-in feature. Logs are written to standard output (run the emulator from a terminal).

Ares' "homebrew mode" must be enabled to view the logs. Otherwise you will only get a warning such as:

```
[unhandled] [PI::busWrite] attempt to write to ISViewer: enable homebrew mode in settings to enable ISViewer emulation
```

To enable homebrew mode, go to `Settings` > `Options` and check `Homebrew Development Mode`.

## mupen64plus

If you use mupen64plus, this is a built-in feature.

## Project64

If using Project64, you can use a set of scripts to view the game logs: https://github.com/Dragorn421/IS64-logging

## simple64

In simple64 (https://simple64.github.io/), you can open the relevant window in `Emulation` > `View Log`.

Feel free to tell me about other emulators!

# Printing logs to console

Logs are written with `osSyncPrintf` / `PRINTF`, which you can use too. `PRINTF()` is a macro that expands to `osSyncPrintf()` in debug versions (if `DEBUG_FEATURES` is set to 1), and to nothing otherwise.

For colored output, check out `include/terminal.h` (https://github.com/zeldaret/oot/blob/8a823a7ad24d25d5ebc390e7436e6859227a0ace/include/terminal.h)

Look for `PRINTF` usage in decomp for examples, it's pretty straightforward.

# Printing logs in English

The game prints most log messages in japanese. Decomp provides English translations (that are not part of the base roms) that you can enable in `include/translation.h` (https://github.com/zeldaret/oot/blob/8a823a7ad24d25d5ebc390e7436e6859227a0ace/include/translation.h) by changing `#define T(jp, en) jp` to `#define T(jp, en) en`.
