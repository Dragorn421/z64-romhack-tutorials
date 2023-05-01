# Debugging in general

## Game logs

If you use Project64, you can use a set of scripts to view the game logs: https://github.com/Dragorn421/IS64-logging

If you use mupen64plus, this is a built-in feature.

In simple64 (https://simple64.github.io/), you can open the relevant window in `Emulation` > `View Log`.

In ares (https://ares-emu.net/), it is a built-in feature. Logs are written to standard output (run the emulator from a terminal).

Feel free to tell me about other emulators!

## Project64 Debugger

The Project64 emulator has the best debugging tools around (if you know of similar tools in another emulator, let me know!)

Its debugger has documentation here: https://hack64.net/docs/pj64d/
(source repo https://github.com/shygoo/pj64d-docs)

Project64 has a Javascript scripting API: https://htmlpreview.github.io/?https://github.com/project64/project64/blob/develop/JS-API-Documentation.html

# Debugging when writing code

## Printing text on screen

If you use decomp (https://github.com/zeldaret/oot) or z64hdr (https://github.com/z64tools/z64hdr),
you can print text on the screen.

For example the following code:

<details>

```c
GfxPrint printer;
Gfx* gfx;

OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

gfx = POLY_OPA_DISP + 1;
gSPDisplayList(OVERLAY_DISP++, gfx);

GfxPrint_Init(&printer);
GfxPrint_Open(&printer, gfx);

GfxPrint_SetColor(&printer, 255, 0, 255, 255);
GfxPrint_SetPos(&printer, 10, 10);
GfxPrint_Printf(&printer, "Hello");

gfx = GfxPrint_Close(&printer);
GfxPrint_Destroy(&printer);

gSPEndDisplayList(gfx++);
gSPBranchList(POLY_OPA_DISP, gfx);
POLY_OPA_DISP = gfx;

CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
```

</details>

This example code is explained in details here:

<details>

```c
// with explanation comments
GfxPrint printer;
Gfx* gfx;

// OPEN_DISPS/CLOSE_DISPS is a macro providing access to the POLY_OPA_DISP and OVERLAY_DISP macro
// (which would otherwise be equivalently accessed like `play->state.gfxCtx->polyOpa.p`/`...->overlay.p`)
// the point is to make debugging easier in case the game crashes (see Tharo's GBD)
OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

// the dlist will be written in the opa buffer because that buffer is larger,
// but executed from the overlay buffer (overlay draws last, for example the hud is drawn to overlay)
gfx = POLY_OPA_DISP + 1;
gSPDisplayList(OVERLAY_DISP++, gfx);

// initialize GfxPrint struct
GfxPrint_Init(&printer);
GfxPrint_Open(&printer, gfx);

// set color to opaque pink
GfxPrint_SetColor(&printer, 255, 0, 255, 255);
// set position to somewhere near screen center
GfxPrint_SetPos(&printer, 10, 10);
// write Hello at previously set position with previously set color
GfxPrint_Printf(&printer, "Hello");

// end of text printing
gfx = GfxPrint_Close(&printer);
GfxPrint_Destroy(&printer);

gSPEndDisplayList(gfx++);
// make the opa dlist jump over the part that will be executed as part of overlay
gSPBranchList(POLY_OPA_DISP, gfx);
POLY_OPA_DISP = gfx;

CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
```

(note this assumes the current function has `PlayState* play` either as a variable or an argument, which is usually the case)

</details>

This example code achieves:

<details>

![](https://cdn.discordapp.com/attachments/915273929369731173/924577222000508948/unknown.png)

(code put at the end of `Play_Draw` for this screenshot, with `PlayState* play = this;`)

</details>

## Printing logs to console

You can view [Game logs](#game-logs), see above.

Logs are written with `osSyncPrintf`, which you can use too.

For colored output, check out `include/vt.h` (https://github.com/zeldaret/oot/blob/bd4912a1bd62a4ac509e2dacd836708d527d7ad8/include/vt.h)

Look for `osSyncPrintf` usage in decomp for examples, it's pretty straightforward.

## Remote Debugging

Only with decomp.

glank has a branch for remote debugging.

Documentation: https://github.com/glankk/oot/blob/rdb/docs/rdb.md

Demonstration with VSCode + Everdrive:
https://cdn.discordapp.com/attachments/718616443834335293/947665569304440842/rdb.mp4

glank also provides a custom build of Project64 for this remote debugging. See the documentation linked above.
