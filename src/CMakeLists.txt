cmake_minimum_required(VERSION 3.10.0)
project(HEAAN)
set(PYBIND11_CPP_STANDARD -std=c++11)

include_directories("/usr/include/python3.6")
include_directories("../pybind11/include")
include_directories("/usr/local/include")
include_directories("../HEAAN/src")

LINK_LIBRARIES("/usr/local/lib/libntl.so")
LINK_LIBRARIES("../HEAAN/lib/libHEAAN.a")

add_subdirectory(pybind11)
pybind11_add_module(HEAAN wrapper.cpp)
