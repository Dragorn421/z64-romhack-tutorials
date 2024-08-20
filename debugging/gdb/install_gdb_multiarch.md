# Install gdb-multiarch

## Windows

Install MSYS2: https://www.msys2.org/

Then install the gdb-multiarch package https://packages.msys2.org/package/mingw-w64-x86_64-gdb-multiarch (open a MSYS2 terminal and run `pacman -S mingw-w64-x86_64-gdb-multiarch`)

You may then run `gdb-multiarch` in a MSYS2 terminal.

## Linux

### Ubuntu and derivatives

`apt install gdb-multiarch`

### Other distros

You can most likely find `gdb-multiarch` with your package manager.

## macOS

The `gdb` package that can be installed using Homebrew comes with all targets:

`brew install gdb`

Use `gdb` in place of `gdb-multiarch` in the rest of this guide.

You may need "to do some OS permissions thing to get it to work (something like https://cohost.org/sdave-b/post/1560910-how-to-get-gdb-to-wo )"
