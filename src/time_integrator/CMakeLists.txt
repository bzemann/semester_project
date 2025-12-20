target_sources(pp_ader
  PRIVATE
    fvm_ssp_rk.cpp
)

target_include_directories(pp_ader
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
