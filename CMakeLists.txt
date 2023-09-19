cmake_minimum_required(VERSION 3.12) 
project(mytool LANGUAGES C CXX)

find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)

include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

add_executable(mytool my-tool.cpp)
target_link_libraries(mytool clangBasic clangTooling)