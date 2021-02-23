# runline

## Description
__runline__ is a tool for converting 128px * 8 px black-white image to C-style HEX array

![alt text](https://raw.githubusercontent.com/KonstantIMP/runline/master/.readme/runline.png "runline screenshot")

## Features

* Save data to file
* Load data from file
* Copy data to clipboard
* English and Russian support
* Fill everything
* Clear everything
* Clear and Fill top and bottom parts

## Build

``` bash
# 1. Install building dependencies
sudo pacman -S meson qt5 qt clang git base-devel
# 2. Clone this repo
git clone https://github.com/KonstantIMP/runline.git
# 3. Build it
cd runline
meson builddir
ninja -C builddir
# 4. Run and use
./builddir/runline
```

### Note

For Windows platforms you can just download latest release and run runline.exe

## Additional info

![GitHub release (latest by date)](https://img.shields.io/github/v/release/KonstantIMP/runline?style=flat-square) ![GitHub](https://img.shields.io/github/license/KonstantIMP/runline?style=flat-square)
