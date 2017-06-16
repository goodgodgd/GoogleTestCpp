// 13_����

#include <stdexcept>
#include "gtest/gtest.h"
// SUT

class IOException : public std::exception {
public:
	const char* what() {
		return "Pipe is broken";
	}
};

class User;
struct IConnection {
	virtual void move(int x, int y) = 0;
	virtual void attack(User* user) = 0;

	virtual ~IConnection() {}
};

class TCPConnection : public IConnection {
public:
	virtual void move(int x, int y) {
		// ��Ŷ�� ����� �����Ѵ�.
		// ��Ʈ��ũ ������ ������, ���ܸ� ������.
	}

	virtual void attack(User* user) {
		// ��Ŷ�� ����� �����Ѵ�.
		// ��Ʈ��ũ ������ ������, ���ܸ� ������.
	}
};

class User {
	IConnection* connection;
public:
	explicit User(IConnection* c = 0) : connection(c) {
		if (c == 0)
			connection = new TCPConnection();
	}
	void move(int x, int y) {
		connection->move(x, y);
		// ...
	}

	void attack(User* user) {
		connection->attack(user);
		// ..
	}
};

// ����
// ������� ������ ���� ���, User�� move�� attack�� ������ �����ϰ� �ʹ�.

// �׽�Ʈ �뿪 �뵵 1. Ư���� ��Ȳ�� �ùķ��̼� �ϰ� �ʹ�.
//	������ �� ���� ������ ���� ��ü�� ������ �ùķ��̼� �Ѵ�.
//	=> Test Stub Pattern

// ������ �� ���� ���� ��ü: �ܺ� ������
//		��Ʈ��ũ, �ð� ... ��
// ���� ����� ���� ������� �ؼ��� �ȵȴ�. Ư�� �ð��� �����ϰ� �ʹ�.

// ���ܸ� �����ֱ� ���� �뿪
class BadConnection : public IConnection {
	virtual void move(int x, int y) {
		throw IOException();
	}

	virtual void attack(User* user) {
		throw IOException();
	}
};

class UserTest : public ::testing::Test {
};

TEST_F(UserTest, move_whenPipeIsBroken_throwsException) {
	BadConnection stub;
	User user(&stub);
	ASSERT_THROW(user.move(10, 42), IOException);
}

