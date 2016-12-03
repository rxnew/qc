cmake_minimum_required(VERSION 2.8)

add_executable(algorithm-general-test
  decomp_to_single_target_gates_test.cpp
  )

target_link_libraries(algorithm-general-test
  gtest
  gtest_main
  pthread
  qc
  )

add_test(
  NAME algorithm-general
  COMMAND $<TARGET_FILE:algorithm-general-test>
  )

# run with: ctest -L lib
set_property(
  TEST algorithm-general
  PROPERTY LABELS lib algorithm-general
  )
