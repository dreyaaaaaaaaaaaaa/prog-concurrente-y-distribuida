add_executable(Practica3_4 main.cpp)
target_link_libraries(Practica3_4 PRIVATE Threads::Threads)
target_compile_features(Practica3_4 PRIVATE cxx_std_11)
