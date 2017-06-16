// 13_스텁

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
		// 패킷을 만들어 전송한다.
		// 네트워크 연결이 끊긴경우, 예외를 던진다.
	}

	virtual void attack(User* user) {
		// 패킷을 만들어 전송한다.
		// 네트워크 연결이 끊긴경우, 예외를 던진다.
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

// 문제
// 사용자의 연결이 끊긴 경우, User의 move와 attack의 동작을 검증하고 싶다.

// 테스트 대역 용도 1. 특수한 상황을 시뮬레이션 하고 싶다.
//	제어할 수 없는 형태의 협력 객체의 동작을 시뮬레이션 한다.
//	=> Test Stub Pattern

// 제어할 수 없는 협력 객체: 외부 의존물
//		네트워크, 시간 ... 등
// 예외 만들려 랜선 뽑으라고 해서는 안된다. 특정 시간에 검증하고 싶다.

// 예외를 날려주기 위한 대역
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

