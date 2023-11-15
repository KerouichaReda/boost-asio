cmake_minimum_required(VERSION 3.14.0 )
project(server LANGUAGES CXX)

## DEPENDECIES

set(BOOST_ROOT "C:/lib/boost_1_82_0")
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib/)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS thread)

# Set Source Header_Files
SET(PROJECT_SOURCE_FILES
server.cc
session.cc
main.cc
conf.cc
)

# Set Header_Files
SET(PROJECT_HEADER_FILES
server.h
conf.h
session.h
)

## TARGET LINK LIBRARIES
include_directories(${Boost_INCLUDE_DIR})
ADD_EXECUTABLE(server ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})


target_link_libraries(server 
    PRIVATE    
    ${Boost_LIBRARIES} 
) 