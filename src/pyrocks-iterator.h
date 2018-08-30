#ifndef _include_pyrocks_iterator_h_
#define _include_pyrocks_iterator_h_

#include <rocksdb/c.h>
#include <string>

class PyRocksIterator {

private:
  PyRocksIterator(const PyRocksIterator &rhs) = delete;
  PyRocksIterator &operator=(const PyRocksIterator &rhs) = delete;

public:
  PyRocksIterator(rocksdb_t *db);

public:
  ~PyRocksIterator();

private:
  rocksdb_readoptions_t *_roptions;
  rocksdb_iterator_t *_iter;

public:
  bool isValid();
  void next();
  void dispose();
  std::string readKey();
};

#endif