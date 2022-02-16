# Game main loop

## The "code" file

The "code" file, often just called "code", contains most of the game's main code. Non-exhaustive list of what is handled by code in the "code" file: audio, graphics utilities, maths utilities, map loading, collision, camera, cutscenes, animation utilities, crash debugger.

## Game main loop 1/2

The [`Graph_ThreadEntry`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/graph.c#L399) function contains the game's main loop.

There actually are two loops, the second inside the first.

The first loop loops over game states.

The second loop executes the current game state's main function.

## The different game states

The game can be in different "game states".

The most important game state is the [`Gameplay`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/z_play.c#L185) one, also known as "global" ("global context") or "play state". It is used to load maps, control Link, play cutscenes and so on.

The file select menu is also its own game state ([`FileChoose`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/overlays/gamestates/ovl_file_choose/z_file_choose.c#L1860), "ovl_file_choose" file).

The map select menu (a debug feature, for quickly warping to various maps) is also its own game state ([`Select`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/overlays/gamestates/ovl_select/z_select.c#L715), "ovl_select" file).

Other game states play a minor role. Game states are listed in [`gGameStateOverlayTable`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/z_game_dlftbls.c#L11).

On retail versions (non-Debug), the [`Title`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/overlays/gamestates/ovl_title/z_title.c#L155) state ("ovl_title" file) is responsible for drawing the N64 logo when the game starts, but it only lasts a frame in the Debug ROM.

The remaining states only serve as transitions to other states.

There are also two unused game states (not in the game state table): [`PreNMI`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/z_prenmi.c) and [`Sample`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/z_sample.c).

## Game states

Game states have three main functions: init, main, destroy.

- The init function is called once before the state starts running.
- The main function is called over and over until the state stops running, typically once per frame.
- The destroy function is called once when the state stops running.

Some game states have their code not in the "code" file but in their own file instead, then the file containing their code is loaded from ROM to RAM when needed and unloaded when no longer needed.

## Game main loop 2/2 (Advanced)

Back to the two loops in [`Graph_ThreadEntry`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/graph.c#L399).

Each game state is run by calling its main function over and over (inner loop). The state may stop running, by setting [`GameState#running`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/include/z64.h#L1058) to `false`.

The next game state to run is determined by the function [`GameState#init`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/include/z64.h#L1053) is set to. (make sure to look at `Graph_GetNextGameState` if you want to mess with game states)

The outer loop keeps switching to the next game state, whenever the previous game state stops running.

## Game state sequence after boot (Advanced)

The first game state to run when the game boots is [`TitleSetup`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/title_setup.c#L13). Mainly, it switches to the [`Title`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/overlays/gamestates/ovl_title/z_title.c#L155) state, which draws the N64 logo in retail versions.

`Title` then switches to the [`Opening`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/overlays/gamestates/ovl_opening/z_opening.c#L33) state ("ovl_opening" file), which switches to the `Gameplay` state and makes it load the title screen (with the cutscene in Hyrule Field and the game logo).

When the player does the adequate inputs on the title screen, the game state eventually switches to `FileChoose` (file selection menu).

Then when a file is loaded, if it is file 1 and on a Debug ROM the `Select` game state (map select) is loaded. When a map is picked, it then switches to the `Gameplay` state with that specific map.

Otherwise (not file 1 or not a Debug ROM), the `Gameplay` state is loaded to a map that depends on the file.

When the map changes (scene transitions), the `Gameplay` state switches to `Gameplay` (it stops running and the next state, also `Gameplay`, starts with another map).

## The `Gameplay` state

Again, the most important state (almost the only one that matters) is `Gameplay`. 

Its init function [`Gameplay_Init`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/z_play.c#L185) does a lot, including loading the map.

The heart of the game lies in the `Gameplay` state's main function [`Gameplay_Main`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/code/z_play.c#L1321). This function calls `Gameplay_Update` then `Gameplay_Draw`.

`Gameplay_Update` will update and compute data such as animations, player and NPCs movements, camera movement, cutscene and dialogue progress, collision, physics simulation...

`Gameplay_Draw` will draw the skybox, the map, Link, NPCs, props... without performing logic.
