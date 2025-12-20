# Example 1
add_executable(my_test
  test.cpp
)

target_link_libraries(my_test
  PRIVATE
    project_options
    project_warnings
    pp_ader
)

# Example 2 (repeat as needed)
# add_executable(example_whatever example_whatever.cpp)
# target_link_libraries(example_whatever PRIVATE project_options 
# project_warnings fv_core time_integrator)
