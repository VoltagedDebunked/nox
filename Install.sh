#!/usr/bin/bash

echo "Preparing executable..."

mkdir build
cd build
cmake ..
make

echo "Installing Nox..."

sudo cp nox /usr/bin/nox

mkdir -p "$HOME/.nox"
curl -o "$HOME/.nox/icon.png" https://i.ibb.co/nb2FN7g/image-1.png

echo "Nox is installed successfully!"