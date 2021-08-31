cmake_minimum_required(VERSION 3.16)
project(hmm)
set(CMAKE_CXX_STANDARD 17)


################################
# setting path to include files 
################################

include_directories( 
    ${CMAKE_SOURCE_DIR}/include 
) 

######################
# compiled libraries
######################

add_library(model STATIC model.cpp)
add_library(alpha SHARED alpha.cpp)
add_library(beta SHARED beta.cpp)
