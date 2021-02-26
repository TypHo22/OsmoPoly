add_library(math hull.cpp)

target_include_directories(math # should be static here, since you don't want to deploy the lib by itself
    PUBLIC include # available to both math and linking libs
)


target_link_libraries(math PRIVATE geodesic) # change PRIVATE to PUBLIC, if Algebra.h is included in a public header
target_link_libraries(math PRIVATE model) # change PRIVATE to PUBLIC, if Algebra.h is included in a public header
