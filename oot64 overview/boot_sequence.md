# Game boot (Advanced)

This is simplified, many steps from the boot sequence are omitted.

## Checksum

The N64 computes a checksum from 1 MB of ROM, starting at 0x1000, and compares it to the checksums in the ROM header.
If the checksums mismatch the game won't start on hardware. (emulators, like [Project64](https://www.pj64-emu.com/), may break out of the infinite loop caused by bad checksums and run the game just fine)

This would of course be an issue for modding, for example the `dmadata` file which lists the offsets of the files inside the ROM is inside that 1 MB used to compute the checksum. So changing any file size or location may change the checksum and prevent the ROM from booting.

So, in oot decomp the checksum is computed ([`tools/n64chksum.c`](https://github.com/zeldaret/oot/blob/master/tools/n64chksum.c)) after each build and written to the rom header ([`tools/elf2rom.c`](https://github.com/zeldaret/oot/blob/master/tools/elf2rom.c#L186)), to keep it matching.

The TLDR is you don't have to worry about this with the oot decomp.

## Running game code

The N64 copies 1 MB of ROM to RAM, then jumps to (starts executing code at) the address specified in the ROM header (entrypoint) ([Manual 6.10](http://n64devkit.square7.ch/pro-man/pro06/06-10.htm)).

The `entrypoint` function is written in assembly: [`asm/entry.s`](https://github.com/zeldaret/oot/blob/master/asm/entry.s#L12). It is located inside the "makerom" file.

It then jumps to [`bootproc`](https://github.com/zeldaret/oot/blob/master/src/boot/boot_main.c#L13), inside the "boot" file.

It should be noted that it is very important that the `entrypoint` and "boot" files stay within the megabyte of ROM initially loaded by the N64. This is achieved by having the files at the start of the `spec`. This also means the "boot" file size is limited, but there is a lot of leeway before that becomes an issue.

From `bootproc` various initialization steps are performed, [`Idle_ThreadEntry`](https://github.com/zeldaret/oot/blob/master/src/boot/idle.c#L37) then [`Main_ThreadEntry`](https://github.com/zeldaret/oot/blob/master/src/boot/idle.c#L19) are executed (as new threads, but that doesn't really matter).

One of the main things that happens in these functions is `Main_ThreadEntry` loads the "code" file from ROM into RAM, then calls the `Main` function from "code".

More initialization happens in `Main`, then the graphics thread is run. ([`Graph_ThreadEntry`](https://github.com/zeldaret/oot/blob/master/src/code/graph.c#L399))

The graphics thread is the thread where most of the game computations actually happen.
