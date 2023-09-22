# Clang Tool Template

This template project is meant to be a tutorial and a quick-setup for anyone who wants to write a tool to generate/modify C/C++ code. LLVM and Clang are huge projects with huge pipelines, and many helper classes and tools exist to simplify tool development. However, that also means there is more than one way to do a single task.

This template project uses the bare minimum amount of LLVM/Clang code to get your tool up-and-running in as idiomatic of a way as possible. 

Some tutorial code is also available in `main.cpp` to help you understand how to write an AST matcher, or a transformer.

## Setup

Requirements:
- CMake
- LLVM 14 or higher
- Clang 14 developer libraries

In Ubuntu 22.04, you just have to install the following packages:

```bash
sudo apt install -y cmake llvm libclang-dev
```

After this, the tool can be built with the following:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The name of the tool can be changed in CMakeLists.txt:2.

In Visual Studio Code, the CMake extension should be automatically able to configure this project, and all integration should work out-of-the-box.

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/nus-test/clang-tool-template?quickstart=1)

⚠️ *There is currently no support for Windows-based compilation with CMake. Please [create an issue](https://github.com/nus-test/clang-tool-template/issues/new/choose) if you require it, and it should be resolved within a day.*

## Resources
The LLVM tutorials are always a good place to start, albeit sometimes out of date.
- [LibTooling Setup](https://clang.llvm.org/docs/LibTooling.html)
- [Clang Transformer Tutorial](https://clang.llvm.org/docs/ClangTransformerTutorial.html)
- [AST Matchers Tutorial](https://clang.llvm.org/docs/LibASTMatchersTutorial.html)