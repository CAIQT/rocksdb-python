cmake_minimum_required(VERSION 3.5)
project(rocksdb-python)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(RocksDB REQUIRED)

add_subdirectory(pybind11)

add_library(rocksdb MODULE src/pyrocks-db.cc src/pyrocks-iterator.cc src/binder.cc)

target_link_libraries(rocksdb PRIVATE pybind11::module ${RocksDB_LIBRARIES})
set_target_properties(rocksdb PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                         SUFFIX "${PYTHON_MODULE_EXTENSION}")