# Segmented Addresses

Addresses of the form `0xSSYYYYYY` are called segmented addresses.

They are also called segment offsets, segmented offsets, segment addresses...

With `SS` being the "segment"

And `YYYYYY` being the "offset"

The game can handle 16 segments, from 0x00 to 0x0F. Each segment corresponds to a base ram address.

When resolving a segmented address to a ram address, the offset `YYYYYY` gets added to the base ram address corresponding to the segment `SS`.

For example a segmented address may be `0x060009E0`.

In the `ObjBombiwa` actor (bombable rock), because in that actor's context segment 6 points to the bombiwa object, `0x060009E0` is the segmented address corresponding to the bombiwa display list inside the bombiwa object.

# More in-depth

The CPU and the RSP each maintain their own segment to base ram address associations.

When mentioning the RSP here, it is assumed the context is about something like F3DZEX2 microcode. It may or may not apply to other microcodes such as jpeg decoding, audio tasks or S2DEX.

## CPU

On the cpu side resolving a segmented address to a RAM address is done with the `SEGMENTED_TO_VIRTUAL` macro:

https://github.com/zeldaret/oot/blob/251d90301c2bbaaf2c46362986a321fc70712ecc/include/macros.h#L9

```c
#define PHYSICAL_TO_VIRTUAL(addr) (void*)((u32)(addr) + 0x80000000)
#define VIRTUAL_TO_PHYSICAL(addr) (u32)((u8*)(addr) - 0x80000000)
#define SEGMENTED_TO_VIRTUAL(addr) PHYSICAL_TO_VIRTUAL(gSegments[SEGMENT_NUMBER(addr)] + SEGMENT_OFFSET(addr))
```

The segment to base ram address associations are stored in the `gSegments` array.

Changing what a segment points to is done by accessing that array directly, for example:

```c
gSegments[4] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[globalCtx->objectCtx.mainKeepIndex].segment);
```

Note `gSegments` holds physical addresses. `SEGMENTED_TO_VIRTUAL` involves `PHYSICAL_TO_VIRTUAL`.

## RSP

On the rsp side, resolving segmented addresses is done on the rsp, so there's nothing to do in code that runs on the cpu. Segmented addresses are passed as is to the rsp.

Changing what segments point to is done through `gSPSegment`/`gsSPSegment` commands.

For example:

```c
gSPSegment(POLY_OPA_DISP++, 0x04, globalCtx->objectCtx.status[globalCtx->objectCtx.mainKeepIndex].segment);
```

Note `g(s)SPSegment` takes in virtual addresses.

## Example

When drawing actors, segment 6 is changed to point to where in ram the actor's object is loaded.

In `Actor_Draw` https://github.com/zeldaret/oot/blob/251d90301c2bbaaf2c46362986a321fc70712ecc/src/code/z_actor.c#L2170

Segment 6 is set on the cpu side through `Actor_SetObjectDependency`:

```c
Actor_SetObjectDependency(globalCtx, actor);
```

```c
void Actor_SetObjectDependency(GlobalContext* globalCtx, Actor* actor) {
    gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[actor->objBankIndex].segment);
}
```

Segment 6 is set on the rsp side with:

```c
    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);
    gSPSegment(POLY_XLU_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);
```

On both the opa and xlu buffers since actors usually use either or both.

An actor's object being loaded at the ram address denoted by `globalCtx->objectCtx.status[actor->objBankIndex].segment`.

So segment 6, also known as the "current object segment", changes for each actor drawn, and allows each actor to reference the object's data through segmented addresses that look like for example `0x06004210`.

## Gotchas

### Physical on cpu, virtual on rsp

On the cpu, `gSegments` holds physical addresses, while on the rsp `g(s)SPSegment` takes virtual addresses.

### Segment 0

Segment 0 should always point to a base ram address of 0, both on the cpu and on the rsp.

Otherwise resolving an address that is not segmented such as `SEGMENTED_TO_VIRTUAL(VIRTUAL_TO_PHYSICAL(0x80123456))` would not result in the initial address (here `0x80123456`).

Indeed the segment bits are only bits 27..24, not bits 31..28, as was first explained above for simplicity.

See for example the `SEGMENT_NUMBER` macro: `#define SEGMENT_NUMBER(a)   (((u32)(a) << 4) >> 28)`

Or the F3DEX2 disassembly by wiseguy:

https://github.com/Mr-Wiseguy/f3dex2/blob/29878bee1a66a1815af25f697eae5c9431de6cee/f3dex2.s#L603

`andi    $11, $11, 0x3C` only keeps the lower 4 bits of the "segment byte".

## Relevant manual parts

Programming Manual: *10.2 Mixing CPU and SP Data* http://n64devkit.square7.ch/pro-man/pro10/10-02.htm

Programming Manual: *11.1.2 Segmented Memory and the RSP Memory Map* http://n64devkit.square7.ch/pro-man/pro11/11-01.htm#02

Index: *16 segment base address* http://n64devkit.square7.ch/keywords/index/data/system.htm#16%20segment%20base%20address

Index: *segment address* http://n64devkit.square7.ch/keywords/index/data/system.htm#segment%20address

Function reference: `gSPSegment` http://n64devkit.square7.ch/n64man/gsp/gSPSegment.htm
