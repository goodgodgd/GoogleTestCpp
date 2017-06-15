// 1. gtest는 프로젝트에 포함되어서 항상 새롭게 빌드되어야 합니다.
//	=> gtest 라이브러리는 정적 라이브러리 사용이 권장됩니다.

// 2. gtest 정적 라이브러리 프로젝트

// Ctrl + F7 : Compile
// Ctrl + F5 : Compile + Run
#include "gtest/gtest.h"

// 아래의 main 코드는 반드시 포함되어야 합니다.
// 아래의 코드는 gtest에서 gtest_main.cc 라는 이름으로 제공됩니다.
// 정적 라이브러리에 포함해서 사용하면 편리합니다.
// main 함수를 안 써도 돼

// 리눅스에서는
// : ar crv gtest.a gtest-all.o gtest_main.o

// 테스트 함수 만드는 방법(매크로 사용): TEST(TestCase 이름, Test 이름)
TEST(TestCase, Test)
{
	// 1. 작성 중인 테스트는 반드시 실패시켜야 합니다. (완성 안됨)
	FAIL() << "작성 중 입니다.";

	// 2. 테스트가 실패할 경우, 실패의 이유를 반드시 제공해야 합니다.
}


#if 0
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif
