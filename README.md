# FDVar
C++ Dynamically typed variable

The goal of this project is to be provide an non intrusive extensible C++ dynamically typed variable library.
The user must be able to make any type convertible to `DynamicVariable` aka `FDVar::var` by implementing conversion functions and a helper struct to check if the type is compatible at compile time;

## Usage
    include <FDVar/FDVar.h>

    using namespace FDVar;

    int main()
    {
        var i = 42;
        var f = 3.14159;
        var str = "some text"

        var m = std::max(static_cast<float>(i), static_cast<float>(f))

        return 0;
    }

## Status
Currently the extensibility is kind of broken. I need to figure out the problem and solve it to be able to support stl containers at first

## Todo
- Document the code
- Document the API
- Use C++20 features
- Fix the stl container problems
- Make it header only
- Split files with forward declarations, prototypes and implementation

## Nice to have
- Use memory pool or Oilpan garbage collector to increase speed and avoid issues with allocation
