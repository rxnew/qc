cmake_minimum_required(VERSION 2.8)

# json11 settings
include(ExternalProject)

ExternalProject_Add(
  json11
  GIT_REPOSITORY https://github.com/ngc-developers/json11.git
  GIT_TAG v1.2
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/projects/json11
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}
  #INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/graph
  INSTALL_COMMAND make install
  LOG_DOWNLOAD ON
  )

ExternalProject_Get_Property(json11 source_dir)

include_directories(
  ${source_dir}
  )

add_library(libjson11 STATIC IMPORTED GLOBAL)

set_property(
  TARGET libjson11
  PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/lib/libjson11.a
  )

set(LIBS libjson11)
