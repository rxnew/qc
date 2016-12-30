cmake_minimum_required(VERSION 2.8)

# graph settings
include(ExternalProject)

ExternalProject_Add(
  graph
  GIT_REPOSITORY https://github.com/rxnew/graph.git
  GIT_TAG v1.0
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/projects/graph
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}
  #INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/graph
  INSTALL_COMMAND make install
  LOG_DOWNLOAD ON
  )
