add_executable(Prac_1M main.cpp)
target_link_libraries(Prac_1M PRIVATE Threads::Threads)
target_compile_features(Prac_1M PRIVATE cxx_std_11)
