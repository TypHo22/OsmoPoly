add_library(geodesic geodesic.cpp UTM.cpp)

target_include_directories(geodesic # should be static here, since you don't want to deploy the lib by itself
    PUBLIC include # available to both math and linking libs
    )
