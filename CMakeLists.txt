cmake_minimum_required(VERSION 3.5)
project(pyrocksdb)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(RocksDB REQUIRED)

add_subdirectory(pybind11)

add_library(pyrocksdb MODULE src/main.cc)

target_link_libraries(pyrocksdb PRIVATE pybind11::module ${RocksDB_LIBRARIES})
set_target_properties(pyrocksdb PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                         SUFFIX "${PYTHON_MODULE_EXTENSION}")