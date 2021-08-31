cmake_minimum_required(VERSION 3.16)
project(hmm)
set(CMAKE_CXX_STANDARD 17)


################################
# setting path to include files 
################################

include_directories( 
    ${CMAKE_SOURCE_DIR}/include 
) 

find_package(model PATHS ${CMAKE_SOURCE_DIR}/lib)
find_package(alpha PATHS ${CMAKE_SOURCE_DIR}/lib)
find_package(beta PATHS ${CMAKE_SOURCE_DIR}/lib)

######################
# target executable
######################

add_executable(application test_model.cpp)
target_link_libraries(application model alpha beta)
