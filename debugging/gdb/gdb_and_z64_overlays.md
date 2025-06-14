# GDB and z64 overlays

You will probably be interested in debugging code inside z64 overlays, such as most actors. These pieces of code are loaded at arbitrary locations in memory, so we need specific handling to tell gdb about where each is loaded.

## Download the script

You may use the script hosted in this repo to load z64 overlays into gdb: [`gdb_load_z64overlay.py`](gdb_load_z64overlay.py)

Note: This script does not currently support overlays made up of multiple object files.

## Run the script in gdb

Save the script somewhere. The simplest location is inside your oot repo.

You can run a script with the gdb command `source path/to/script.py`. For example `source gdb_load_z64overlay.py` if you ran gdb in the same folder as `gdb_load_z64overlay.py` is in.

The script can be used in two modes: "auto" and "manual". The default is "manual" mode.

## manual mode

After loading the script, you need to run `ovl ...` to load an overlay before using its symbols (e.g. to set a breakpoint).

For example run `ovl ACTOR_OBJ_BOMBIWA` in Hyrule Field before adding a breakpoint like `b ObjBombiwa_Update`.

The overlays that can be loaded are:

- Actors: `ovl ACTOR_...`
- Gamestates: `ovl GAMESTATE_...`
- Effects: `ovl EFFECT_...`
- The pause menu: `ovl PAUSE` or `ovl KALEIDO` or `ovl KALEIDO_SCOPE`

## auto mode

Execute `ovl auto on`, or change `AUTOLOAD_ENABLED_BY_DEFAULT` in the script, to use auto mode. Disable with `ovl auto off`.

You want to then load a new scene for the script to catch the z64 overlays loading and load them in gdb.

For example run `ovl auto on`, then load Hyrule Field, then add a breakpoint like `b ObjBombiwa_Update`.

Note: using auto mode has the disadvantage of being slow.

## Auto-load the script on gdb startup

To have gdb auto-load the script instead of needing to `source` it every time, you need the following:

In the oot directory, create a `.gdbinit` file with the following contents:

```
define target hookpost-remote
    source gdb_load_z64overlay.py
end
```

And in your home directory, create `~/.config/gdb/gdbinit` with the following contents:

```
add-auto-load-safe-path path/to/oot/.gdbinit
```

where `path/to/oot/` is your own path to the oot directory.
