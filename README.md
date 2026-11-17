# SDL2 C Project

## Layout
```
src/       all .c files (subfolders fine) – compiled and linked automatically
include/   your headers (already on the include path)
build/     object files (generated)
bin/       final executable (generated)
```

## Install SDL2 (once per machine)
- **Ubuntu/Debian/WSL:** `sudo apt install build-essential libsdl2-dev`
- **Fedora:** `sudo dnf install SDL2-devel`
- **Arch:** `sudo pacman -S sdl2`
- **macOS:** `brew install sdl2 pkg-config`
- **Windows:** use MSYS2 → `pacman -S mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-gcc make`

## Build & run
```
make            # debug build -> bin/app
make run        # build and launch
make release    # optimised build
make clean      # remove build output
```
Change the executable name by editing `TARGET` in the Makefile.
