# Find the RocksDB libraries
#
# The following variables are optionally searched for defaults
#  ROCKSDB_ROOT_DIR:    Base directory where all RocksDB components are found
#
# The following are set after configuration is done:
#  ROCKSDB_FOUND
#  RocksDB_INCLUDE_DIR
#  RocksDB_LIBRARIES

# we must have Snappy if we are using RocksDB
# as this is the only way to ensure that the database can
# be used across platforms
find_package(Snappy REQUIRED)

find_path(RocksDB_INCLUDE_DIR NAMES rocksdb/db.h
                             PATHS $ENV{VCPKG_INSTALL_DIR}/include ${ROCKSDB_ROOT_DIR} ${ROCKSDB_ROOT_DIR}/include)

find_library(RocksDB_LIBRARIES NAMES rocksdb rocksdb-shared
                              PATHS $ENV{VCPKG_INSTALL_DIR}/lib ${ROCKSDB_ROOT_DIR} ${ROCKSDB_ROOT_DIR}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RocksDB DEFAULT_MSG RocksDB_INCLUDE_DIR RocksDB_LIBRARIES)

if(ROCKSDB_FOUND)
  message(STATUS "Found RocksDB  (include: ${RocksDB_INCLUDE_DIR}, library: ${RocksDB_LIBRARIES})")
  if(NOT IS_WINDOWS)
    list(APPEND RocksDB_LIBRARIES ${RocksDB_LIBRARIES} "-lsnappy")
  endif()
  mark_as_advanced(RocksDB_INCLUDE_DIR RocksDB_LIBRARIES)
endif()