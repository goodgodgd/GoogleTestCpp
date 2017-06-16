// 7_timeout.cpp
// 비기능(시간, 메모리) 테스트

// Timeout => 문제없이 잘 동작하였지만, 사용자가 요구하는 시간을 넘겼을 경우, 실패로 간주한다.
//	: Google Test에서는 지원하지 않습니다.

#include <Windows.h>					// #include <unistd.h>	: 리눅스
#define delay(sec)		Sleep(sec*1000)	// sleep(sec)			: 리눅스
#include <time.h>

#include <gtest/gtest.h>

// SUT
void foo()
{
	delay(3);
}

#if 0
// setup에서 teardown 함수가 호출 되는 사이의 시간을 측정하여 FAIL() 날린다.
class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	void SetUp() {
		// 실제 구현에서는 더 해상도 높은 함수 사용하자.
		startTime = time(0);
	}

	void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < 2) << "timed out: " << duration << " seconds";
		// 그런데 2초가 아니라 다른 시간으로 검사하고 싶으면??
		// 템플릿 사용!!
	}
};

TEST_F(TimeoutTest, foo)
{
	foo();
}
#endif



// setup에서 teardown 함수가 호출 되는 사이의 시간을 측정하여 FAIL() 날린다.
template<typename T, int N>
class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	void SetUp() {
		// 실제 구현에서는 더 해상도 높은 함수 사용하자.
		startTime = time(0);
	}

	void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < N) << "timed out: " << duration << " seconds";
		// 그런데 2초가 아니라 다른 시간으로 검사하고 싶으면??
		// 템플릿 사용!!
	}
};

// template<int N> 이 아니고 template<typename T, int N> 으로 선언하는 이유
// TimeoutTest<2> 만 하고 다른데서 또 TimeoutTest<2> 를 상속받는 객체가 나타나면
// 부모형이 같기 때문에 정적 변수를 공유하게 되는 "사고"가 날수 있다.
// 자식의 타입을 전달하면 모든 자식클래스들의 타입을 "다르게" 만들수 있다.

// CRTP: Curiously Recurring Template Pattern
//	=> 부모 클래스가 템플릿인데, 자식의 타입을 인자로 전달하는 설계 방식

class Timeout2SecTest : public TimeoutTest<Timeout2SecTest, 2> {
};

class Timeout5SecTest : public TimeoutTest<Timeout5SecTest, 5> {
};

TEST_F(Timeout5SecTest, foo)
{
	foo();
}

// TestCase 클래스 객체를 생성하는 것은 테스트 프레임워크에서 하기 땜누에
// 생성자의 인자를 전달하는 방식을 이용할 수는 없습니다.
// -> template 사용
