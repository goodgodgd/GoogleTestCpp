// �׽�Ʈ ���� ���� Ŭ����
//	: Test Specific Subclass Pattern
// 1. SUT�� �����ؾ� �ϴ� ���°� �������� ���� ��, ��� �ϸ� �׽�Ʈ �����ϰ� �� �� �ִ°�?
// 2. �Ǵ� SUT�� �����ؾ� �ϴ� ���¿� ������ �� ���� �� (isStart)

// SUT
#include <stdio.h>

class Engine {
protected:
	bool isStart;

public:
	virtual void start() {
		printf("start engine...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* e) : engine(e) {}

	void go() { engine->start(); }
};

#include "gtest/gtest.h"

class CarTest : public ::testing::Test {

};

// �ڵ����� go�� ȣ��Ǿ��� ����, ������ ���¸� �����ϰ� �ʹ�.
#if 0
TEST_F(CarTest, go)
{
	Engine engine;
	Car car(&engine);

	car.go();
	// �� �ؿ� �ܾ��� ������ ���� �������� �ʴ´�. �׳� Ŀ�������� ���̴� �Լ�
}
#endif


// ��� => �θ�Ŭ������ �ڽ�Ŭ����
// ����� ������ ������ �ƴ϶� �������� ��ǥ
// �������� �����ϱ� ���ؼ��� is-a ����, circle is a shape

// ��ǰ �ڵ带 �ǵ帮�� �ʰ� �׽�Ʈ �����ϰ� �����.
// ������ �׽�Ʈ ������ ���踦 �����... private �ȵ�, virtual ����
class TestEngine : public Engine {
	// �׽�Ʈ�� �ʿ��� ���¸� �߰��Ѵ�.
	bool isStart_;
public:
	TestEngine() : isStart_(false) {}
	void start() {
		Engine::start();	// �θ��� ����� �̿��Ѵ�.
		isStart_ = true;	// Ȯ���ϰ� ���� ���� ����
	}

	// �׽�Ʈ�Լ� ���� �̿��� �� �ִ� �Լ��� �����h��.
	bool isStart() { return isStart_; }
};

// �׽�Ʈ ����� �������� �ʰ� (��ǰ�ڵ�) ���ϴ� �׽�Ʈ�� �� �� �ִ�.

// �ڵ����� go�� ȣ��Ǿ��� ����, ������ ���¸� �����ϰ� �ʹ�.
TEST_F(CarTest, go)
{
	TestEngine engine;
	Car car(&engine);	// is-a ����� TestEngine�� �־ �������.

	car.go();
	// �� �ؿ� �ܾ��� ������ ���� �������� �ʴ´�. �׳� Ŀ�������� ���̴� �Լ�
	ASSERT_TRUE(engine.isStart()) << "�ڵ����� go�� ��";
}

// 1. �θ� �����ϴ� ����� �ݵ�� ���� �Լ��� �����Ǿ� �־�� �մϴ�.
//	�Ϲ� �Լ�(���� ���ε�) vs ���� �Լ�(���� ���ε�)
// 2. �θ��� ����� private �̸� �ȵȴ�.

// ���ε�: � �Լ��� ȣ������ �����ϴ� ��