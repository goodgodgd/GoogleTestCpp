// 전역 픽스쳐
//	=> Google Test 에서만 제공하는 기능

// 테스트 프로그램이 시작할 때 SetUp
// 테스트 프로그램이 종료하기 전에 TearDown

#include "gtest/gtest.h"

class TestEnvironment : public ::testing::Environment {
public:
	void SetUp() {
		printf("Global Setup\n");
	}

	void TearDown() {
		printf("Global TearDown\n");
	}
};

TEST(Sample, foo)
{
	printf("sample foo\n");
}

// 설치하는 방법
//	1) 전역 변수 => main을 제공하지 않을 경우
// main함수 실행전에 전역변수 초기화 이용
#if 0
::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new TestEnvironment);
#endif

//	2) main 함수 => main을 직접 만들 경우
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::AddGlobalTestEnvironment(new TestEnvironment);

	return RUN_ALL_TESTS();
}


// 일반적으로 두 번째 방법 권장
// 전역변수 권장안하는 이유: C++ 문법 자체가 모호, ISO C++ 표준이 촘촘하지 않아, undefined 많아.
// 전역변수 생성자/소멸자의 호출 시점이 명확하지 않음
// C++에서 싱글톤을 쓰는 이유는 생성/소멸 시점이 명확하기 때문

