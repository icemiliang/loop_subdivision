# Loop subdivision

This package includes the prototype codes for implementing Loop subdivision.

![alt text](data/bunny.jpg?raw=true "Loop subdivision")

## Build
[![Build status](https://ci.appveyor.com/api/projects/status/xh035nmdsm39t6j5?svg=true)](https://ci.appveyor.com/project/icemiliang/loop-subdiv)

The program has been tested on Ubuntu 20.04 with g++ 9.3.0.

In the root directory, run:
```
$ rm -r build
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Usage
```
./main ../data/bunny.obj output.obj

./main -r 2 ../data/bunny.obj output.obj
```

## Contact
Please contact Liang Mi icemiliang@gmail.com for any issues, or create an issue for reporting bugs, requesting additional features, etc.
