# 53E Over Under

[![Build Project](https://github.com/Area-53-Robotics/53E/actions/workflows/pros-build.yml/badge.svg)](https://github.com/Area-53-Robotics/53E/actions/workflows/pros-build.yml)
[![Clang Format](https://github.com/Area-53-Robotics/53E/actions/workflows/test-clang-format.yml/badge.svg)](https://github.com/Area-53-Robotics/53E/actions/workflows/test-clang-format.yml)

This is 53E's codebase for the 2023, 2024 Over Under Season.


## Style Guide

This project follows [Google's](https://google.github.io/styleguide/cppguide.html) style guide, with a few exceptions.

### Pragma Once

Use of pragma once is permitted in the place of normal header guards. We only ever need to compile for one architecture, with the same compiler each time, so using non-standard features is not an issue for us.


### File names

Use .cpp for C++ body files, and .hpp for C++ header files.

## Thanks To

Here are the people and codebases that helped us along the way:
- [Lib7842](https://github.com/theol0403/lib7842)
- [RaidZeroLib](https://github.com/Ryan4253/RaidZeroLib/tree/main/src)
- [LemLib](https://github.com/LemLib/LemLib)
