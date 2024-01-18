# matrix
The Matrix Programming Language

## Build the compiler

First, create a new build directory and navigate to it:

```sh
mkdir build && cd build
```

Next, build the compiler:

```sh
cmake ..
```

&&

```sh
make
```

## Common issues

In case any LLVM libs are not found, run this command:

```sh
llvm-config --libs
```

Edit `llvm_libs` variables in the CMakeLists.txt `llvm_map_components_to_libnames` field to whatever the result of the above command is, then omit the `-lLLVM` part.

