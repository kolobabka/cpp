add_executable(siamese_problem main.cc)
add_library(siamese main.cc)

target_include_directories(siamese PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(siamese_problem siamese)