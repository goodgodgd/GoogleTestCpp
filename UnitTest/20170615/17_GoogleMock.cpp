// �Ѱ�: C++�� Reflection�� �������� �ʽ��ϴ�.
// Reflection
//	1) ��Ÿ�ӿ� Ÿ���� üũ�� �� �ֽ��ϴ�. - RTTI C++�� �־�
//	2) ���� ����
//		: ��Ÿ�ӿ� ���ϴ� Ÿ���� ��ü�� ������ �� �ֽ��ϴ�.
//		=> �������� MockObject�� ������ �� �ֽ��ϴ�.
// !! scripts/gmock_gen.py�� �����ϸ� �ڵ����� MockObject Ŭ������ �ڵ����� ������ش�.

#include <string>

struct Unit {
	virtual ~Unit() {}
	virtual void stop() = 0;
	virtual void say(const std::string& message) = 0;
	virtual void attack(Unit* p) = 0;
	virtual void move(int x, int y) = 0;
	virtual void getX() const = 0;
	virtual void getY() const = 0;
};

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// ���� ��ü - ���� ��� �׽�Ʈ
// 1. �޼ҵ� ȣ�� ����
// 2. �޼ҵ� ȣ�� Ƚ��
// 3. �޼ҵ� ȣ�� ����

// �Ϲ� ��� �Լ�
// : MOCK_METHOD{������ ����}(������ �̸�, �Լ��� Ÿ��);
// const ��� �Լ�
// : MOCK_CONST_METHOD{������ ����}(������ �̸�, �Լ��� Ÿ��);

// ��ü Ŭ������ �ƴ� �������̽��� ���� ������.

// googlemock/scripts/generator/mock_gen.py�� �̿��ϸ� �ڵ����� ���� ���� �մϴ�.
// �ٵ� �̰ɷ� ���� ����� include ���带 �߰������ ��
// #ifndef HEADER \ #define HEADER \ #endif
class MockUnit : public Unit {
public:
	MOCK_METHOD0(stop, void());
	MOCK_METHOD1(say, void(const std::string& message));
	MOCK_METHOD1(attack, void(Unit* p));
	MOCK_METHOD2(move, void(int x, int y));
	MOCK_CONST_METHOD0(getX, void());
	MOCK_CONST_METHOD0(getY, void());
};


// 1. ȣ�� ����
void foo(Unit* p)
{
	p->stop();
}

TEST(GMockTest, foo)
{
	// google mock�� arrange, assert, act ������ �����Ѵ�. gmock�� ���� Ư¡
	// 1. �غ� �ܰ� - Arrange
	MockUnit mock;

	// 2. ����ϴ� �ٸ� �ܾ��Ѵ� - Assert
	EXPECT_CALL(mock, stop());	// mock���� stop�� ȣ��Ǿ�� �Ѵ�.

	// 3. mock�� �����ϴ� SUT�� �����Ѵ�. - Act
	foo(&mock);
}

// ���ۿ�
// gmock�� ���� ��ü�� �ı��Ǵ� ������ ���� ��� ������ ����ȴ�.
TEST(GMockTest, foo_bad)
{
	MockUnit* mock = new MockUnit;
	EXPECT_CALL(*mock, stop());	// mock���� stop�� ȣ��Ǿ�� �Ѵ�.
	foo(mock);
	delete mock;
}


// 2. ȣ�� Ƚ�� �Ǵ�
void goo(Unit* p)
{
	p->stop();
	p->stop();
	p->stop();
}

using ::testing::AnyNumber;
TEST(GMockTest, goo)
{
	MockUnit mock;
	// �� �� �����ϴ°�?
	EXPECT_CALL(mock, stop()).Times(3);
//	EXPECT_CALL(mock, stop()).Times(AnyNumber());	// Ƚ�� ������� ȣ�� �ƴ��� Ȯ��
	goo(&mock);
}

// C++�� �ִ� ����: stack�� ��ü�� ������ �� �ִ�. ���� ������ ������ ������
// gtest�� stack�� ��ü�� �����ϴ� ���� ������


// 3. �޼ҵ� ȣ�� ����
void hoo(Unit* p)
{
	p->move(10, 42);
	p->stop();
}

// �޼ҵ� ȣ�� ������ ������ �ʿ��ϴٸ�, InSequence ��ü�� �����ϸ� �˴ϴ�.
using ::testing::InSequence;
TEST(GMockTest, hoo) {
	InSequence seq;
	MockUnit mock;

	// ����ϴ� ȣ�� �������
	EXPECT_CALL(mock, move(10, 42));
	EXPECT_CALL(mock, stop());

	hoo(&mock);
}



// Mockito, Google Mock
//	=> �ݸ� �����ӿ�ũ

// Mock => ���� ����
// Stub, Fake => �ݸ�

class Time {
public:
	virtual ~Time() {}
	virtual std::string getTime() { return "16:42";  }
};

// �Ϲ������� stub�� ����µ� mock�� ���ؼ��� �ذ��� �� �ִ�.
class MockTime : public Time {
public:
	MOCK_METHOD0(getTime, std::string());
};

// ������ �����ϴ� �κ��� ���������� �����ϰ� �ʹ�.
using ::testing::Return;
TEST(TimeTest, Stub)
{
	MockTime stub;
	// call�� ���� �� ����("00:00") ����
	// MockTime�� Time�� ��ӹ޾� ��ü Ŭ������ �����ϴµ� ���ϰ��� �������� �ʾҴ�.
	// Return()���� ���ϰ��� ������ �� �ִ�.
	ON_CALL(stub, getTime()).WillByDefault(Return("00:00"));

	printf("%s\n", stub.getTime().c_str());
}
