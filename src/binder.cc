#include "pyrocks-db.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(rocksdb, m) {

  py::class_<PyRocksDB>(m, "PyRocksDB")
      .def(py::init<const std::string &>())
      .def("open", &PyRocksDB::open)
      .def("close", &PyRocksDB::close)
      .def("count", &PyRocksDB::count);
}