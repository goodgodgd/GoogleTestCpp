// 2_3A
// : �׽�Ʈ �Լ��� �ۼ��ϴ� ���

// SUT (�׽�Ʈ ��� �ý���), CUT
//	: System Under Test, Code (Class) Under Test

class Calculator {
	int value;
public:
	Calculator() : value(0) {}

	void plus(int n) { value += n; }
	void minus(int n) { value -= n; }
	
	int display() { return value; }
};
// ��������� ��ǰ �ڵ�

#include "gtest/gtest.h"

// 3A (TDD) => BDD (Behavior, ���� �ֵ� ����), �׽�Ʈ �ڵ��� �������� �߿����. �ڵ带 ����� ����ó��
// Arrange: ��ü�� �����ϰ�, �ʿ��� ��� �����ϰ� �����Ѵ�.	- Given (BDD)
// Act: ��ü�� �ۿ��� ���Ѵ�.								- When (BDD)
// Assert: ����ϴ� �ٸ� �ܾ��Ѵ�.						- Then (BDD)

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
		FAIL() << "2 ���ϱ� 2�� �Ͽ��� ��";
}
#endif

// �׽�Ʈ�� �ٽ�
// 1. ������
// 2. �ŷڼ�
// 3. ����������
//	: �׽�Ʈ �Լ� �ȿ����� �ݺ����̳� ���ǹ� ���� ���� �帧 ������ ������� �ʴ� ���� ����.
//	���ǹ��� ��� �ϴ� ���� ���� ������ �׽�Ʈ ���̽��� ����� ���� ����.

// �� �׽�Ʈ�� � �ó������� �����ϴ��� ���θ� �׽�Ʈ �Լ��� ���� �巯���� ���� ����.
// �� �� �ڼ��� �̸� �ʿ�
// ex) �׽�Ʈ����Լ�_�ó�����_��밪
// cpp ǥ���� �����ڵ� �ƴ� �ƽ�Ű�ڵ� ���� �ѱ۷δ� ���̹� ����.
// VS�� ����. ǥ�ؿ� ����� Ȯ����, �ڹٴ� ����

TEST(CalculatorTest, plus_TwoPlusTwo_DisplaysFour)
{
	// Arrange
	Calculator* calculator = new Calculator;
	// => Fixture Setup

	// Act
	calculator->plus(2);
	calculator->plus(2);

	// Assert
	// 1. �Ʒ��� �ڵ带 ĸ��ȭ�� �Լ��� �����մϴ�.
	// => ASSERT_EQ(��밪, ������)
	
	// 2. ������ ������ �����ؾ� �մϴ�.
	// �ΰ��� �� ���������� ��밪�� ���� �ִ´�. (���๮ �ؼ� ������)
	ASSERT_EQ(4, calculator->display()) << "2 ���ϱ� 2�� �Ͽ��� ��";
	//	ASSERT_EQ(calculator->display(), 4);

	//	if (calculator->display() != 4)
	//		FAIL() << "2 ���ϱ� 2�� �Ͽ��� ��";
}

