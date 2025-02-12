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
    db.write("Kapil_Sachdeva_Test2", b"Some random string2")

    # read an entry
    print(db.read("Kapil_Sachdeva_Test"))

    iterator = db.new_iterator()
    print(iterator.is_valid())

    while iterator.is_valid():
        k = iterator.read_key()
        print(type(k), k)
        iterator.next()

    iterator.dispose()

    # close it
    db.close()


if __name__ == '__main__':
    main(sys.argv[1])
