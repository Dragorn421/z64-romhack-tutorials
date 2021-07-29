#include "actor.h"

void CustomActor_Init(CustomActor* this, GlobalContext* globalCtx);
void CustomActor_Destroy(CustomActor* this, GlobalContext* globalCtx);
void CustomActor_Update(CustomActor* this, GlobalContext* globalCtx);
void CustomActor_Draw(CustomActor* this, GlobalContext* globalCtx);

const ActorInit initvars = {
    1,
    ACTORCAT_MISC,
    0x00000030,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(CustomActor),
    (ActorFunc)CustomActor_Init,
    (ActorFunc)CustomActor_Destroy,
    (ActorFunc)CustomActor_Update,
    (ActorFunc)CustomActor_Draw,
};

void CustomActor_Init(CustomActor* this, GlobalContext* globalCtx) {

}

void CustomActor_Destroy(CustomActor* this, GlobalContext* globalCtx) {
    
}

void CustomActor_Update(CustomActor* this, GlobalContext* globalCtx) {
    
}

void CustomActor_Draw(CustomActor* this, GlobalContext* globalCtx) {
    GfxPrint printer;
    Gfx* gfx = globalCtx->state.gfxCtx->polyOpa.p + 1;

    gSPDisplayList(globalCtx->state.gfxCtx->overlay.p++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    /*
    GfxPrint_SetColor takes r, g, b, a (red, green, blue, alpha)
    This uses r=255, g=0, b=0, a=255
    So it is red, and opaque (0 alpha is transparent, 255 alpha is opaque)
    */
    GfxPrint_SetColor(&printer, 255, 0, 0, 255);
    /*
    GfxPrint_SetPos takes x, y
    Coordinates relative to top left of the screen
    */
    GfxPrint_SetPos(&printer, 1, 1);
    /*
    GfxPrint_Printf takes a format (a string) with zero or more "%*" parts
    Each %* is replaced by the value passed in following arguments.
    For example here %X uses the value of this
        (this is a pointer, so that is the address in memory of the custom actor struct)
    %X means to format the value as a hexadecimal integer.
    */
    GfxPrint_Printf(&printer, "It works! I am loaded at 0x%X", this);

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    gSPBranchList(globalCtx->state.gfxCtx->polyOpa.p, gfx);
    globalCtx->state.gfxCtx->polyOpa.p = gfx;
}
