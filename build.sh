#!/bin/bash

clang++ main.cc --compile -nostdlib --target=wasm32 --std=c++20 --optimize=3 --output tmp.o
wasm-ld-14 --no-entry --export-all --allow-undefined --import-memory tmp.o -o out.wasm
rm tmp.o
