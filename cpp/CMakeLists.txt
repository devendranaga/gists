cmake_minimum_required(VERSION 2.4)

project(CPPLearning)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

add_executable(destructor destructor.cpp)
add_executable(namespaces namespaces.cpp)
add_executable(std_makeshared_class std_makeshared_class.cpp)
add_executable(std_shareptr_makeshared std_shareptr_makeshared.cpp)
add_executable(string2 string2.cpp)
add_executable(strings strings.cpp)
add_executable(to_string to_string.cpp)
add_executable(vector_sort vector_sort.cpp)