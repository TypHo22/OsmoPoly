cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

#
#set(PYTHON_INCLUDE_DIRS = /usr/include/python2.7 )
#set(PYTHON_LIBRARIES = /usr/lib/x86_64-linux-gnu/libpython2.7.so.1.0)
#
#if(NOT PYTHON_LIBRARIES_FOUND)
#    message(WARNING "PythonLibs 2.7 not found. Make sure you have installed python 2.7.
#       If that doesn't solve the problem, consult
#       https://github.com/lava/matplotlib-cpp")
#endif()
#

project(OsmoPoly C CXX)

find_package (Threads REQUIRED)

include_directories(matplotlib-cpp)

add_subdirectory(src/xml)
add_subdirectory(src/geodesic)
add_subdirectory(src/math)
add_subdirectory(src/model)


#add exectuable
add_executable(OsmoPoly src/main.cpp)

#target_include_directories(OsmoPoly PUBLIC PYTHON_INCLUDE_DIRS)
#target_link_libraries(OsmoPoly PRIVATE PYTHON_LIBRARIES)

target_link_libraries(OsmoPoly PRIVATE xml model)
target_link_libraries(OsmoPoly PRIVATE model geodesic)
target_link_libraries(OsmoPoly PRIVATE model math)
target_link_libraries(OsmoPoly PRIVATE Threads::Threads)



