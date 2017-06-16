// 7_timeout.cpp
// ����(�ð�, �޸�) �׽�Ʈ

// Timeout => �������� �� �����Ͽ�����, ����ڰ� �䱸�ϴ� �ð��� �Ѱ��� ���, ���з� �����Ѵ�.
//	: Google Test������ �������� �ʽ��ϴ�.

#include <Windows.h>					// #include <unistd.h>	: ������
#define delay(sec)		Sleep(sec*1000)	// sleep(sec)			: ������
#include <time.h>

#include <gtest/gtest.h>

// SUT
void foo()
{
	delay(3);
}

#if 0
// setup���� teardown �Լ��� ȣ�� �Ǵ� ������ �ð��� �����Ͽ� FAIL() ������.
class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	void SetUp() {
		// ���� ���������� �� �ػ� ���� �Լ� �������.
		startTime = time(0);
	}

	void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < 2) << "timed out: " << duration << " seconds";
		// �׷��� 2�ʰ� �ƴ϶� �ٸ� �ð����� �˻��ϰ� ������??
		// ���ø� ���!!
	}
};

TEST_F(TimeoutTest, foo)
{
	foo();
}
#endif



// setup���� teardown �Լ��� ȣ�� �Ǵ� ������ �ð��� �����Ͽ� FAIL() ������.
template<typename T, int N>
class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	void SetUp() {
		// ���� ���������� �� �ػ� ���� �Լ� �������.
		startTime = time(0);
	}

	void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < N) << "timed out: " << duration << " seconds";
		// �׷��� 2�ʰ� �ƴ϶� �ٸ� �ð����� �˻��ϰ� ������??
		// ���ø� ���!!
	}
};

// template<int N> �� �ƴϰ� template<typename T, int N> ���� �����ϴ� ����
// TimeoutTest<2> �� �ϰ� �ٸ����� �� TimeoutTest<2> �� ��ӹ޴� ��ü�� ��Ÿ����
// �θ����� ���� ������ ���� ������ �����ϰ� �Ǵ� "���"�� ���� �ִ�.
// �ڽ��� Ÿ���� �����ϸ� ��� �ڽ�Ŭ�������� Ÿ���� "�ٸ���" ����� �ִ�.

// CRTP: Curiously Recurring Template Pattern
//	=> �θ� Ŭ������ ���ø��ε�, �ڽ��� Ÿ���� ���ڷ� �����ϴ� ���� ���

class Timeout2SecTest : public TimeoutTest<Timeout2SecTest, 2> {
};

class Timeout5SecTest : public TimeoutTest<Timeout5SecTest, 5> {
};

TEST_F(Timeout5SecTest, foo)
{
	foo();
}

// TestCase Ŭ���� ��ü�� �����ϴ� ���� �׽�Ʈ �����ӿ�ũ���� �ϱ� ������
// �������� ���ڸ� �����ϴ� ����� �̿��� ���� �����ϴ�.
// -> template ���
