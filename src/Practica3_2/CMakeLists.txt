add_executable(Practica3_2 Main.cpp)
target_link_libraries(Practica3_2 PRIVATE Threads::Threads)
target_compile_features(Practica3_2 PRIVATE cxx_std_11)
