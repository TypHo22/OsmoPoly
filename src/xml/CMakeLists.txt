#include_directories(${OsmoPoly}src/xml)
#add_library(xml fileHandler.cpp tinyxml2.cpp)
#target_link_libraries(xml model)

add_library(xml STATIC
    fileHandler.cpp
    tinyxml2.cpp
)

target_include_directories(xml PUBLIC include)

target_link_libraries(xml PRIVATE model) # change PRIVATE to PUBLIC, if Algebra.h is included in a public header
