# rainyday

Rain simulation, built for a rainy day.

## Installation

1. Compile using the build.sh script

```
./build.sh
```

2. To run rainyday from anywhere, create a symlink

```
repo_path=$(pwd)
ln -s "$repo_path"/rainyday /usr/local/bin/rainyday
```

## Controls

`UP/DOWN` - Increase or decrease the number of raindrops

`RIGHT/LEFT` - Increase or decrease the raindrop acceleration

`1/2/3` - Swap between raindrop colors

## Dependencies

1. GNU C++ Compiler

2. Various dependencies of olcPixelGameEngine:

    - Linux: [Compiling on Linux](https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Compiling-on-Linux "olcPixelGameEngine Wiki")

    - Windows: [Compiling on Windows](https://www.youtube.com/watch?v=eTGSTTxR-Ss "Youtube Tutorial")
