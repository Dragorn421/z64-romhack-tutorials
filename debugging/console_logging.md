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

Logs are written with `osSyncPrintf`, which you can use too.

For colored output, check out `include/terminal.h` (https://github.com/zeldaret/oot/blob/1f9c28f370d73268981fd8a42f9c6ac15b560a1a/include/terminal.h)

Look for `osSyncPrintf` usage in decomp for examples, it's pretty straightforward.
