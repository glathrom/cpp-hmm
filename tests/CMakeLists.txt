cmake_minimum_required(VERSION 3.16)
project(hmm)
set(CMAKE_CXX_STANDARD 17)


################################
# setting path to include files 
################################

include_directories( 
    ../include 
) 

link_directories(
    ../lib
)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
find_package(model REQUIRED)
message(STATUS "model_DIR = ${model_DIR}")

#find_package(alpha PATHS ${CMAKE_SOURCE_DIR}/lib)
#find_package(beta PATHS ${CMAKE_SOURCE_DIR}/lib)

######################
# target executable
######################

add_executable(test_model test_model.cpp)
target_link_libraries(test_model model)
