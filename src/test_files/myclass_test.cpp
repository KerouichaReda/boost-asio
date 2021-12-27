#include<gtest/gtest.h>

#include"../Header_Files/myclass.hpp"
#include"../Source_Files/myclass.cpp"

int main(int argc, char** argv) {
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


TEST(Test1, return_zero) {	
	int result=0;
	ASSERT_EQ(result, 0);
}
