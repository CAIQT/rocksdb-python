import sys
from rocksdb import PyRocksDB


def main(db_path):
    db = PyRocksDB(db_path)

    # open
    db.open(False)

    # count the number of keys
    print(db.count())

    # write an entry
    db.write("Kapil_Sachdeva_Test", "Some random string")

    # read an entry
    print(db.read("Kapil_Sachdeva_Test"))

    # close it
    db.close()


if __name__ == '__main__':
    main(sys.argv[1])
