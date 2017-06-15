// 2_3A
// : 테스트 함수를 작성하는 방법

// SUT (테스트 대상 시스템), CUT
//	: System Under Test, Code (Class) Under Test

class Calculator {
	int value;
public:
	Calculator() : value(0) {}

	void plus(int n) { value += n; }
	void minus(int n) { value -= n; }
	
	int display() { return value; }
};
// 여기까지가 제품 코드

#include "gtest/gtest.h"

// 3A (TDD) => BDD (Behavior, 행위 주도 개발), 테스트 코드의 가독성을 중요시함. 코드를 사람의 문장처럼
// Arrange: 객체를 생성하고, 필요한 경우 적절하게 설정한다.	- Given (BDD)
// Act: 객체에 작용을 가한다.								- When (BDD)
// Assert: 기대하는 바를 단언한다.						- Then (BDD)

#if 0
TEST(CalculatorTest, plus)
{
	// Arrange
	Calculator* calculator = new Calculator;

	// Act
	calculator->plus(2);
	calculator->plus(2);

	// Assert
	if (calculator->display() != 4)
		FAIL() << "2 더하기 2를 하였을 때";
}
#endif

// 테스트의 핵심
// 1. 가독성
// 2. 신뢰성
// 3. 유지보수성
//	: 테스트 함수 안에서는 반복문이나 조건문 같은 제어 흐름 구문은 사용하지 않는 것이 좋다.
//	조건문을 써야 하는 경우는 차라리 별도의 테스트 케이스로 만드는 것이 좋다.

// 각 테스트가 어떤 시나리오로 동작하는지 여부를 테스트 함수를 통해 드러내는 것이 좋다.
// 좀 더 자세한 이름 필요
// ex) 테스트대상함수_시나리오_기대값
// cpp 표준은 유니코드 아닌 아스키코드 언어라서 한글로는 네이밍 못함.
// VS는 가능. 표준에 벗어나서 확장함, 자바는 가능

TEST(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	// Arrange
	Calculator* calculator = new Calculator;
	// => Fixture Setup

	// Act
	calculator->plus(2);
	calculator->plus(2);

	// Assert
	// 1. 아래의 코드를 캡슐화한 함수를 제공합니다.
	// => ASSERT_EQ(기대값, 실제값)
	
	// 2. 인자의 순서를 주의해야 합니다.
	// 두가지 다 가능하지만 기대값을 먼저 넣는다. (실행문 해석 쉬워짐)
	ASSERT_EQ(4, calculator->display()) << "2 더하기 2를 하였을 때";
	//	ASSERT_EQ(calculator->display(), 4);

	//	if (calculator->display() != 4)
	//		FAIL() << "2 더하기 2를 하였을 때";
}

