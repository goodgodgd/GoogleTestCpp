
class Calculator {
	int value;
public:
	Calculator() : value(0) {}

	void plus(int n) { value += n; }
	void minus(int n) { value -= n; }

	int display() { return value; }
};


// Test Fixture
// 정의: xUnit Test Pattern에서 SUT를 실행하기 위해 준비해야 하는것
// => 픽스쳐를 구성하는 모든 로직 부분을 '픽스쳐 설치' 라고 합니다.

// 픽스쳐 설치 방법 1. 인라인 픽스쳐 설치
// : 모든 픽스쳐의 설치를 테스트 함수 안에서 처리한다.

// (아래 코드의)
// 장점: 픽스쳐의 설치와 검증 로직이 하나의 함수 안에 존재하기 때문에 인과관계를 쉽게 파악할 수 있다.
// 단점: 모든 테스트 함수 안에서 [코드 중복]이 발생한다.

// [코드 중복]: 테스트 냄새
// 만약 Calculator 생성 방법이 바뀌면 이것을 생성하는 모든 중복 코드를 수정해야 한다.
// => 깨지기 쉬운 테스트를 만들 확률이 높다.


#include "gtest/gtest.h"

#if 0
TEST(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	// Arrange
	Calculator* calculator = new Calculator;

	// Act
	calculator->plus(2);
	calculator->plus(2);

	// Assert
	ASSERT_EQ(4, calculator->display()) << "2 더하기 2를 하였을 때";
}

TEST(CalculatorTest, minus)
{
	Calculator* calculator = new Calculator;

	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()); << "-2-2";
}
#endif

// 픽스쳐 설치 방법 2. 위임 설치
// 1. 동일한 픽스쳐를 가진 테스트 함수를 클래스로 묶는다.
// 2. 픽스쳐 설치에 관한 중복되는 코드를 함수로 제공한다.

// 동일한 픽스쳐를 가진 클래스 => 테스트 케이스 (클래스)
// TestCase class를 만드는 방법

#if 0
class CalculatorTest : public ::testing::Test {
	// Google Test에서는 반드시 Test Utility 함수의 접근 지정자는
	// protected로 제공해야 합니다.

protected:
	// SUT의 생성 방법이 변경되어도 이제는 create 함수 하나만 수정하면 됩니다.
	Calculator* create() {
		return new Calculator;
	}
};

// 픽스쳐를 공유하는 함수: TEST_F
TEST_F(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	// Arrange
	Calculator* calculator = create();

	// Act
	calculator->plus(2);
	calculator->plus(2);

	// Assert
	ASSERT_EQ(4, calculator->display()) << "2 더하기 2를 하였을 때";
}

TEST_F(CalculatorTest, minus)
{
	Calculator* calculator = create();

	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()) << "-2-2";
}

// 모든 테스트 케이스는 testing::Test 의 자식
// TEST_F()는 첫번째 인자의 자식을 따로 만든다.
// 내부적으로 CalculatorTest.plus 같은 새로운 클래스를 만든다.
// 고로 private 멤버는 사용 불가하고 적어도 protected로 선언해야
#endif


// 픽스쳐 설치 방법 3. 암묵적 설치 / 해체
//	: 테스트 프레임워크에서 지원하는 기능
//	=> 여러 테스트에서 같은 테스트 픽스쳐를 SetUp/TearDown 함수를 통해 설치한다.

// 장점: 테스트 코드 중복을 제거하고, 꼭 필요하지 않은 상호작용을 캡슐화 할 수 있다.
// 단점: 픽스쳐의 설치코드가 함수 밖에 존재하기 때문에, (명시적으로 보이지 않기 때문에)
//		테스트 함수만으로 코드를 이해하기 어렵다. (지금은 다 이렇게 쓴다.)
// 이 방법이 대세!!

#if 0
class CalculatorTest : public ::testing::Test {
protected:
	Calculator* calculator;

	// 각각의 Run을 실행하기 전에 SetUp을 실행한다.
	void SetUp() {
		printf("SetUp\n");
		calculator = new Calculator;
	}
};

TEST_F(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	printf("plus\n");
	calculator->plus(2);
	calculator->plus(2);

	ASSERT_EQ(4, calculator->display()) << "2 더하기 2를 하였을 때";
}

TEST_F(CalculatorTest, minus)
{
	printf("minus\n");
	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()) << "-2-2";
}
#endif

// 4 단계 테스트
//	: xUnit Test Pattern에서 테스트 함수를 구성하는 방법
// 1단계: 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업을 한다.
// 2단계: SUT와 상호작용을 한다.
// 3단계: 기대 결과를 확인한다.
// 4단계: 테스트의 픽스쳐를 해체해서, 테스트 시작 상태로 되돌려 놓는다. - 중요!

class CalculatorTest : public ::testing::Test {
public:
	CalculatorTest() { printf("CalculatorTest created\n"); }
protected:
	Calculator* calculator;

	// 각각의 Run을 실행하기 전에 SetUp을 실행한다.
	void SetUp() {
		printf("SetUp\n");
		calculator = new Calculator;
	}

	// 암묵적 해체
	// new를 했으면 delete도 해줘야 함
	void TearDown() {
		printf("TearDown\n");
		delete calculator;
		// 자바의 경우 delete는 필요 없지만 운영체제의 자원은 반납해야 한다. 스레드 등
	}
};

TEST_F(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	printf("plus\n");
	calculator->plus(2);
	calculator->plus(2);

	ASSERT_EQ(4, calculator->display()) << "2 더하기 2를 하였을 때";
}

TEST_F(CalculatorTest, minus)
{
	printf("minus\n");
	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()) << "-2-2";
}

// xUnit Test Framework이 테스트케이스 안의 함수를 수행하는 방식
// => 신선한 픽스쳐의 전략
//	: 각 테스트 함수가 독립적으로 구성되어, 언제 어떻게 실행하더라도 항상 동일한 결과가 나올 수 있도록 한다.

// TestCase* test = new TestCase();
// test->SetUp();
// test->foo();
// test->TearDown();

//	매번 테스트 케이스 클래스를 매번 새롭게 생성한다. 이전 테스트의 영향을 받지 않기 위해
// TestCase* test = new TestCase();
// test->SetUp();
// test->goo();
// test->TearDown();

// nUnit은 신선한 픽스쳐가 안들어 갔는데... 실수란다;;
// 대부분의 xUnit은 신선한 픽스쳐 사용

