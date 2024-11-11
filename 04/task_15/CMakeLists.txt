add_executable(add_type main.cc)

#find_package(Boost REQUIRED)

#target_include_directories(add_type PUBLIC ${Boost_INCLUDE_DIRS})
target_compile_features(add_type PUBLIC cxx_std_17)