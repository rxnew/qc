cmake_minimum_required(VERSION 3.2)

set(JSON11_INCLUDE_PATHS ${JSON11_INCLUDE_PATHS}
    /lib/include
    /lib/local/include)

set(JSON11_LIBRARY_PATHS ${JSON11_LIBRARY_PATHS}
    /usr/lib
    /usr/local/lib)

set(JSON11_INCLUDE_PATH JSON11_INCLUDE_PATH-NOTFOUND)
set(JSON11_LIBRARY JSON11_LIBRARY-NOTFOUND)

find_path(JSON11_INCLUDE_PATH
          NAMES json11.hpp
          PATHS ${JSON11_INCLUDE_PATHS})

find_library(JSON11_LIBRARY
             NAMES json11
             PATHS ${JSON11_LIBRARY_PATHS})

if(NOT JSON11_INCLUDE_PATH OR NOT JSON11_LIBRARY)
  include(${CMAKE_CURRENT_LIST_DIR}/json11.cmake)
endif()
