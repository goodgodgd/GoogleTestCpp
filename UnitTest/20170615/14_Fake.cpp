// 14_Fake Object

#include <string>
#include "gtest/gtest.h"

class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string toString() const {
		char buf[128];
		sprintf(buf, "{name=%s, age=%d}\n", getName().c_str(), getAge());
		std::string str = buf;
		return str;
	}

	std::string getName() const { return name; }
	int getAge()		  const { return age; }
};

struct IDatabase {
	virtual void save(User* user) = 0;
	virtual User* load(const std::string& name) = 0;

	virtual ~IDatabase() {}
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}
	void save(const std::string& name, int age) {
		//...
		database->save(new User(name, age));
	}

	User* load(const std::string& name) {
		//...
		return database->load(name);
	}
};


// 테스트 대역 목적 2.
//	: 협력 객체를 사용하기 어려울 때, 테스트를 수행하고 싶다.

// 1. 아직 준비되지 않은 협력 객체
// 2. 협력 객체로 인해서, 느린 테스트의 문제가 발생할 때
//		느린 테스트 => 개발자들이 테스트 안해, 생산성 저하

// => Fake Object Pattern
//	: 빠르고 가벼운 객체로 교체한다.
// 특정 데이터에 의존하는 경우, mysql 설치해야 하는경우, 클라우드 환경 사용에 비용이 들 경우

// 검증해야 하는 SUT는 UserManager인데 데이터베이스에 의존하므로 가짜로 만들어주자.

// Key-value
#include <map>

class MemoryDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void save(User* user) {
		data[user->getName()] = user;
	}
	User* load(const std::string& name) {
		return data[name];
	}
};

class UserManagerTest : public ::testing::Test {
protected:
};

TEST_F(UserManagerTest, save_compareFields)
{
	MemoryDatabase mdb;
	UserManager manager(&mdb);

	manager.save("test_name", 42);
	User* actual = manager.load("test_name");

	ASSERT_EQ("test_name", actual->getName());
	ASSERT_EQ(42, actual->getAge());
}

// 컴파일이 안돼
// 사용자 정의 객체에 대해서 단언함수를 사용하기 위해서는
// 반드시 해당하는 연산자에 대한 재정의가 필요합니다.
bool operator==(const User& lhs, const User& rhs)
{
	// 실패하면 메모리덤프;;
	return false;
	return lhs.getName() == rhs.getName() && lhs.getAge() == rhs.getAge();
}

// 근데 이것이 실패했을 때의 메시지가 메모리 덤프를 보여주기 때문에 에러 메시지를 만들어주자!!
#include <iostream>
// 사용자 정의 객체를 문자열의 형태로 출력하기 위해서는 아래의 함수를 제공하면 됩ㄴ다. - Google Test/ C++ cout
// 이런 방법도 있고 자기 자신이 toString() 메소드를 만들어주는 방법도 잇다.
#if 0
std::ostream& operator<<(std::ostream& os, const User& user) {
	char buf[128];
	sprintf(buf, "{name=%s, age=%d}\n", user.getName().c_str(), user.getAge());
	return os << buf;
}
#endif

std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << user.toString();
}


TEST_F(UserManagerTest, save_compareObject)
{
	MemoryDatabase mdb;
	UserManager manager(&mdb);
	User expected("test_name", 42);

	manager.save("test_name", 42);
	User* actual = manager.load("test_name");

	ASSERT_EQ(expected, *actual);	// == 연산자 수행하는데 User는 없다.
}

