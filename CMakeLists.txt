cmake_minimum_required(VERSION 3.5)
project(pyrocksdb)

add_subdirectory(pybind11)
pybind11_add_module(pyrocksdb src/main.cc)