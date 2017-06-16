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


// �׽�Ʈ �뿪 ���� 2.
//	: ���� ��ü�� ����ϱ� ����� ��, �׽�Ʈ�� �����ϰ� �ʹ�.

// 1. ���� �غ���� ���� ���� ��ü
// 2. ���� ��ü�� ���ؼ�, ���� �׽�Ʈ�� ������ �߻��� ��
//		���� �׽�Ʈ => �����ڵ��� �׽�Ʈ ����, ���꼺 ����

// => Fake Object Pattern
//	: ������ ������ ��ü�� ��ü�Ѵ�.
// Ư�� �����Ϳ� �����ϴ� ���, mysql ��ġ�ؾ� �ϴ°��, Ŭ���� ȯ�� ��뿡 ����� �� ���

// �����ؾ� �ϴ� SUT�� UserManager�ε� �����ͺ��̽��� �����ϹǷ� ��¥�� ���������.

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

// �������� �ȵ�
// ����� ���� ��ü�� ���ؼ� �ܾ��Լ��� ����ϱ� ���ؼ���
// �ݵ�� �ش��ϴ� �����ڿ� ���� �����ǰ� �ʿ��մϴ�.
bool operator==(const User& lhs, const User& rhs)
{
	// �����ϸ� �޸𸮴���;;
	return false;
	return lhs.getName() == rhs.getName() && lhs.getAge() == rhs.getAge();
}

// �ٵ� �̰��� �������� ���� �޽����� �޸� ������ �����ֱ� ������ ���� �޽����� ���������!!
#include <iostream>
// ����� ���� ��ü�� ���ڿ��� ���·� ����ϱ� ���ؼ��� �Ʒ��� �Լ��� �����ϸ� �ˤ���. - Google Test/ C++ cout
// �̷� ����� �ְ� �ڱ� �ڽ��� toString() �޼ҵ带 ������ִ� ����� �մ�.
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

	ASSERT_EQ(expected, *actual);	// == ������ �����ϴµ� User�� ����.
}

