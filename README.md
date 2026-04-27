# Chaos Game

# Usage
When the program opens, you left-click to create points (maximum of 10).

Afterwards, right-clicking will begin rendering it.

Pressing the `r` key will erase your shape, allowing you to make another.

## Building
There are 3 ways to compile and run the program. Using CMake is preferred, whicn can be done via IDE or command line. We also supply a makefile, but that requires extra work to get running for most machines.

### IDE
Import it into VSCode, CLion, or your IDE of choice, and it should recognize the CMakeLists.txt file and let you compile/run the program.

### Command line
#### CMake
This requires the CMake package be installed on your system.

You run `cmake -B build` first, to cache SFML locally (you only need to do this once)

Then, you run `cmake --build build` to build the program itself.

The output will be in `build/bin/`

#### Makefile
If you have SFML2 installed on your system, you can directly compile the program with our `makefile` by running the `make` command. Most distro repositories distribute SFML3, which is incompatible with our program. This is why we prefer CMake instead, since we configured it to cache the correct SFML2 version.

## Linux
Linux requires a few packages to be installed to be able to compile the project.

### Fedora
- `glew-devel`
- `SDL2-devel`
- `SDL2_image-devel`
- `glm-devel`
- `freetype-devel`
