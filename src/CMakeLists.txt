find_package(Eigen3 3.4.1 REQUIRED NO_MODULE)

add_library(pp_ader STATIC)

# Public include root: allows #include "fv_core/mesh.hpp" etc. if you want later
target_include_directories(pp_ader
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pp_ader
  PUBLIC
    project_options
    project_warnings
    Eigen3::Eigen
)

add_subdirectory(fv_core)
add_subdirectory(time_integrator)
