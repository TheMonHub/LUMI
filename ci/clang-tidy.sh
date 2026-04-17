#!/bin/bash
set -e

cd "$(dirname "$0")"/.. || error_exit "Failed to change directory"

echo "Installing LuaJIT"
git clone https://luajit.org/git/luajit.git
cd luajit
git checkout v2.1
make && sudo make install
cd ..

echo "Running clang-tidy checks..."
./automated/check.sh