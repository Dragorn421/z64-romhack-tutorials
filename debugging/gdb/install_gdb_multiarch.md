# Install gdb-multiarch

## Windows

Warning: I don't use Windows, these instructions are untested.

Install MSYS2: https://www.msys2.org/

Then install the gdb-multiarch package https://packages.msys2.org/package/mingw-w64-x86_64-gdb-multiarch (open a MSYS2 terminal and run `pacman -S mingw-w64-x86_64-gdb-multiarch`)

You may then run `gdb-multiarch` in a MSYS2 terminal.

## Linux

### Ubuntu and derivatives

`apt install gdb-multiarch`

### Other distros

You can most likely find `gdb-multiarch` with your package manager.
