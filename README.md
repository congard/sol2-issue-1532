# sol2 issue 1532

This repository contains a complete test case for [ThePhD/sol2](https://github.com/ThePhD/sol2)
issue [1532](https://github.com/ThePhD/sol2/issues/1532).

## Dependencies

This repository has [sol2](https://github.com/ThePhD/sol2) and [lua](https://github.com/walterschell/Lua)
as dependencies. Clone it with

```bash
git clone --recurse-submodules https://github.com/congard/sol2-issue-1532.git
```

Or, if you have already cloned it, use

```bash
git submodule update --init --recursive
```

## Building

```bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -B build -G "Ninja"
cmake --build build --target sol2_issue_1532 -- -j 8
```

## Results

- The issue appears when `sol::state` is being used in the external library;
- The issue occurs when the library is built as shared, but only on Windows;
- Tested with both sol v3.3.0 and v3.2.3 - the same results were obtained;

| OS                  | Compiler                                                   | Shared library result   | Static library result |
|---------------------|------------------------------------------------------------|-------------------------|-----------------------|
| Windows 11 22H2     | `clang.exe` / `clang++.exe` 16.0.0, x86_64-pc-windows-msvc | ❌ Failed w/o workaround | ✅ Ok in both cases    |
| Windows 11 22H2     | MSVC 14.37.32822 `cl.exe` / `cl.exe`                       | ❌ Failed w/o workaround | ✅ Ok in both cases    |
| Ubuntu 22.04.3 LTS* | `clang` / `clang++` 14.0.0-1ubuntu1.1, x86_64-pc-linux-gnu | ✅                       | ✅                     |
| Ubuntu 22.04.3 LTS* | `gcc` / `g++` 11.4.0-1ubuntu1~22.04                        | ✅                       | ✅                     |
| Fedora 38**         | `clang` / `clang++` 16.0.6 (Fedora 16.0.6-3.fc38)          | ✅                       | ✅                     |
| Fedora 38**         | `gcc` / `g++` 13.2.1 20230728 (Red Hat 13.2.1-1)           | ✅                       | ✅                     |

_\* Linux 5.15.90.1-microsoft-standard-WSL2_
_\*\* Linux 6.4.15-200.fc38.x86_64_

### Windows shared library error message

#### sol v3.3.0

```
Testing with workaround disabled
stack index 1, expected userdata, received sol.lib::Bar *: value at this index does not properly reflect the desired type (bad argument into 'void(lib::Foo *)')
stack traceback:
        [C]: in function 'func'
        [string "loadType('Foo') loadType('Bar') function f(o)..."]:1: in function 'f'
Testing with workaround disabled
stack index 1, expected userdata, received sol.lib::Bar *: value at this index does not properly reflect the desired type (bad argument into 'void(lib::Foo *)')
stack traceback:
        [C]: in function 'func'
        [string "loadType('Foo') loadType('Bar') function f(o)..."]:1: in function 'f'
Testing with workaround enabled
Ok
Testing with workaround enabled
Ok
```

#### sol v3.2.3

```
Testing with workaround disabled
stack index 1, expected userdata, received sol.void) [T = lib::Bar *]: value at this index does not properly reflect the desired type (bad argument into 'void) [T = void](void) [T = lib::Foo *])')
stack traceback:
        [C]: in function 'func'
        [string "loadType('Foo') loadType('Bar') function f(o)..."]:1: in function 'f'
Testing with workaround disabled
stack index 1, expected userdata, received sol.void) [T = lib::Bar *]: value at this index does not properly reflect the desired type (bad argument into 'void) [T = void](void) [T = lib::Foo *])')
stack traceback:
        [C]: in function 'func'
        [string "loadType('Foo') loadType('Bar') function f(o)..."]:1: in function 'f'
Testing with workaround enabled
Ok
Testing with workaround enabled
Ok
```
