// 테스트전용하위클래스2

#include "gtest/gtest.h"

#if 0
class User {
protected:
	int age;
	User() : age(42) {}

	int getAge() { return age; }
};

// 부모의 접근하고자 하는 속성이 protected의 경우
// using을 통해서 공개로 변경할 수 있습니다.
class TestUser : public User {
	// public getAge() { User::getAge(); } // java 스타일
public:
	// C++ 전용 문법, 부모의 접근권한 변경
	using User::getAge;
	using User::age;
};

// getAge 테스트 가능하다
TEST(UserTest, getAge)
{
	TestUser u;
	printf("%d/n", u.age);
	printf("%d/n", u.getAge());
}
#endif

#if 0
// 꼼수
// private이면 어떻하나? private 없애 버려;;
#define private public
#define class struct

// 보통은 클래스를 인클루드함
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

// 구글 테스트에서 제공하는 FRIEND_TEST 매크로 사용
// 제품 코드에서 약속을 해주면 됨

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
