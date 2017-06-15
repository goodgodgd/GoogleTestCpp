// ���� �Ƚ���
//	=> Google Test ������ �����ϴ� ���

// �׽�Ʈ ���α׷��� ������ �� SetUp
// �׽�Ʈ ���α׷��� �����ϱ� ���� TearDown

#include "gtest/gtest.h"

class TestEnvironment : public ::testing::Environment {
public:
	void SetUp() {
		printf("Global Setup\n");
	}

	void TearDown() {
		printf("Global TearDown\n");
	}
};

TEST(Sample, foo)
{
	printf("sample foo\n");
}

// ��ġ�ϴ� ���
//	1) ���� ���� => main�� �������� ���� ���
// main�Լ� �������� �������� �ʱ�ȭ �̿�
#if 0
::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new TestEnvironment);
#endif

//	2) main �Լ� => main�� ���� ���� ���
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::AddGlobalTestEnvironment(new TestEnvironment);

	return RUN_ALL_TESTS();
}


// �Ϲ������� �� ��° ��� ����
// �������� ������ϴ� ����: C++ ���� ��ü�� ��ȣ, ISO C++ ǥ���� �������� �ʾ�, undefined ����.
// �������� ������/�Ҹ����� ȣ�� ������ ��Ȯ���� ����
// C++���� �̱����� ���� ������ ����/�Ҹ� ������ ��Ȯ�ϱ� ����

