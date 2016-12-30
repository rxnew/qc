cmake_minimum_required(VERSION 2.8)

# graph settings
include(ExternalProject)

ExternalProject_Add(
  graph
  GIT_REPOSITORY https://github.com/rxnew/graph.git
  GIT_TAG v1.0
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/projects/graph
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )

ExternalProject_Get_Property(graph source_dir)

include_directories(
  ${source_dir}
  )
