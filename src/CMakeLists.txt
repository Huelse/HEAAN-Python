cmake_minimum_required(VERSION 3.10.0)
project(HEAAN)
set(CMAKE_BUILD_TYPE "Release")
set(PYBIND11_CPP_STANDARD -std=c++11)

include_directories("/usr/include/python3.6")
include_directories("../pybind11/include")
include_directories("/usr/local/include")
include_directories("../HEAAN/src")

LINK_LIBRARIES("/usr/local/lib/libntl.so") # must be shared on compile
LINK_LIBRARIES("../HEAAN/lib/libHEAAN.a")  # must -fPIC compile

add_subdirectory(pybind11) # or
#find_package(pybind11)
pybind11_add_module(HEAAN wrapper.cpp)
