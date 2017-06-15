// 스위트 픽스쳐

#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace std;

#include <Windows.h>	// #include <unistd.h>
#define delay(sec)		Sleep(1000*sec); // sleep(sec)

// SUT
class Database {
public:
	// connect와 disconnect는 느린 작업입니다.
	void connect() { delay(2); }
	void disconnect() { delay(1); }

	void login(const std::string* id, const std::string& password)
	{}

	void logout() {}

	bool isLogin() { return false; }
};

// 아래 두 테스트의 경우 중복 많아, 픽스쳐 설치 해체 중복
#if 0
TEST(DatabseTest, login)
{
	Database* database = new Database;
	database->connect();

	database->login("test_id", "test_password");

	ASSERT_TRUE(database->isLogin()) << "로그인 하였을 때";

	database->disconnect();
	delete database;
}

TEST(DatabseTest, logout)
{
	Database* database = new Database;
	database->connect();

	database->login("test_id", "test_password");
	database->logout();

	ASSERT_FALSE(database->isLogin()) << "로그아웃 하였을 때";

	database->disconnect();
	delete database;
}
#endif

// 암묵적 설치 해체를 무조건 적용하는게 아니라 하면서 중복되는 것을 없애기 위해 적용하자.

class DatabaseTest : public ::testing::Test {
protected:
	Database* database;

	void SetUp() {
		database = new Database;
		database->connect();
	}

	void TearDown() {
		database->disconnect();
		delete database;
	}
};

TEST_F(DatabaseTest, login)
{
	database->login("test_id", "test_password");
	ASSERT_TRUE(database->isLogin()) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, logout)
{
	database->login("test_id", "test_password");
	database->logout();

	ASSERT_FALSE(database->isLogin()) << "로그아웃 하였을 때";
}

// 픽스쳐의 설치 / 해체가 느린 경우
// : 테스트가 추가될 때마다, 점점 더 느려진다.

// 느린 테스트(Slow Test) 문제
//	: 테스트가 너무 느려서, SUT가 변경되어도 개발자들이 매번 테스트를 수행하지 않는다.
//	=> 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.

//	=> 스위트 픽스쳐 설치/해체를 통해서 해결 할 수 있습니다.
//	: 정적 멤버 함수로 약속되어 있습니다.

// SetUp - suite fixture setup
// TestCase testcase = new TestCase;
// testcase.SetUp
// testcase.foo
// testcase.TearDown

// TestCase testcase = new TestCase;
// testcase.SetUp
// testcase.goo
// testcase.TearDown
// TearDown - suite fixture teardown

// 설치 해체를 xUnit framework에서 한번만 실행하게 지원한다.

