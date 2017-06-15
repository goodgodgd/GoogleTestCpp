// ���� �Ƚ���
//	=> Google Test ������ �����ϴ� ���

// �׽�Ʈ ���α׷��� ������ �� SetUp
// �׽�Ʈ ���α׷��� �����ϱ� ���� TearDown
// ���̺귯���� ���� ��ü �¾��ؾ� �� ��

// "5_����Ʈ�Ƚ���2" ���� "static void SetUpTestCase()" �� 
//	�׽�Ʈ���̽� Ŭ������ ��ġ/��ü�� �ѹ��� �ϴ� ���̰�
// ���� �Ƚ��Ĵ� ��ü ���α׷� �������� �ѹ����� ��ġ/��ü �ϴ� ���̴�.

#include "gtest/gtest.h"

// ::testing::Environment �̰� ����� ���� �����ؾ� ���� �Ƚ��� ��ġ��
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
//	: ���� �Ƚ��ĸ� ����ؾ� �ϴ� ���, ���� main�� ����� ���� �����ϴ�.

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	// ���� �Ƚ��� �¾��� main�ȿ� �ζ������� ����
	::testing::AddGlobalTestEnvironment(new TestEnvironment);

	return RUN_ALL_TESTS();
}


// �Ϲ������� �� ��° ��� ����
// �������� ������ϴ� ����: C++ ���� ��ü�� ��ȣ, ISO C++ ǥ���� �������� �ʾ�, undefined ����.
// �������� ������/�Ҹ����� ȣ�� ������ ��Ȯ���� ����
// C++���� �̱����� ���� ������ ����/�Ҹ� ������ ��Ȯ�ϱ� ����

