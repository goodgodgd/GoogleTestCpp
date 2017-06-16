// SUT
bool isPrime(int value) {
	if (value < 2)
		return false;

	for (int i = 2; i < value; i++)
		if (value % i == 0)
			return false;

	return true;
}

#include "gtest/gtest.h"

// ������ �߽��� �׽�Ʈ�� ������ �׽�Ʈ�� �����ϰ� �����ϸ� ���� �ڵ� �ߺ��� �߻��մϴ�.
#if 0
TEST(PrimeTest, isPrime)
{
	EXPECT_TRUE(isPrime(2));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(5));
	EXPECT_TRUE(isPrime(7));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(13));
}
#endif

// Parameterized Test (�Ķ����ȭ�׽�Ʈ)
//	=> �Էµ����͸� �ٲ㰡��, ������ �ݺ� �˻��ϴ� ������ �߽��� �׽�Ʈ���� �ߺ��� �����ִ� ���
//	: xUnit Test Framework���� �����ϴ� ���

// 1. ��� => ::testing::TestWithParam<�Էµ�����Ÿ��>
//		TestWithParam : ���ø� Ŭ����
class PrimeTest : public ::testing::TestWithParam<int> {

};

// 2. ������ �� ����
INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest, ::testing::Values(2, 3, 5, 7, 11, 13));

// 3. ������ �پ��� �׽�Ʈ �Լ��� �����ϸ� �˴ϴ�.
// TEST
// TEST_F => Fixture ��ġ/��ü ����
// TEST_P => Parameterized
TEST_P(PrimeTest, isPrime)
{
	EXPECT_TRUE(isPrime(GetParam()));
}

TEST_P(PrimeTest, isPrime2)
{
	EXPECT_TRUE(isPrime(GetParam()));
}

// ������ (���)
// 1. �׽�Ʈ �̸����� � �����ͷ� �׽�Ʈ �ϴ��� �� �� ����.
//		��°��� �׽�Ʈ �ϴ� �������� �ȳ����� 1,2,3,.. �� ���´�. only gtest�� ����
//		�������� ������ �ִ�. => junit4������ �ذ�
// 2. �Ϲ����� �׽�Ʈ�� ������ �߽��� �׽�Ʈ�� �и��Ǽ� ������ �� �ۿ� ����.
//		=> junit5������ �Ķ����ȭ �׽�Ʈ�� �����. ���� �׽�Ʈ

