# - Find Snappy
#
#  SNAPPY_LIBS    - List of libraries when using Snappy.
#  SNAPPY_FOUND   - True if Snappy found.

get_filename_component(module_file_path ${CMAKE_CURRENT_LIST_FILE} PATH)

find_path(SNAPPY_INCLUDE NAMES snappy.h PATHS $ENV{VCPKG_INSTALL_DIR}/include /opt/local/include /usr/local/include /usr/include DOC "Path in which the file leveldb/db.h is located." )
mark_as_advanced(SNAPPY_INCLUDE)

find_library(SNAPPY_LIBS NAMES snappy libsnappy PATHS /usr/lib /usr/local/lib $ENV{VCPKG_INSTALL_DIR}/lib DOC "Path to snappy library." )
mark_as_advanced(SNAPPY_LIBS)

# Copy the results to the output variables.
if (SNAPPY_INCLUDE AND SNAPPY_LIBS)  
  set(SNAPPY_FOUND 1)
  include(CheckCXXSourceCompiles)
  set(CMAKE_REQUIRED_LIBRARY ${SNAPPY_LIBS})
  set(CMAKE_REQUIRED_INCLUDES ${SNAPPY_INCLUDE})
 else ()
   set(SNAPPY_FOUND 0)
 endif ()

 # Report the results.
 if (NOT SNAPPY_FOUND)
   set(SNAPPY_DIR_MESSAGE "SNAPPY_LIBS was not found. Install it or set SNAPPY_ROOT environment variable.")
   message(FATAL_ERROR "${SNAPPY_DIR_MESSAGE}")   
 endif ()