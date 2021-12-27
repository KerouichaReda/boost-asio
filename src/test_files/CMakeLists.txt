cmake_minimum_required(VERSION 3.14)



set(PROJECT_SOURCE_FILES
    myclass_test.cc)

ADD_EXECUTABLE(MyClass_Test ${PROJECT_SOURCE_FILES})



 target_link_libraries( MyClass_Test PRIVATE
 GTest::gmock
 GTest::gtest
 GTest::gmock_main
 GTest::gtest_main

 )
 enable_testing()



ADD_TEST(
    NAME project_test
    COMMAND project_test)