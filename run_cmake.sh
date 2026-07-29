#!/usr/bin/env bash

# clone/update FTXUI submodule
git submodule add https://github.com/ArthurSonzogni/FTXUI external/ftxui
git submodule update --init --recursive

# configure build
mkdir -p build
cmake -B build -G Ninja

# build
# cmake --build build --target clean
cmake --build build --parallel $(nproc)

