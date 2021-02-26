#include_directories(${OsmoPoly}model)
#add_library(model model.cpp modelGPX.cpp modelOSM.cpp node.cpp)
add_library(model model.cpp modelGPX.cpp modelOSM.cpp node.cpp)

target_include_directories(model # should be static here, since you don't want to deploy the lib by itself
    PUBLIC include # available to both math and linking libs
)
