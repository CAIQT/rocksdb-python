#include "pyrocks-db.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(rocksdb, m) {

  py::class_<PyRocksIterator>(m, "PyRocksIterator")
      .def("next", &PyRocksIterator::next)
      .def("is_valid", &PyRocksIterator::isValid)
      .def("read_key", &PyRocksIterator::readKey)
      .def("dispose", &PyRocksIterator::dispose);

  py::class_<PyRocksDB>(m, "PyRocksDB")
      .def(py::init<const std::string &>())
      .def("open", &PyRocksDB::open)
      .def("close", &PyRocksDB::close)
      .def("count", &PyRocksDB::count)
      .def("read", &PyRocksDB::read)
      .def("write", &PyRocksDB::write)
      .def("new_iterator", &PyRocksDB::newIterator);
}