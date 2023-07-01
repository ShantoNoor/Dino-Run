#!/bin/bash

# Set up environment variables
export CXX=/usr/bin/clang++
export CPATH=/opt/homebrew/include
export LIBRARY_PATH=/opt/homebrew/lib

# Build SDL2
cd /opt/homebrew/Cellar/sdl2/2.28.0/bin
./sdl2-config --cflags
./sdl2-config --libs
cd -

# Build SDL2_image
sdl2_image_cflags=$(pkg-config --cflags SDL2_image)
sdl2_image_libs=$(pkg-config --libs SDL2_image)

# Build SDL2_mixer
sdl2_mixer_cflags=$(pkg-config --cflags sdl2_mixer)
sdl2_mixer_libs=$(pkg-config --libs sdl2_mixer)

# Build SDL2_ttf
sdl2_ttf_cflags=$(pkg-config --cflags sdl2_ttf)
sdl2_ttf_libs=$(pkg-config --libs sdl2_ttf)

# Build your SDL2 project
cd /Users/shantonoor/Downloads/Dino-Run
$CXX -std=c++17 -o bin/main src/*.cpp $sdl2_image_cflags $sdl2_image_libs $sdl2_mixer_cflags $sdl2_mixer_libs $sdl2_ttf_cflags $sdl2_ttf_libs -I/opt/homebrew/Cellar/sdl2/2.28.0/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.28.0/lib -lSDL2