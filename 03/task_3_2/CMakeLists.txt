add_executable(figures main.cc)
add_library(geom geom.cc)

target_include_directories(geom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(figures geom)
