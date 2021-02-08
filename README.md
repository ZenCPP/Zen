Zen C++ Libraries
=================

<img src="https://raw.githubusercontent.com/ZenLibraries/ZenLibraries/master/zen-logo.png" height="250" />

The Zen C++ libraries are a set of C++ headers that aim to partially replace
the C++ standard library. The libraries try to fill missing pieces in the
existing C++ ecosystem, based on ideas taken from Haskell and Rust.

You can freely use these libraries in your own projects. 

⚠️🧪 These libraries are experimental. They require a modern C++ compiler that
supports at least C++17. The API may break regularly with the release of new
versions. If you plan to make use of them right now, you will have to refactor
your code regularly when upgrading.

## Installation and Usage 

We support Meson and CMake. Currently, the preferred method for using these
libraries is by downloading a recent tarball of the repository's source and
checking in the sources into your project's version control system (e.g. in a
folder called `vendor/zen`).

**CMakeLists.txt**
```cmake
add_subdirectory(vendor/zen EXCLUDE_FROM_ALL)

# ...

target_link_libraries(myapp zen_base)
```

**meson.build**
```meson
project('myproject', 'cxx')

zen_proj = subproject('zen')
zen_dep = zen_proj.get_variable('zen_dep')

executable('myapp', dependencies: zen_dep)
```

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
[3]: https://github.com/ZenLibraries/ZenLibraries/blob/master/LICENSE


