# `clang-format` and `clang-tidy` experiment

## Usage (Windows + Visual Studio)

### Setup

- Get `clang-format.exe` and `clang-tidy.exe`
  - These can either have been built locally (see [Optional](##Optional) section below), downloaded from the [Release](https://github.com/pr0g/clang-tidy-and-clang-format/releases/tag/initial) page on this repo, or obtained from another source.
- Ensure `clang-format.exe` and `clang-tidy.exe` are added to your path (restart your command prompt after making this change if necessary).
  - Alternatively you can modify your path for the current session by running:
    ```bash
    set PATH=%PATH%;<path/to/clang-format_and_clang-tidy>
    ```
  - e.g. `set PATH=%PATH%;C:\clang-utils`

### Example Usage

- Open Developer Command Prompt for Visual Studio (required for Ninja build project)
  - (You can find this in the Start menu)
- Create a new directory and clone this repo
  - ```bash
    mkdir example && cd example
    git clone https://github.com/pr0g/clang-tidy-and-clang-format.git .
    mkdir build
    ```
- Generate a Ninja build project (to generate `compile_commands.json` file)
  - `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build/ -G Ninja`
- Build the project
  - `cmake --build build/`
- Run `clang-tidy` check (`compile_commands.json` is only needed for `clang-tidy`)
  - `clang-tidy main.cpp -p build\`
- Run `clang-tidy` fix
  - `clang-tidy main.cpp -p build\ -fix`
- Run `clang-format` check
  - `clang-format main.cpp`
- Run `clang-format` fix
  - `clang-format main.cpp -i`

### Optional

- Clone llvm/clang and build `clang-tidy` + `clang-format` from source.

#### Instructions

##### Latest

```bash
cd ${SRC_ROOT} # root folder for llvm repo
git clone --depth 1 https://github.com/llvm/llvm-project .
mkdir build
cmake -S llvm/ -B build\ -G "Visual Studio 16 2019" ^
  -DCMAKE_GENERATOR_PLATFORM=x64 ^
  -Thost=x64 ^
  -DLLVM_INCLUDE_TESTS=OFF ^
  -DLLVM_BUILD_TOOLS=OFF ^
  -DLLVM_INCLUDE_UTILS=OFF ^
  -DLLVM_TARGETS_TO_BUILD="" ^
  -DCLANG_ENABLE_STATIC_ANALYZER=OFF ^
  -DCLANG_ENABLE_ARCMT=OFF
  -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra"
cmake --build build\ --config Release -j4
```

##### Deprecated (llvm project has moved - see above)

```bash
# source - https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-1-extending-clang-tidy/
cd ${SRC_ROOT}
git clone https://git.llvm.org/git/llvm.git
cd llvm/tools
git clone https://git.llvm.org/git/clang.git
cd clang/tools
git clone https://git.llvm.org/gitclang-tools-extra.git extra
cd ../../..
mkdir build
cmake -S . -B build/ -G "Visual Studio 15 2017" ^
      -DCMAKE_GENERATOR_PLATFORM=x64 ^
      -Thost=x64 ^
      -DLLVM_INCLUDE_TESTS=OFF ^
      -DLLVM_BUILD_TOOLS=OFF ^
      -DLLVM_INCLUDE_UTILS=OFF ^
      -DLLVM_TARGETS_TO_BUILD="" ^
      -DCLANG_ENABLE_STATIC_ANALYZER=OFF ^
      -DCLANG_ENABLE_ARCMT=OFF
cmake --build build/ --target clang-tidy --config Release
cmake --build build/ --target clang-format --config Release
```
