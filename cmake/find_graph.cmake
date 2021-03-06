cmake_minimum_required(VERSION 3.2)

set(GRAPH_INCLUDE_PATHS ${GRAPH_INCLUDE_PATHS}
    /lib/include
    /lib/local/include)

if(INSTALL_EXTERNAL_PROJECTS_PREFIX)
  set(GRAPH_INCLUDE_PATHS ${GRAPH_INCLUDE_PATHS}
      ${INSTALL_EXTERNAL_PROJECTS_PREFIX}/include)
endif()

find_path(GRAPH_INCLUDE_PATH
          NAMES graph
          PATHS ${GRAPH_INCLUDE_PATHS})

if(NOT GRAPH_INCLUDE_PATH)
  include(${CMAKE_CURRENT_LIST_DIR}/graph.cmake)
endif()
