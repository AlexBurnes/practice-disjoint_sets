## Student practice C++: searching disjoint sets

Searching of non-intersected groups of source files by list of destination files based on mapping between sources and destionations files.

## Author

Aleksey.Ozhigov<AlexBurnes@gmail.com>

## Version

0.1.0

## Task

Implement then algorithm in the grouping.cpp file, run tests, run benchmarks on different container libraries. 
See working example at git@github.com:AlexBurnes/practice-sort_keys.git

## Change log

For detail history changes, see [CHANGELOG](CHANGELOG.md)

## Build

    git submodule init
    git submodule update
    docker build --tag disjoint_sets:latest --network host --progress=plain .

## Test Coverage

To view test coverage, run a Docker container:

    docker run -d --rm --name disjoint_sets --publish 8081:80 disjoint_sets

Then open your browser at [Coverage](http://localhost:8081)

## Code Style Check

For checking code style formatting the clang-format-19 utility is used.
The format is defined in style_format.txt, which is based on [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

    clang-format-19 --style="file:style_format.txt" source

# License

This work is distributed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0), see [LICENSE](https://github.com:AlexBurnes/practice-disjoint_sets/blob/master/LICENSE) for more information.
