add_executable(inheritance main.cc)
add_library(inher main.cc)

target_include_directories(inher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(inher PUBLIC cxx_std_20)
target_link_libraries(inheritance inher m)