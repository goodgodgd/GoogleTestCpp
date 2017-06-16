// 테스트 전용 하위 클래스
//	: Test Specific Subclass Pattern
// 1. SUT에 검증해야 하는 상태가 존재하지 않을 때, 어떻게 하면 테스트 가능하게 할 수 있는가?
// 2. 또는 SUT에 검증해야 하는 상태에 접근할 수 없을 때 (isStart)

// SUT
#include <stdio.h>

class Engine {
protected:
	bool isStart;

public:
	virtual void start() {
		printf("start engine...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* e) : engine(e) {}

	void go() { engine->start(); }
};

#include "gtest/gtest.h"

class CarTest : public ::testing::Test {

};

// 자동차의 go가 호출되었을 때ㅣ, 엔진의 상태를 검증하고 싶다.
#if 0
TEST_F(CarTest, go)
{
	Engine engine;
	Car car(&engine);

	car.go();
	// 이 밑에 단언문이 없으면 절대 실패하지 않는다. 그냥 커버리지만 높이는 함수
}
#endif


// 상속 => 부모클래스와 자식클래스
// 상속은 재사용이 목적이 아니라 다형성이 목표
// 다형성이 성립하기 위해서는 is-a 관계, circle is a shape

// 제품 코드를 건드리지 않고 테스트 가능하게 만든다.
// 하지만 테스트 가능한 설계를 해줘야... private 안되, virtual 선언
class TestEngine : public Engine {
	// 테스트에 필요한 상태를 추가한다.
	bool isStart_;
public:
	TestEngine() : isStart_(false) {}
	void start() {
		Engine::start();	// 부모의 기능을 이용한다.
		isStart_ = true;	// 확인하고 싶은 상태 변경
	}

	// 테스트함수 에서 이용할 수 있는 함수를 제공햔다.
	bool isStart() { return isStart_; }
};

// 테스트 대상을 수정하지 않고 (제품코드) 원하는 테스트를 할 수 있다.

// 자동차의 go가 호출되었을 때ㅣ, 엔진의 상태를 검증하고 싶다.
TEST_F(CarTest, go)
{
	TestEngine engine;
	Car car(&engine);	// is-a 관계로 TestEngine을 넣어도 상관없다.

	car.go();
	// 이 밑에 단언문이 없으면 절대 실패하지 않는다. 그냥 커버리지만 높이는 함수
	ASSERT_TRUE(engine.isStart()) << "자동차가 go할 때";
}

// 1. 부모가 제공하는 기능이 반드시 가상 함수로 구현되어 있어야 합니다.
//	일반 함수(정적 바인딩) vs 가상 함수(동적 바인딩)
// 2. 부모의 기능이 private 이면 안된다.

// 바인딩: 어떤 함수를 호출할지 결정하는 것