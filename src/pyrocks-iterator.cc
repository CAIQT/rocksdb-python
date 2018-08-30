#include "pyrocks-iterator.h"
#include <iostream>

PyRocksIterator::PyRocksIterator(rocksdb_t *db) {
  _roptions = rocksdb_readoptions_create();
  _iter = rocksdb_create_iterator(db, _roptions);
  rocksdb_iter_seek_to_first(_iter);
}

PyRocksIterator::~PyRocksIterator() { dispose(); }

bool PyRocksIterator::isValid() { return rocksdb_iter_valid(_iter); }

void PyRocksIterator::next() { rocksdb_iter_next(_iter); }

void PyRocksIterator::dispose() {
  if (_iter != NULL) {
    rocksdb_iter_destroy(_iter);
    _iter = NULL;
  }

  if (_roptions != NULL) {
    rocksdb_readoptions_destroy(_roptions);
    _roptions = NULL;
  }
}

std::string PyRocksIterator::readKey() {

  char *err = NULL;

  size_t keyLen;
  const char *entryKey;
  entryKey = rocksdb_iter_key(_iter, &keyLen);

  std::string value(entryKey, keyLen);

  return value;
}