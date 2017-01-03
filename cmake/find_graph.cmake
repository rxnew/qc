cmake_minimum_required(VERSION 3.2)

set(GRAPH_INCLUDE_PATHS ${GRAPH_INCLUDE_PATHS}
    /lib/include
    /lib/local/include)

set(GRAPH_INCLUDE_PATH GRAPH_INCLUDE_PATH-NOTFOUND)

find_path(GRAPH_INCLUDE_PATH
          NAMES graph
          PATHS ${GRAPH_INCLUDE_PATHS})

message(${GRAPH_INCLUDE_PATHS})
message(${GRAPH_INCLUDE_PATH})

if(NOT GRAPH_INCLUDE_PATH)
  include(${CMAKE_CURRENT_LIST_DIR}/graph.cmake)
endif()
