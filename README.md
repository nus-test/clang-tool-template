# Setup

Certain libraries are required to have this work. In Ubuntu, you just have to install the following:

```bash
sudo apt install -y cmake llvm libclang-dev libclang-cpp-dev
```

After this, the tool can be built with the following:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

In Visual Studio Code, the CMake extension should be automatically able to configure this project, and all integration should work out-of-the-box.