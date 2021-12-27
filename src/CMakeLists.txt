cmake_minimum_required(VERSION 3.14.0 )
project(server LANGUAGES CXX)

## TESTING
#ENABLE_TESTING()


#find_package(GTest CONFIG REQUIRED)

## DEPENDECIES

set(Boost_USE_STATIC_LIBS ON)
find_package(OpenSSL REQUIRED)
add_compile_options(-bigobj)

# Set Source Header_Files
SET(PROJECT_SOURCE_FILES
source_files/server.cc
source_files/talk_to_client.cc
main.cc
)

# Set Header_Files
SET(PROJECT_HEADER_FILES
header_files/server.h
header_files/talk_to_client.h
header_files/setting.h
)

## TARGET LINK LIBRARIES



ADD_EXECUTABLE(ion_server ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})

target_link_libraries(server 
    PRIVATE 
    OpenSSL::SSL OpenSSL::Crypto
    ${Boost_LIBRARIES} 
    ) 

ADD_SUBDIRECtORY(client)
#ADD_SUBDIRECtORY(test_files)

