add_executable (test1 "test1.cpp")
target_compile_features(test1 PRIVATE cxx_std_20)
target_link_libraries(test1 PUBLIC RTTR::Core_Lib)