# Basics

## Actor Layout

Open the [actor.c](../custom_actor_base/actor.c) file you just downloaded.

The first line (`#include "actor.h"`) includes [actor.h](../custom_actor_base/actor.h), bringing whatever `actor.h` defines into `actor.c`.

### `actor.h`

Open [actor.h](../custom_actor_base/actor.h).

#### Include guards

<details>

<summary>
The first two lines (`#ifndef ...`, `#define ...`) and the last line (`#endif`) form an include guard.
</summary>

The first two lines

```c
#ifndef _Z_CUSTOMACTOR_H_
#define _Z_CUSTOMACTOR_H_
```

and the last line

```c
#endif
```

form an [include guard](https://en.wikipedia.org/wiki/Include_guard), which is typically used in C to prevent the contents of `actor.h` of being duplicated in case of it being included twice (with `#include`).

</details>

Just don't touch them, and add anything you want to add in `actor.h` between those lines.

#### Include z64hdr

Like `#include "actor.h"` did in `actor.c`, here in `actor.h` the line `#include "z64hdr/oot_debug.h"` brings z64hdr definitions to `actor.h`, and to `actor.c`.

#### CustomActor struct

```c
typedef struct CustomActor {
    Actor actor;
} CustomActor;
```

A [`struct`](https://en.wikipedia.org/wiki/Struct_(C_programming_language)) (structure) defines how to use some memory.

Each actor has its own struct, but they all share the same base struct, `Actor`, which holds generic actor data such as actor id, position, speed...

It is considered good practice in C to put such definitions in header files (`.h`), and include those header files in source files (`.c`), like we do here.

### `actor.c`

Open [actor.c](../custom_actor_base/actor.c) again.

#### Forward declarations

```c
void CustomActor_Init(Actor* thisx, GlobalContext* globalCtx);
void CustomActor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void CustomActor_Update(Actor* thisx, GlobalContext* globalCtx);
void CustomActor_Draw(Actor* thisx, GlobalContext* globalCtx);
```

These are [forward declarations](https://en.wikipedia.org/wiki/Forward_declaration). They indicate that the functions exist and will be defined later.

Explaining what a [function](https://en.wikipedia.org/wiki/Subroutine) is, is too long for this tutorial.

#### Init vars

"Init vars", as they are referred to, ("initialization variables") hold generic settings used when spawning an actor, for example when a scene/room loads.

```c
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
```

If you find the `ActorInit` struct definition in [z64hdr](https://github.com/turpaan64/z64hdr) (hint: it's in [z64actor.h](https://github.com/turpaan64/z64hdr/blob/main/include/z64actor.h)), you can see what each value is for.

##### Actor id and category

`1` is the actor id.

`ACTORCAT_MISC` is the actor category. You may as well only use that one. See the `ActorCategory` enum in `z64actor.h` for a list of categories.

##### Actor Flags

`0x00000030` are the actor flags. It is a [bitfield](https://en.wikipedia.org/wiki/Bit_field), meaning each bit (a 0 or a 1 when written in binary) sets or unsets a property.

For example, `0x00000030` in binary is `0011 0000`. The 5th bit (the right-most `1`) indicates that the actor should always update, and the 6th bit (the left-most `1`) indicates that the actor should always draw.

Some actor flags are documented on [the CloudModding wiki](https://wiki.cloudmodding.com/oot/Actors#Initialization_Variables).

##### Object, struct size

`OBJECT_GAMEPLAY_KEEP` sets the actor's object. An object holds data used by an actor, such as graphics data, collision...

Without going into details (yet), using `OBJECT_GAMEPLAY_KEEP` acts as if the actor didn't use an object.

`sizeof(CustomActor)` indicates how much memory the `CustomActor` struct needs.

##### Init, Destroy, Update, Draw

```c
    (ActorFunc)CustomActor_Init,
    (ActorFunc)CustomActor_Destroy,
    (ActorFunc)CustomActor_Update,
    (ActorFunc)CustomActor_Draw,
```

These tell the engine what functions to call to make the actor perform operations.

* The Init function (here `CustomActor_Init`) is called when the actor spawns (for example on scene/room entry). For example, an actor may load its collision.

* The Destroy function is called when the actor is unloaded (for example when leaving the scene/room). For example, an actor may unload its collision to free memory.

* The Update function is called every frame to make the actor update itself. For example, an actor may move by changing its position.

* The Draw function is called every frame to make the actor draw itself.

Note: Update and Draw are only called every frame that the actor is on camera (not culled), unless some actor flags are set (see actor flags above). This custom actor base sets the flags so that Update and Draw are always run every frame regardless of the actor being culled or not.

#### Function definitions

The four functions Init, Destroy, Update, Draw all take the same arguments and return nothing (`void`).

```c
void CustomActor_Init(CustomActor* this, GlobalContext* globalCtx) {

}
```

The first argument is `CustomActor* this`, a [pointer](https://en.wikipedia.org/wiki/Pointer_(computer_programming)) to the memory used by the custom actor struct.

The second argument `GlobalContext* globalCtx` is a pointer to the structure known as the ["global context"](https://wiki.cloudmodding.com/oot/Global_Context_(Game)). Basically, the global context stores or points to everything the game needs to run.

You can find the definition of the `GlobalContext` struct in [z64.h](https://github.com/turpaan64/z64hdr/blob/main/include/z64.h).

As you can see, Init, Destroy and Update have an empty body (nothing between the curly brackets `{`, `}`). This actor does nothing but drawing.

## Your first actor code

I will be using comments in C to give details. The syntax for comments in C is:

```c
// a single-line comment that ends when the line ends
/* a multi-line comment that ends
whenever you want it to */
```

If you want to tinker with the Draw function (`CustomActor_Draw`) you should only touch the lines with `GfxPrint_SetColor`, `GfxPrint_SetPos`, `GfxPrint_Printf`.

For example, this prints the actor's XYZ coordinates in the middle of the screen:

```c
// opaque yellow
GfxPrint_SetColor(&printer, 255, 255, 0, 255);
// in the middle of the screen vertically
GfxPrint_SetPos(&printer, 1, 10);
// %f for floating point (decimal) values
GfxPrint_Printf(&printer, "I am located at");
// in the middle of next line
GfxPrint_SetPos(&printer, 6, 11);
// %f for floating point (decimal) values
GfxPrint_Printf(&printer, "%f %f %f", this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z);
```

![in-game screen text actor position](images/ingame_screentext_position.png)

As training I would now like you to print a message, in green and near the bottom of the screen, telling how far horizontally the actor is from Link.

The horizontal distance to Link is stored in `this->actor.xzDistToPlayer`. It is a floating point value, so use `%f`. Have fun :)

<details>

<summary>
Click to reveal a solution
</summary>

```c
void CustomActor_Draw(CustomActor* this, GlobalContext* globalCtx) {
    GfxPrint printer;
    Gfx* gfx = globalCtx->state.gfxCtx->polyOpa.p + 1;

    gSPDisplayList(globalCtx->state.gfxCtx->overlay.p++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

	// the actually modified lines v
	GfxPrint_SetColor(&printer, 0, 255, 0, 255);
	GfxPrint_SetPos(&printer, 1, 20);
	GfxPrint_Printf(&printer, "Link is %f units away horizontally", this->actor.xzDistToPlayer);
	// the actually modified lines ^

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    gSPBranchList(globalCtx->state.gfxCtx->polyOpa.p, gfx);
    globalCtx->state.gfxCtx->polyOpa.p = gfx;
}
```

</details>

## The start of something

We will now make the actor kill Link when he gets too close.

With the distance to Link shown on screen, you can decide of a good range to use. Try not killing Link as soon as he spawns in!

Since this isn't about drawing the actor, but about its logic and how it interacts with something else, we will put the relevant code in the update function `CustomActor_Update`.

To kill Link, set his health to 0. Link's health is stored in `gSaveContext.health`.

<details>

<summary>
Click to reveal a solution
</summary>

```c
void CustomActor_Update(CustomActor* this, GlobalContext* globalCtx) {
	// kill Link if he gets 100 units or closer
	if (this->actor.xzDistToPlayer < 100.0f) {
		gSaveContext.health = 0;
	}
}
```

I will write floats (floating point values) as `100.0f`, but it is fine to just write `100` or `100.0`.

<details>

<summary>
The difference is the type of the value.
</summary>

- `100`: integer (`s32`)
- `100.0f`: float (`f32`, simple-precision floating point value)
- `100.0`: double (`f64`, double-precision floating point value)

When comparing two values, they need to be converted to the same type, so using a `f32` value (`100.0f`) to compare against another `f32` value (`this->actor.xzDistToPlayer`) does not require a conversion. That means less instructions in the compiler output.

</details>

</details>

Is Link dying as expected? Now, instead of killing him immediately, we will only damage him if he gets too close.

Link's health is stored in `gSaveContext.health`, in sixteenth of hearts. That means `gSaveContext.health = 16;` sets Link's health to one full heart.

For now, let's make Link loose 1/16th heart per frame he is too close.

<details>

<summary>
Click to reveal a solution
</summary>

```c
void CustomActor_Update(CustomActor* this, GlobalContext* globalCtx) {
	// damage Link if he gets 100 units or closer
	if (this->actor.xzDistToPlayer < 100.0f) {
		/*
		 * the next condition prevents setting a negative health value.
		 * negative health may be fine but it is good practice to avoid weird scenarios,
		 * you never know when it may matter and cause a crash!
		 */
		if (gSaveContext.health > 0) {
			gSaveContext.health--;
		}
	}
}
```

</details>

The game runs at 20 [fps](https://en.wikipedia.org/wiki/Frame_rate) (frames per second) and the game keeps track of health in 1/16ths of hearts, so Link is damaged at a rate of around one heart every second, but it looks like his life is being drained.

I would instead like the actor to damage Link by one full heart (at once) when he gets too close, but only once every few seconds.

So we need the actor to "remember" not to damage Link for some time after damaging him. The actor instance (the `CustomActor* this` argument) is the right place to store that kind of data.

Open `actor.h`, where the definition of the `CustomActor` struct is. ([see above](#CustomActor-struct))

The struct definition is minimal at the moment:

```c
typedef struct CustomActor {
    Actor actor;
} CustomActor;
```

**The `Actor actor;` member must always be the first (top-most) member in the struct definition.** If it isn't, the game may (not immediately) crash and your actor is more than likely to not behave as expected.

There are several ways to implement the wait-after-damaging-Link we want to achieve, I will be using a timer that ticks down to 0.

With all of that in mind, let's add a member *after* the `actor` member, with an appropriate name.

```c
typedef struct CustomActor {
    Actor actor;
	s32 dontHitPlayerTimer; // when above zero, do not damage Link
} CustomActor;
```

We can now make use of this new member in our code. Back to `CustomActor_Update` in `actor.c`:

```c
void CustomActor_Update(CustomActor* this, GlobalContext* globalCtx) {
	// tick down to 0
	if (this->dontHitPlayerTimer > 0) {
		dontHitPlayerTimer--;
	}
	// damage Link if he gets 100 units or closer
	if (this->actor.xzDistToPlayer < 100.0f) {
		if (this->dontHitPlayerTimer == 0) {
			if (gSaveContext.health > 0) {
				// damage by a full heart
				gSaveContext.health -= 16;
				// do not damage Link again for 60 frames (3 seconds)
				this->dontHitPlayerTimer = 60; 
			}
		}
	}
}
```

Link is now damaged by a full heart every three seconds when he is too close to the actor. Pretty cool, right?

To be fancier, you could change the text printed by `CustomActor_Draw`, for example draw red text with the remaining time before damaging Link again when Link is too close (use `%d` for integers like `this->dontHitPlayerTimer`), and green text with Link's distance when he is far enough.

Now that we wrote the basics of the actor's logic, it is time to worry about how it looks and make it actually appear in game, instead of just text on the screen.
