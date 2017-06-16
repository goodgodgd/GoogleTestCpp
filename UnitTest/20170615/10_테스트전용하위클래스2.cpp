// �׽�Ʈ��������Ŭ����2

#include "gtest/gtest.h"

#if 0
class User {
protected:
	int age;
	User() : age(42) {}

	int getAge() { return age; }
};

// �θ��� �����ϰ��� �ϴ� �Ӽ��� protected�� ���
// using�� ���ؼ� ������ ������ �� �ֽ��ϴ�.
class TestUser : public User {
	// public getAge() { User::getAge(); } // java ��Ÿ��
public:
	// C++ ���� ����, �θ��� ���ٱ��� ����
	using User::getAge;
	using User::age;
};

// getAge �׽�Ʈ �����ϴ�
TEST(UserTest, getAge)
{
	TestUser u;
	printf("%d/n", u.age);
	printf("%d/n", u.getAge());
}
#endif

#if 0
// �ļ�
// private�̸� ��ϳ�? private ���� ����;;
#define private public
#define class struct

// ������ Ŭ������ ��Ŭ�����
// #include <user.h>
class User {
	int age;
private:
	User() : age(42) {}
	int getAge() { return age; }

	FRIEND_TEST(UserTest, getAge)
};

TEST(UserTest, getAge)
{
	User u;
	printf("%d/n", u.age);
	printf("%d/n", u.getAge());
}
#endif

// ���� �׽�Ʈ���� �����ϴ� FRIEND_TEST ��ũ�� ���
// ��ǰ �ڵ忡�� ����� ���ָ� ��

class User {
public:
	User() : age(42) {}
	FRIEND_TEST(UserTest, getAge);

private:
	int age;
	int getAge() { return age; }
};

class UserTest : public ::testing::Test {};

TEST(UserTest, getAge)
{
	User u;
	printf("%d/n", u.age);
	printf("%d/n", u.getAge());
}
