// 전역 픽스쳐
//	=> Google Test 에서만 제공하는 기능

// 테스트 프로그램이 시작할 때 SetUp
// 테스트 프로그램이 종료하기 전에 TearDown
// 라이브러리나 전역 객체 셋업해야 할 때

// "5_스위트픽스쳐2" 에서 "static void SetUpTestCase()" 는 
//	테스트케이스 클래스의 설치/해체를 한번만 하는 것이고
// 전역 픽스쳐는 전체 프로그램 단위에서 한번씩만 설치/해체 하는 것이다.

#include "gtest/gtest.h"

// ::testing::Environment 이걸 상속한 것을 생성해야 전역 픽스쳐 설치됨
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
//	: 전역 픽스쳐를 등록해야 하는 경우, 직접 main을 만드는 것이 좋습니다.

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	// 직접 픽스쳐 셋업을 main안에 인라인으로 구현
	::testing::AddGlobalTestEnvironment(new TestEnvironment);

	return RUN_ALL_TESTS();
}


// 일반적으로 두 번째 방법 권장
// 전역변수 권장안하는 이유: C++ 문법 자체가 모호, ISO C++ 표준이 촘촘하지 않아, undefined 많아.
// 전역변수 생성자/소멸자의 호출 시점이 명확하지 않음
// C++에서 싱글톤을 쓰는 이유는 생성/소멸 시점이 명확하기 때문

