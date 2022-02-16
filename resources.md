# Resources

This is a pile of useful links and resources.

# Communities

Hylian Modding https://hylianmodding.com/

ZeldaRET https://zelda64.dev/

# Decompilations and disassemblies

## OoT decomp

A full decompilation of OoT64. Usually called "(oot) decomp".

Currently only Master Quest Debug and WIP documentation.

https://github.com/zeldaret/oot

## OoT 1.0 disassembly

Complete disassembly of the OoT NTSC 1.0 ROM

https://github.com/Roman971/oot-disassembly

# Creation Tools

## SharpOcarina

Also called "SO", noob-friendly fully-featured map editor.

https://hylianmodding.com/?p=240

Tutorial: https://www.youtube.com/watch?list=PLHifXa1TzdydElLH_cSvnWIemkqJvBLDZ&v=yJS83VECD9U

Current direct link (1.30, updates to 1.32): https://mega.nz/file/qEwkxRBK#iMxxI970AKabgPPDKENikJ0xp-s5sfAfRqnuGiCaxJY

Link for manual update: http://nexus.inpureprojects.info/noka/sharpocarina/Updates/1.32.zip

## CustomActorsToolkit

Compile and inject actors.

https://hylianmodding.com/?p=217

Tutorial: [Custom Actors tutorial](custom%20actors/index.md)

Version 0.53 (updates to 0.54): https://mega.nz/file/2Io2zboK#OzJDh9V6ownVfhC_w8HQnjmzgiv8LwY0pezKwRvOrW0

Version 0.54: https://github.com/Nokaubure/CustomActorToolkit/releases/download/CustomActorToolkit0.54/CustomActorToolkit0.54.zip

Source: https://github.com/Nokaubure/CustomActorToolkit

## zzrtl

Script-based ROM dumping and building.

https://github.com/z64me/zzrtl

Scripts with more features (such as audio): https://github.com/jaredemjohnson/zzrtl-audio

# Importers

https://github.com/Dragorn421/zelda64-import-blender

https://github.com/Dragorn421/zelda64-collision-import-blender

# Debugging tools

## Project64

Documentation (not entirely up-to-date): https://hack64.net/docs/pj64d/

Scripts API: https://htmlpreview.github.io/?https://github.com/project64/project64/blob/develop/JS-API-Documentation.html

## IS64-logging

View the game logs (if the game is a debug version) https://github.com/Dragorn421/IS64-logging

## Graphics Binary Debugger

Find what makes a render task crash https://github.com/Thar0/gbd

# Documentation

OoT Camera Function LookUp Table (WIP) https://docs.google.com/spreadsheets/d/17Mz4wgodnNFjA4l5yzskEvP5-IUv9iqewRx9U9BiEtg/edit#gid=0

A ton more links https://n64.dev/

Image formats https://n64squid.com/homebrew/n64-sdk/textures/image-formats/

# N64 hardware and low level

Thanks to Tharo for providing most of these links.

Official SDK Online Manuals http://n64devkit.square7.ch/

Friendly hardware overview https://www.copetti.org/writings/consoles/nintendo-64/

Technical notes about making an emulator (overviews, memory map, registers) https://n64.readthedocs.io/

VR4300 (N64 cpu) manual http://datasheets.chipdb.org/NEC/Vr-Series/Vr43xx/U10504EJ7V0UMJ1.pdf

Memory map, RCP registers http://en64.shoutwiki.com/wiki/Memory_map_detailed

`as` assembler documentation https://sourceware.org/binutils/docs/as/

`osTvType`, `osResetType`, `osMemSize`, `osAppNMIBuffer`:

- http://ultra64.ca/files/documentation/online-manuals/functions_reference_manual_2.0i/os/osGlobals.html
- http://en64.shoutwiki.com/wiki/N64_Memory#Boot_Strap

## Boot

- http://n64devkit.square7.ch/pro-man/pro06/06-10.htm
- https://sites.google.com/site/consoleprotocols/home/techinfo/lowlevel/n64-boot-sequence
- http://en64.shoutwiki.com/wiki/ROM#Checking_Integrated_Circuit_.28CIC.29_or_Lockout_chip.2Fboot_chip
- https://www.retroreversing.com/n64bootcode
- https://github.com/glankk/gz/blob/master/src/gz/zu.c#L320 (https://github.com/glankk/gz/blob/4417d6f12de6392bb96b51571d13cd8f8fab05af/src/gz/zu.c#L320)
- https://github.com/n64dev/cen64/issues/58
- https://github.com/hcs64/boot_stub

https://github.com/ttk2/mupen64plus/blob/master/wiki/SoftResetNotes.wiki
https://github.com/ttk2/mupen64plus/blob/f527f64f7655cce885145b707a643f37bbb3be94/wiki/SoftResetNotes.wiki

## RCP

https://dragonminded.com/n64dev/Reality%20Coprocessor.pdf

Official sgi document, it has some errors
https://ultra64.ca/files/documentation/silicon-graphics/SGI_Nintendo_64_RSP_Programmers_Guide.pdf

Really good rsp doc made by the homebrew community
https://github.com/rasky/r64emu/blob/master/doc/rsp.md
https://github.com/rasky/r64emu/blob/ddecbc0be48fedc224bce2262b1d30b0f67dbf78/doc/rsp.md

Angrylion, highly accurate video plugin https://github.com/ata4/angrylion-rdp-plus

F3DEX2 disassembly https://github.com/Mr-Wiseguy/f3dex2

https://github.com/Thar0/binutils-rsp
