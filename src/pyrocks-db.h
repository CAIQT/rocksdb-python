#ifndef _include_pyrocks_db_h_
#define _include_pyrocks_db_h_

#include <rocksdb/c.h>
#include <string>

class PyRocksDB {
private:
  PyRocksDB(const PyRocksDB &rhs) = delete;
  PyRocksDB &operator=(const PyRocksDB &rhs) = delete;

public:
  PyRocksDB(const std::string &dbPath);
  ~PyRocksDB();

private:
  std::string _dbPath;
  rocksdb_t *_db;

public:
  bool open(bool createIfMissing);
  void close();
  int count();
  std::string read(const std::string &key);
  void write(const std::string &key, const std::string &value);
};

#endif