cmake_minimum_required(VERSION 2.8)

add_executable(algorithm-oracle-test
  is_mct_circuit_test.cpp
  )

target_link_libraries(algorithm-oracle-test
  gtest
  gtest_main
  pthread
  qc
  )

add_test(
  NAME algorithm-oracle
  COMMAND $<TARGET_FILE:algorithm-oracle-test>
  )

# run with: ctest -L lib
set_property(
  TEST algorithm-oracle
  PROPERTY LABELS lib algorithm algorithm-oracle
  )
