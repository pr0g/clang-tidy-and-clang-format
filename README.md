# `clang-format` and `clang-tidy` experiment

## Usage (Windows)

### Optional

- Clone llvm/clang and build `clang-tidy` + `clang-format`

#### Latest

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

#### Deprecated

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

### Setup

- Ensure `clang-format.exe` and `clang-tidy.exe` are added to your path (restart your command prompt after making this change if necessary). These can either have been built locally (see [Optional](##Optional) section), downloaded from the [Release](https://github.com/pr0g/clang-tidy-and-clang-format/releases/tag/initial) page or obtained from another source.

### Usage

- Open Developer Command Prompt for Visual Studio
- Generate Ninja build project (to generate `compile_commands.json` file)
  - `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build/ -G Ninja`
- Build the project
  - `cmake --build build/`
- Run `clang-tidy` check
  - `clang-tidy main.cpp -p build\`
- Run `clang-tidy` fix
  - `clang-tidy main.cpp -p build\ -fix`
- Run `clang-format` check
  - `clang-format main.cpp`
- Run `clang-format` fix
  - `clang-format main.cpp -i`
