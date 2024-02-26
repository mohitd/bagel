# Bagel

An "everything bagel" of C++!

This is a personal project created to experiment with and better understand C++,
CMake, and other auxiliary tooling. It holds a bunch of miscellaneous C++ data
structures and components, similar to libraries like Boost, Folly, and `std`. 

This library is not meant to replace (or even complement) other offerings. It's
solely for my own personal experimentation and usage. But if there are
offerings that appeal to your use-case, feel free to use it :)

# Building

Use CMake.

```
mkdir build
cmake ..
make & make install
```

There are a few options that you can enable:

* `BAGEL_BUILD_SHARED`: builds shared libraries (can also use BUILD_SHARED_LIBS)
* `BAGEL_BUILD_TESTS`: builds tests
* `BAGEL_BUILD_EXAMPLES`: builds examples
* `BAGEL_BUILD_DOCS`: builds Doxygen documentation

# Usage

Link against this library using the `bagel::bagel` target.

```
target_link_libraries(my_proj
    bagel::bagel
)
```

Since this project uses "modern" CMake pratices, there are no magic variables
like `bagel_LIBRARIES` or `bagel_INCLUDE_DIRS`.
