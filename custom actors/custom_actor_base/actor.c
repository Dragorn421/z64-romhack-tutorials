#include "actor.h"

#define FLAGS 0x00000000

#define THIS ((CustomActor*)thisx)

void CustomActor_Init(Actor* thisx, GlobalContext* globalCtx);
void CustomActor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void CustomActor_Update(Actor* thisx, GlobalContext* globalCtx);
void CustomActor_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Box_InitVars = {
    1,
    ACTORCAT_MISC,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    0,
    sizeof(CustomActor),
    (ActorFunc)CustomActor_Init,
    (ActorFunc)CustomActor_Destroy,
    (ActorFunc)CustomActor_Update,
    (ActorFunc)CustomActor_Draw,
};

void CustomActor_Init(Actor* thisx, GlobalContext* globalCtx) {

}

void CustomActor_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    
}

void CustomActor_Update(Actor* thisx, GlobalContext* globalCtx) {
    
}

void CustomActor_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GfxPrint printer;
    Gfx* gfx = globalCtx->state.gfxCtx->polyOpa.p + 1;

    gSPDisplayList(globalCtx->state.gfxCtx->overlay.p++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    GfxPrint_SetColor(&printer, 255, 0, 0, 255);
    GfxPrint_SetPos(&printer, 1, 1);
    GfxPrint_Printf(&printer, "It works! I am loaded at 0x%X", thisx);

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    gSPBranchList(globalCtx->state.gfxCtx->polyOpa.p, gfx);
    globalCtx->state.gfxCtx->polyOpa.p = gfx;
}
