
class Calculator {
	int value;
public:
	Calculator() : value(0) {}

	void plus(int n) { value += n; }
	void minus(int n) { value -= n; }

	int display() { return value; }
};


// Test Fixture
// ����: xUnit Test Pattern���� SUT�� �����ϱ� ���� �غ��ؾ� �ϴ°�
// => �Ƚ��ĸ� �����ϴ� ��� ���� �κ��� '�Ƚ��� ��ġ' ��� �մϴ�.

// �Ƚ��� ��ġ ��� 1. �ζ��� �Ƚ��� ��ġ
// : ��� �Ƚ����� ��ġ�� �׽�Ʈ �Լ� �ȿ��� ó���Ѵ�.

// (�Ʒ� �ڵ���)
// ����: �Ƚ����� ��ġ�� ���� ������ �ϳ��� �Լ� �ȿ� �����ϱ� ������ �ΰ����踦 ���� �ľ��� �� �ִ�.
// ����: ��� �׽�Ʈ �Լ� �ȿ��� [�ڵ� �ߺ�]�� �߻��Ѵ�.

// [�ڵ� �ߺ�]: �׽�Ʈ ����
// ���� Calculator ���� ����� �ٲ�� �̰��� �����ϴ� ��� �ߺ� �ڵ带 �����ؾ� �Ѵ�.
// => ������ ���� �׽�Ʈ�� ���� Ȯ���� ����.


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
	ASSERT_EQ(4, calculator->display()) << "2 ���ϱ� 2�� �Ͽ��� ��";
}

TEST(CalculatorTest, minus)
{
	Calculator* calculator = new Calculator;

	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()); << "-2-2";
}
#endif

// �Ƚ��� ��ġ ��� 2. ���� ��ġ
// 1. ������ �Ƚ��ĸ� ���� �׽�Ʈ �Լ��� Ŭ������ ���´�.
// 2. �Ƚ��� ��ġ�� ���� �ߺ��Ǵ� �ڵ带 �Լ��� �����Ѵ�.

// ������ �Ƚ��ĸ� ���� Ŭ���� => �׽�Ʈ ���̽� (Ŭ����)
// TestCase class�� ����� ���

#if 0
class CalculatorTest : public ::testing::Test {
	// Google Test������ �ݵ�� Test Utility �Լ��� ���� �����ڴ�
	// protected�� �����ؾ� �մϴ�.

protected:
	// SUT�� ���� ����� ����Ǿ ������ create �Լ� �ϳ��� �����ϸ� �˴ϴ�.
	Calculator* create() {
		return new Calculator;
	}
};

// �Ƚ��ĸ� �����ϴ� �Լ�: TEST_F
TEST_F(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	// Arrange
	Calculator* calculator = create();

	// Act
	calculator->plus(2);
	calculator->plus(2);

	// Assert
	ASSERT_EQ(4, calculator->display()) << "2 ���ϱ� 2�� �Ͽ��� ��";
}

TEST_F(CalculatorTest, minus)
{
	Calculator* calculator = create();

	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()) << "-2-2";
}

// ��� �׽�Ʈ ���̽��� testing::Test �� �ڽ�
// TEST_F()�� ù��° ������ �ڽ��� ���� �����.
// ���������� CalculatorTest.plus ���� ���ο� Ŭ������ �����.
// ��� private ����� ��� �Ұ��ϰ� ��� protected�� �����ؾ�
#endif


// �Ƚ��� ��ġ ��� 3. �Ϲ��� ��ġ / ��ü
//	: �׽�Ʈ �����ӿ�ũ���� �����ϴ� ���
//	=> ���� �׽�Ʈ���� ���� �׽�Ʈ �Ƚ��ĸ� SetUp/TearDown �Լ��� ���� ��ġ�Ѵ�.

// ����: �׽�Ʈ �ڵ� �ߺ��� �����ϰ�, �� �ʿ����� ���� ��ȣ�ۿ��� ĸ��ȭ �� �� �ִ�.
// ����: �Ƚ����� ��ġ�ڵ尡 �Լ� �ۿ� �����ϱ� ������, (��������� ������ �ʱ� ������)
//		�׽�Ʈ �Լ������� �ڵ带 �����ϱ� ��ƴ�. (������ �� �̷��� ����.)
// �� ����� �뼼!!

#if 0
class CalculatorTest : public ::testing::Test {
protected:
	Calculator* calculator;

	// ������ Run�� �����ϱ� ���� SetUp�� �����Ѵ�.
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

	ASSERT_EQ(4, calculator->display()) << "2 ���ϱ� 2�� �Ͽ��� ��";
}

TEST_F(CalculatorTest, minus)
{
	printf("minus\n");
	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()) << "-2-2";
}
#endif

// 4 �ܰ� �׽�Ʈ
//	: xUnit Test Pattern���� �׽�Ʈ �Լ��� �����ϴ� ���
// 1�ܰ�: �׽�Ʈ�� �Ƚ��ĸ� ��ġ�ϰų�, ���� ����� �����ϱ� ���� �ʿ��� ���� ����ִ� �۾��� �Ѵ�.
// 2�ܰ�: SUT�� ��ȣ�ۿ��� �Ѵ�.
// 3�ܰ�: ��� ����� Ȯ���Ѵ�.
// 4�ܰ�: �׽�Ʈ�� �Ƚ��ĸ� ��ü�ؼ�, �׽�Ʈ ���� ���·� �ǵ��� ���´�. - �߿�!

class CalculatorTest : public ::testing::Test {
public:
	CalculatorTest() { printf("CalculatorTest created\n"); }
protected:
	Calculator* calculator;

	// ������ Run�� �����ϱ� ���� SetUp�� �����Ѵ�.
	void SetUp() {
		printf("SetUp\n");
		calculator = new Calculator;
	}

	// �Ϲ��� ��ü
	// new�� ������ delete�� ����� ��
	void TearDown() {
		printf("TearDown\n");
		delete calculator;
		// �ڹ��� ��� delete�� �ʿ� ������ �ü���� �ڿ��� �ݳ��ؾ� �Ѵ�. ������ ��
	}
};

TEST_F(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	printf("plus\n");
	calculator->plus(2);
	calculator->plus(2);

	ASSERT_EQ(4, calculator->display()) << "2 ���ϱ� 2�� �Ͽ��� ��";
}

TEST_F(CalculatorTest, minus)
{
	printf("minus\n");
	calculator->minus(2);
	calculator->minus(2);

	ASSERT_EQ(-4, calculator->display()) << "-2-2";
}

// xUnit Test Framework�� �׽�Ʈ���̽� ���� �Լ��� �����ϴ� ���
// => �ż��� �Ƚ����� ����
//	: �� �׽�Ʈ �Լ��� ���������� �����Ǿ�, ���� ��� �����ϴ��� �׻� ������ ����� ���� �� �ֵ��� �Ѵ�.

// TestCase* test = new TestCase();
// test->SetUp();
// test->foo();
// test->TearDown();

//	�Ź� �׽�Ʈ ���̽� Ŭ������ �Ź� ���Ӱ� �����Ѵ�. ���� �׽�Ʈ�� ������ ���� �ʱ� ����
// TestCase* test = new TestCase();
// test->SetUp();
// test->goo();
// test->TearDown();

// nUnit�� �ż��� �Ƚ��İ� �ȵ�� ���µ�... �Ǽ�����;;
// ��κ��� xUnit�� �ż��� �Ƚ��� ���

