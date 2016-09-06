
# CeCe core library

[![Build Status](https://travis-ci.org/GeorgievLab/CeCe-core.svg?branch=master)](https://travis-ci.org/GeorgievLab/CeCe-core)
[![Build status](https://ci.appveyor.com/api/projects/status/sb1w56upjfwj9w7g/branch/master?svg=true)](https://ci.appveyor.com/project/NTSFka/cece-core/branch/master)

CeCe is a platform for advanced simulation of cell communication in dynamic environment.

This repository contains only core library, for whole project see [https://github.com/GeorgievLab/CeCe](https://github.com/GeorgievLab/CeCe)

## Building from source

Building from source code is done by CMake (see Requirements). Required submodules (Box2D, googletest) are cloned by CMake in case they are needed.

### Linux & macOS

```bash
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

### Windows
```batch
md build
cd build
cmake -G "Visual Studio 14 2015" ..
cmake --build .
```

### Requirements

* C++11 compiler - GCC, Clang, MSVC.
* [CMake](https://cmake.org) v3.1 or newer.
