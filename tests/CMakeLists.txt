cmake_minimum_required(VERSION 3.20)

include(FetchContent)

# ---------------------------
# Fetch doctest (header-only)
# ---------------------------
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# ---------------------------
# Test executable (single runner with many suites)
# ---------------------------
add_executable(pp_ader_tests
  test_main.cpp
  fv_core/test_mesh.cpp
  fv_core/test_fluxes.cpp
  fv_core/test_field_bc.cpp
)

target_link_libraries(pp_ader_tests
  PRIVATE
    pp_ader
    doctest::doctest
)

# Make sure tests compile with the same C++ level
target_compile_features(pp_ader_tests PRIVATE cxx_std_23)

# Optional but nice warnings for tests too
if (MSVC)
  target_compile_options(pp_ader_tests PRIVATE /W4)
else()
  target_compile_options(pp_ader_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---------------------------
# Register doctest test cases with CTest
# ---------------------------
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(pp_ader_tests)
