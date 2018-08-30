#include <iostream>
#include <pybind11/pybind11.h>
#include <rocksdb/c.h>

int add(int i, int j) {

  std::string dbPath("db-cache");

  rocksdb_options_t *options = rocksdb_options_create();
  rocksdb_options_set_create_if_missing(options, 1);

  char *err = NULL;
  rocksdb_t *db = rocksdb_open(options, dbPath.c_str(), &err);

  if (err != NULL) {
    std::cerr << "Failed to open the database .." << std::endl;
    return -1;
  }

  rocksdb_close(db);

  return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(pyrocksdb, m) {
  m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: cmake_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

  m.def("add", &add, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");

  m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}