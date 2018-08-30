import sys
from rocksdb import PyRocksDB


def main(db_path):
    db = PyRocksDB(db_path)
    db.open()
    print(db.count())
    db.close()


if __name__ == '__main__':
    main(sys.argv[1])
