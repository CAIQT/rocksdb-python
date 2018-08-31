#include "pyrocks-db.h"
#include <iostream>

PyRocksDB::PyRocksDB(const std::string &dbPath) : _dbPath(dbPath) {}

PyRocksDB::~PyRocksDB() { close(); }

bool PyRocksDB::open(bool createIfMissing) {
  rocksdb_options_t *options = rocksdb_options_create();
  rocksdb_options_set_create_if_missing(options, createIfMissing ? 1 : 0);

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

std::string PyRocksDB::read(const std::string &key) {
  char *err = NULL;

  rocksdb_readoptions_t *readoptions = rocksdb_readoptions_create();

  size_t keyLen = key.size();
  const char *entryKey = key.c_str();

  size_t valueLen;
  char *returned_value =
      rocksdb_get(_db, readoptions, entryKey, keyLen, &valueLen, &err);

  rocksdb_readoptions_destroy(readoptions);

  // TODO: proper error handling
  // throw an exception/error
  if (err != NULL || valueLen == 0) {
    return std::string("");
  }

  std::string value(returned_value, valueLen);

  return value;
}

void PyRocksDB::write(const std::string &key, const std::string &value) {
  char *err = NULL;

  rocksdb_writeoptions_t *writeoptions = rocksdb_writeoptions_create();

  size_t keyLen = key.size();
  const char *entryKey = key.c_str();

  size_t valueLen = value.size();
  const char *entryValue = value.c_str();

  rocksdb_put(_db, writeoptions, entryKey, keyLen, entryValue, valueLen, &err);

  rocksdb_writeoptions_destroy(writeoptions);

  // TODO: proper error handling
  // throw an exception/error
}

std::unique_ptr<PyRocksIterator> PyRocksDB::newIterator() {
  return std::make_unique<PyRocksIterator>(_db);
}
