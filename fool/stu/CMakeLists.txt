
add_executable(fool main.cpp)
target_link_libraries(fool fmt range-v3)
target_include_directories(fool PRIVATE ${CMAKE_SOURCE_DIR})