add_executable(Practica3_3 main.cpp)
target_link_libraries(Practica3_3 PRIVATE Threads::Threads)
target_compile_features(Practica3_3 PRIVATE cxx_std_11)
