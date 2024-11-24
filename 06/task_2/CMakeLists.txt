add_executable(PImpl PImpl.cc)
add_executable(FastPImpl FastPImpl.cc)

target_compile_features(FastPImpl PUBLIC cxx_std_17)