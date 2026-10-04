add_executable(Practica3_1 Main.cpp)
target_link_libraries(Practica3_1 PRIVATE Threads::Threads)
target_compile_features(Practica3_1 PRIVATE cxx_std_11)
