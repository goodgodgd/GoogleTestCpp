// 1. gtest�� ������Ʈ�� ���ԵǾ �׻� ���Ӱ� ����Ǿ�� �մϴ�.
//	=> gtest ���̺귯���� ���� ���̺귯�� ����� ����˴ϴ�.

// 2. gtest ���� ���̺귯�� ������Ʈ

// Ctrl + F7 : Compile
// Ctrl + F5 : Compile + Run
#include "gtest/gtest.h"

// �Ʒ��� main �ڵ�� �ݵ�� ���ԵǾ�� �մϴ�.
// �Ʒ��� �ڵ�� gtest���� gtest_main.cc ��� �̸����� �����˴ϴ�.
// ���� ���̺귯���� �����ؼ� ����ϸ� ���մϴ�.
// main �Լ��� �� �ᵵ ��

// ������������
// : ar crv gtest.a gtest-all.o gtest_main.o

// �׽�Ʈ �Լ� ����� ���(��ũ�� ���): TEST(TestCase �̸�, Test �̸�)
TEST(TestCase, Test)
{
	// 1. �ۼ� ���� �׽�Ʈ�� �ݵ�� ���н��Ѿ� �մϴ�. (�ϼ� �ȵ�)
	FAIL() << "�ۼ� �� �Դϴ�.";

	// 2. �׽�Ʈ�� ������ ���, ������ ������ �ݵ�� �����ؾ� �մϴ�.
}


#if 0
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif
