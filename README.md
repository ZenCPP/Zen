Zen C++ Libraries
=================

<img src="https://raw.githubusercontent.com/ZenCPP/Zen/master/zen-logo.png" height="250" />

The Zen C++ libraries are a set of C++ headers that you can freely use in your
own projects. The libraries try to fill missing pieces in the existing C++
ecosystem, based on ideas taken from Haskell and Rust.

🧪 These headers are experimental and currently require a modern compiler
supporting a modern C++ standard.

## Installation and Usage 

Currently, the preferred method for using these libraries is by downloading a
recent tarball of the repository's source and checking in the sources into your
project's version control system (e.g. in a folder called `vendor/zen`).

**CMakeLists.txt**
```cmake
add_subdirectory(vendor/zen EXCLUDE_FROM_ALL)

# ...

target_link_libraries(myapp zen_base)
```

Additionally, we are working on a system that will automatically detect,
download and build the correct dependencies without pulling in CMake. However, 
the construction of this build tool will take a while.

## Documentation

Documentation will soon be available on [the official website][1]. For now, you
will have to consult the header files in `include/zen/` to learn more.
Alternatively, you can try to build the documentation locally using [Doxygen][2].

## License

This library is licensed under Apache 2.0 license. Briefly put, you are allowed
to use this library commercially as long as you give due credit to the authors
that put their time and energy in building this.

See [the LICENSE file][3] for more information.

[1]: https://zencpp.github.io/
[2]: http://www.doxygen.nl/
[3]: https://github.com/ZenCPP/Zen/blob/master/LICENSE


