cmake_minimum_required(VERSION 3.16)
project(hmm)
set(CMAKE_CXX_STANDARD 17)

######################################################
# setting paths for libraries and executable outputs
######################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

################################
# setting path to include files 
################################

include_directories( 
    ${CMAKE_SOURCE_DIR}/include 
) 

######################
# imported libraries
######################

#add_library(dono STATIC IMPORTED)
#set_target_properties(dono PROPERTIES 
#    IMPORTED_LOCATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libdono.a
#)

######################
# compiled libraries
######################

add_library(model STATIC ${CMAKE_SOURCE_DIR}/src/model.cpp)
#add_library(goodbye SHARED ${CMAKE_SOURCE_DIR}/src/goodbye.cpp)

######################
# target executable
######################

set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_executable(application ${SOURCES})
target_link_libraries(application model)
