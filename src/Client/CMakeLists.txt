cmake_minimum_required(VERSION 3.14.0 )
project(ion_client LANGUAGES CXX)

## TESTING
# ENABLE_TESTING()
# find_package(GTest CONFIG REQUIRED)

## DEPENDECIES

set(Boost_USE_STATIC_LIBS ON)

add_compile_options(-bigobj)

# Set Source Header_Files
SET(PROJECT_SOURCE_FILES
source_files/talk_to_server.cc
main.cc
)

# Set Header_Files
SET(PROJECT_HEADER_FILES
header_files/talk_to_server.h
)

## TARGET LINK LIBRARIES



ADD_EXECUTABLE(client ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})


target_link_libraries(ion_client 
    PRIVATE 
    OpenSSL::SSL OpenSSL::Crypto
    ${Boost_LIBRARIES} 
    ) 

#ADD_SUBDIRECtORY(test_files)

