# SDL2 Lambertian Shader
Implements per-pixel Lambertian shading in a 2D environment with a simulated 3rd dimension.

## Quickstart Guide
### Install SDL2
- **Ubuntu/Debian/WSL:** `sudo apt install build-essential libsdl2-dev`
- **Fedora:** `sudo dnf install SDL2-devel`
- **Arch:** `sudo pacman -S sdl2`
- **macOS:** `brew install sdl2 pkg-config`
- **Windows:** use MSYS2 → `pacman -S mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-gcc make`

### Build & run
```
make            # debug build -> bin/app
make run        # build and launch
make release    # optimised build
make clean      # remove build output
```
