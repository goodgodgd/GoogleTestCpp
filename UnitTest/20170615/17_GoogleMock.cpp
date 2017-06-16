// 한계: C++은 Reflection을 지원하지 않습니다.
// Reflection
//	1) 런타임에 타입을 체크할 수 있습니다. - RTTI C++에 있어
//	2) 동적 생성
//		: 런타임에 원하는 타입의 객체를 생성할 수 있습니다.
//		=> 동적으로 MockObject를 생성할 수 있습니다.
// !! scripts/gmock_gen.py를 실행하면 자동으로 MockObject 클래스를 자동으로 만들어준다.

#include <string>

struct Unit {
	virtual ~Unit() {}
	virtual void stop() = 0;
	virtual void say(const std::string& message) = 0;
	virtual void attack(Unit* p) = 0;
	virtual void move(int x, int y) = 0;
	virtual void getX() const = 0;
	virtual void getY() const = 0;
};

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// 모의 객체 - 행위 기반 테스트
// 1. 메소드 호출 여부
// 2. 메소드 호출 횟수
// 3. 메소드 호출 순서

// 일반 멤버 함수
// : MOCK_METHOD{인자의 개수}(인자의 이름, 함수의 타입);
// const 멤버 함수
// : MOCK_CONST_METHOD{인자의 개수}(인자의 이름, 함수의 타입);

// 구체 클래스가 아닌 인터페이스를 통해 만들자.

// googlemock/scripts/generator/mock_gen.py를 이용하면 자동으로 생성 가능 합니다.
// 근데 이걸로 만든 헤더에 include 가드를 추가해줘야 함
// #ifndef HEADER \ #define HEADER \ #endif
class MockUnit : public Unit {
public:
	MOCK_METHOD0(stop, void());
	MOCK_METHOD1(say, void(const std::string& message));
	MOCK_METHOD1(attack, void(Unit* p));
	MOCK_METHOD2(move, void(int x, int y));
	MOCK_CONST_METHOD0(getX, void());
	MOCK_CONST_METHOD0(getY, void());
};


// 1. 호출 여부
void foo(Unit* p)
{
	p->stop();
}

TEST(GMockTest, foo)
{
	// google mock은 arrange, assert, act 순서로 실행한다. gmock의 고유 특징
	// 1. 준비 단계 - Arrange
	MockUnit mock;

	// 2. 기대하는 바를 단언한다 - Assert
	EXPECT_CALL(mock, stop());	// mock에서 stop이 호출되어야 한다.

	// 3. mock에 의존하는 SUT를 실행한다. - Act
	foo(&mock);
}

// 나쁜예
// gmock은 모의 객체가 파괴되는 시점에 행위 기반 검증이 실행된다.
TEST(GMockTest, foo_bad)
{
	MockUnit* mock = new MockUnit;
	EXPECT_CALL(*mock, stop());	// mock에서 stop이 호출되어야 한다.
	foo(mock);
	delete mock;
}


// 2. 호출 횟수 판단
void goo(Unit* p)
{
	p->stop();
	p->stop();
	p->stop();
}

using ::testing::AnyNumber;
TEST(GMockTest, goo)
{
	MockUnit mock;
	// 세 번 실행하는가?
	EXPECT_CALL(mock, stop()).Times(3);
//	EXPECT_CALL(mock, stop()).Times(AnyNumber());	// 횟수 상관없이 호출 됐는지 확인
	goo(&mock);
}

// C++의 최대 강점: stack에 객체를 생성할 수 있다. 동적 생성은 과정이 복잡해
// gtest는 stack에 객체를 생성하는 것을 권장해


// 3. 메소드 호출 순서
void hoo(Unit* p)
{
	p->move(10, 42);
	p->stop();
}

// 메소드 호추 순서의 검증이 필요하다면, InSequence 객체만 생성하면 됩니다.
using ::testing::InSequence;
TEST(GMockTest, hoo) {
	InSequence seq;
	MockUnit mock;

	// 기대하는 호출 순서대로
	EXPECT_CALL(mock, move(10, 42));
	EXPECT_CALL(mock, stop());

	hoo(&mock);
}



// Mockito, Google Mock
//	=> 격리 프레임워크

// Mock => 행위 검증
// Stub, Fake => 격리

class Time {
public:
	virtual ~Time() {}
	virtual std::string getTime() { return "16:42";  }
};

// 일반적으로 stub을 만드는데 mock을 통해서도 해겨할 수 있다.
class MockTime : public Time {
public:
	MOCK_METHOD0(getTime, std::string());
};

// 자정에 동작하는 부분을 독립적으로 검증하고 싶다.
using ::testing::Return;
TEST(TimeTest, Stub)
{
	MockTime stub;
	// call이 됐을 때 자정("00:00") 리턴
	// MockTime은 Time을 상속받아 구체 클래스를 생성하는데 리턴값을 정해지지 않았다.
	// Return()으로 리턴값을 정해줄 수 있다.
	ON_CALL(stub, getTime()).WillByDefault(Return("00:00"));

	printf("%s\n", stub.getTime().c_str());
}
