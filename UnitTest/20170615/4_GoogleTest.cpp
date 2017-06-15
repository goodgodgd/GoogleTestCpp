// Google Test

#include "gtest/gtest.h"

// 1. 단언문
//	- ASSERT_XX
//		NE(!=), EQ(==), LT(<), GT(>), LE(<=), GE(>=), TRUE, FALSE
//	: 하나라도 실패할 경우, 이후의 동작은 수행하지 않습니다.
//	=> 암묵적 설치/해체는 영향받지 않습니다.

//	- EXPECTED_XX
//	: 실패하더라도, 이후의 동작은 계속 됩니다.
//	=> 두 개 이상 단언문이 테스트 함수 내에 필요할 경우,
//		EXPECTED_XX를 사용하는 것이 좋습니다.

// 크기가 큰 클래스
class Resource {
public:
	Resource() { printf("자원 생성\n"); }
	~Resource() { printf("자원 소멸\n"); }
};

#if 0
TEST(GoogleTest, func1)
{
	// Arrange
	Resource* r = new Resource;
	int expected = 42;
	int actual = 40;
	// Act

	// Assert
	// FAIL();
	// 하나의 테스트 안에 단언문을 여러개 넣는것이 안좋다고 보는 시각도 있다
//	ASSERT_EQ(expected, actual);
//	ASSERT_EQ(expected, actual);
//	ASSERT_EQ(expected, actual);

	// 죽은 단언문이 생길수도 있으므로 => EXPECTED_XX
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual);

	// TearDown: inline TearDown은 assert 이후에 실행 안됨, 자원 누수
	delete r;
}
#endif

// 2. 테스트 비활성화
//	: 테스트의 결과에는 포함되지 않지만, 비활성화되어 있는 테스트가 있다는 사실을 지속적으로 알려야 한다.
//	TestCase 이름 또는 Test 함수의 이름이 DISABLED_ 시작한다면	비활성화 테스트로 인식됩니다.
// junit 4 - @Ignore
// junit 5 - @Disabled

// 단순 주석처리하면 개발자의 마음에서 잊혀진다. 
TEST(DISABLED_GoogleTest, DISABLED_func2)
{
	// Arrange
	Resource* r = new Resource;
	int expected = 42;
	int actual = 40;
	// Act

	// Assert
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual);

	// TearDown: inline TearDown은 assert 이후에 실행 안됨, 자원 누수
	delete r;
}

// 3. C++ 문자열
//	stl - string : ASSERT_EQ / ASSERT_NE 사용가능
//	const char*	 : ASSERT_STREQ / ASSERT_STRNE (위 함수를 쓰면 포인터를 비교하므로)
// 문자열의 단언문은 주의해서 사용해야

#include <string>
TEST(GoogleTest, func3)
{
	std::string expected = "hello";
	std::string actual = "hello";

	ASSERT_EQ(expected, actual);

	const char* s1 = "hello";
	const char* s2 = actual.c_str();
//	ASSERT_EQ(s1, s2);
	ASSERT_STREQ(s1, s2);
}

// 4. 부동소수점 비교
//	: 부동 소수점은 오차가 있습니다. 누적됩니다.
//	=> ASSERT_DOUBLE_EQ / ASSERT_FLOAT_EQ 제공
// 사용자가 직접 오차 범위를 설정하고 싶다면,
//	=> ASSERT_NEAR

TEST(GoogleTest, func4)
{
	double expected = 0.7;
	double actual = 0.1 * 7;

//	ASSERT_DOUBLE_EQ(expected, actual);
	ASSERT_NEAR(expected, actual, 0.00001);
}


// 5. 예외 테스트
// foo 에 잘못된 입력 값을 전달하였을 경우, invalid_argument에 대한 예외가 던져지는지 확인하고 싶다.
//	=>  ASSERT_THROW
//		ASSERT_ANY_THROW

void foo(const std::string& name)
{
	if (name.empty() || name.size() <= 5)
		throw std::invalid_argument("name should not be empty!");
	// ...
}

// gtest의 기능을 이용하지 않고 기본 기능만 사용했을 경우
#if 0
TEST(GoogleTest, func5)
{
	// 변수명, 문자열을 지을 때도 어떤 테스트인지 드러나게 해야 좋은 테스트 코드
	std::string bad_name = "bad";

	// 테스트는 가독성이 중요한데 이러한 제어구문은 바람직하지 않다.
	try {
		foo(bad_name);
		FAIL() << "예외가 발생하지 않음..";
	} catch (std::invalid_argument&) {
		SUCCEED();
	}
	catch (...) {
		FAIL() << "기대한 예외와 다름...";
	}
}
#endif

TEST(GoogleTest, func5)
{
	std::string bad_name = "bad";
//	ASSERT_THROW(foo(bad_name), std::invalid_argument);
	// 어떠한 예외든 던져야 한다.
	ASSERT_ANY_THROW(foo(bad_name));
}

