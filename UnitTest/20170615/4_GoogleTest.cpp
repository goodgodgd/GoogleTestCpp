// Google Test

#include "gtest/gtest.h"

// 1. �ܾ�
//	- ASSERT_XX
//		NE(!=), EQ(==), LT(<), GT(>), LE(<=), GE(>=), TRUE, FALSE
//	: �ϳ��� ������ ���, ������ ������ �������� �ʽ��ϴ�.
//	=> �Ϲ��� ��ġ/��ü�� ������� �ʽ��ϴ�.

//	- EXPECTED_XX
//	: �����ϴ���, ������ ������ ��� �˴ϴ�.
//	=> �� �� �̻� �ܾ��� �׽�Ʈ �Լ� ���� �ʿ��� ���,
//		EXPECTED_XX�� ����ϴ� ���� �����ϴ�.

// ũ�Ⱑ ū Ŭ����
class Resource {
public:
	Resource() { printf("�ڿ� ����\n"); }
	~Resource() { printf("�ڿ� �Ҹ�\n"); }
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
	// �ϳ��� �׽�Ʈ �ȿ� �ܾ��� ������ �ִ°��� �����ٰ� ���� �ð��� �ִ�
//	ASSERT_EQ(expected, actual);
//	ASSERT_EQ(expected, actual);
//	ASSERT_EQ(expected, actual);

	// ���� �ܾ��� ������� �����Ƿ� => EXPECTED_XX
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual);

	// TearDown: inline TearDown�� assert ���Ŀ� ���� �ȵ�, �ڿ� ����
	delete r;
}
#endif

// 2. �׽�Ʈ ��Ȱ��ȭ
//	: �׽�Ʈ�� ������� ���Ե��� ������, ��Ȱ��ȭ�Ǿ� �ִ� �׽�Ʈ�� �ִٴ� ����� ���������� �˷��� �Ѵ�.
//	TestCase �̸� �Ǵ� Test �Լ��� �̸��� DISABLED_ �����Ѵٸ�	��Ȱ��ȭ �׽�Ʈ�� �νĵ˴ϴ�.
// junit 4 - @Ignore
// junit 5 - @Disabled

// �ܼ� �ּ�ó���ϸ� �������� �������� ��������. 
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

	// TearDown: inline TearDown�� assert ���Ŀ� ���� �ȵ�, �ڿ� ����
	delete r;
}

// 3. C++ ���ڿ�
//	stl - string : ASSERT_EQ / ASSERT_NE ��밡��
//	const char*	 : ASSERT_STREQ / ASSERT_STRNE (�� �Լ��� ���� �����͸� ���ϹǷ�)
// ���ڿ��� �ܾ��� �����ؼ� ����ؾ�

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

// 4. �ε��Ҽ��� ��
//	: �ε� �Ҽ����� ������ �ֽ��ϴ�. �����˴ϴ�.
//	=> ASSERT_DOUBLE_EQ / ASSERT_FLOAT_EQ ����
// ����ڰ� ���� ���� ������ �����ϰ� �ʹٸ�,
//	=> ASSERT_NEAR

TEST(GoogleTest, func4)
{
	double expected = 0.7;
	double actual = 0.1 * 7;

//	ASSERT_DOUBLE_EQ(expected, actual);
	ASSERT_NEAR(expected, actual, 0.00001);
}


// 5. ���� �׽�Ʈ
// foo �� �߸��� �Է� ���� �����Ͽ��� ���, invalid_argument�� ���� ���ܰ� ���������� Ȯ���ϰ� �ʹ�.
//	=>  ASSERT_THROW
//		ASSERT_ANY_THROW

void foo(const std::string& name)
{
	if (name.empty() || name.size() <= 5)
		throw std::invalid_argument("name should not be empty!");
	// ...
}

// gtest�� ����� �̿����� �ʰ� �⺻ ��ɸ� ������� ���
#if 0
TEST(GoogleTest, func5)
{
	// ������, ���ڿ��� ���� ���� � �׽�Ʈ���� �巯���� �ؾ� ���� �׽�Ʈ �ڵ�
	std::string bad_name = "bad";

	// �׽�Ʈ�� �������� �߿��ѵ� �̷��� ������� �ٶ������� �ʴ�.
	try {
		foo(bad_name);
		FAIL() << "���ܰ� �߻����� ����..";
	} catch (std::invalid_argument&) {
		SUCCEED();
	}
	catch (...) {
		FAIL() << "����� ���ܿ� �ٸ�...";
	}
}
#endif

TEST(GoogleTest, func5)
{
	std::string bad_name = "bad";
//	ASSERT_THROW(foo(bad_name), std::invalid_argument);
	// ��� ���ܵ� ������ �Ѵ�.
	ASSERT_ANY_THROW(foo(bad_name));
}

