
## Printing text on screen

If you use decomp (https://github.com/zeldaret/oot) or z64hdr (https://github.com/z64tools/z64hdr) (for example in z64rom),
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
