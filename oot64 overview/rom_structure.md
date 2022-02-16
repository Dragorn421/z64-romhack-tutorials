# The ROM

A ROM is a single file, usually .z64, .n64 or .v64. [Read more](http://n64dev.org/romformats.html)

To set up decomp, a rom is needed to be put into the oot directory as `baserom_original.z64`, `.n64` or `.v64`.
It is then processed to a `baserom.z64` rom which md5 must be `f0b7f35375f9cc8ca1b2d59d78e35405`.
The size of this `baserom.z64` is 54 MB.

## The file system

A ROM contains several files (1533 files in PAL MQ Debug OoT64), just like an archive (for example a `.zip`).

Each file takes a portion of the ROM.

For example the `code` file spans from 0xA94000 to 0xBCEF30 (start inclusive, end exclusive), as can be seen when building decomp by looking in the map file `build/z64.map` for `_codeSegmentRomStart` and `_codeSegmentRomEnd`.

In the oot decomp repo, the file names come from strings present in the Debug ROM. (specifically, from `sDmaMgrFileNames`)
This is why for the time being some names are weird/funny, like `ovl_En_Torch2` which is Dark Link's code, or `ovl_Boss_Ganondrof` which is Phantom Ganon's code (forest temple boss).

## The file system (Advanced)

The game references files by their VROM (Virtual ROM) offset. VROM offsets are translated to ROM offsets (which index into the actual ROM file) by a look-up inside the "DMA table" (`dmadata` file, [`src/dmadata/dmadata.c`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/src/dmadata/dmadata.c)) which lists VROM and ROM offsets for each file.
In an uncompressed ROM, VROM and ROM offsets are typically identical.

Knowing ROM offsets, the game loads data from the cartridge by performing what is called [DMA](http://n64devkit.square7.ch/keywords/index/data/system.htm#DMA). If compressed, the file is decompressed.

## How files are defined in oot decomp

The [`spec`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/spec) defines which files contain what.

Files appear in the same order in the `spec` as in the ROM.

For example this defines the "makerom" file, the first file in the ROM:

```
beginseg
    name "makerom"
    include "build/asm/rom_header.o"
    include "build/asm/ipl3.o"
    include "build/asm/entry.o"
endseg
```

"seg" stands for "segment".
This file/segment contains the ROM header, the IPL3 boot code, and the entrypoint function.

It is possible to edit the `spec` if you want to add or modify files for modding.

When building decomp, the `spec` is processed to a [linker script](https://sourceware.org/binutils/docs/ld/Scripts.html) `build/ldscript.txt` ([relevant Makefile part](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/Makefile#L180-L184)).

## The ROM header

The ROM header provides information useful to the N64 when booting the ROM.
In oot decomp it is located in [`asm/rom_header.s`](https://github.com/zeldaret/oot/blob/05b2cbfc60d396a7cf3b539347fc693d5588cada/asm/rom_header.s).

One of your first edits may be to change the "Region" from `"P"` (Europe) to `"E"` (North America) ([En64 Wiki: ROM Header](http://en64.shoutwiki.com/wiki/ROM#Cartridge_ROM_Header), [Software Submissison Requirements (PAL)](http://n64devkit.square7.ch/info/submission/pal/01-01.html)) to make the ROM "NTSC" instead of "PAL", so the ROM runs at 20fps instead of the decreased PAL framerate.
