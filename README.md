# PixelSort

A fast C++ command-line tool for creating pixel sorting effects on images.

## Features
- Sort pixels by brightness, hue, or saturation
- Horizontal or vertical sorting
- Threshold-based sorting (only sort pixels above/below certain brightness)
- Fast processing with STB image libraries

## Building
```bash
mkdir build && cd build
cmake ..
make
```

## Usage
```bash
./pixelsort input.jpg output.png --mode brightness --direction horizontal
```

## Requirements
- C++17 or higher
- CMake 3.15+

