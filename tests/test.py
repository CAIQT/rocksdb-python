import sys
from rocksdb import PyRocksDB


def main(db_path):
    db = PyRocksDB(db_path)

    # open
    db.open(True)

    # count the number of keys
    print(db.count())

    # write an entry
    db.write("Kapil_Sachdeva_Test", "Some random string")

    # read an entry
    print(db.read("Kapil_Sachdeva_Test"))

    iterator = db.new_iterator()
    print(iterator.is_valid())

    while iterator.is_valid():
        print(iterator.read_key())
        iterator.next()

    iterator.dispose()

    # close it
    db.close()


if __name__ == '__main__':
    main(sys.argv[1])
