#!/usr/bin/env bash

# configure build
mkdir -p build
cmake -B build -G Ninja

# build
# cmake --build build --target clean
cmake --build build --parallel $(nproc)

