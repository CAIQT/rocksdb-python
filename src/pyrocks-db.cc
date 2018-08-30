#include "pyrocks-db.h"
#include <iostream>

PyRocksDB::PyRocksDB(const std::string &dbPath) : _dbPath(dbPath) {}

PyRocksDB::~PyRocksDB() { close(); }

bool PyRocksDB::open() {
  rocksdb_options_t *options = rocksdb_options_create();
  rocksdb_options_set_create_if_missing(options, 1);

  char *err = NULL;
  _db = rocksdb_open(options, _dbPath.c_str(), &err);

  if (err != NULL) {
    std::cerr << "Failed to open the database .." << std::endl;
    return false;
  }

  return true;
}

void PyRocksDB::close() {
  if (_db != NULL) {
    rocksdb_close(_db);
    _db = NULL;
  }
}

int PyRocksDB::count() {
  rocksdb_readoptions_t *roptions = rocksdb_readoptions_create();
  rocksdb_iterator_t *iter = rocksdb_create_iterator(_db, roptions);

  int numOfEntries = 0;

  rocksdb_iter_seek_to_first(iter);

  while (rocksdb_iter_valid(iter)) {
    numOfEntries++;
    rocksdb_iter_next(iter);
  }

  rocksdb_iter_destroy(iter);
  rocksdb_readoptions_destroy(roptions);

  return numOfEntries;
}
