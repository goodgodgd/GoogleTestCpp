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

	void login(const std::string& id, const std::string& password)
	{}

	void logout() {}

	bool isLogin() { return false; }
};

class DatabaseTest : public ::testing::Test {
protected:
	static Database* database;

	static void SetUpTestCase() {
		printf("Suite SetUp\n");
		database = new Database;
		database->connect();
	}
	static void TearDownTestCase() {
		printf("Suite TearDown\n");
		database->disconnect();
		delete database;
	}

	void SetUp() {
	}

	void TearDown() {
	}
};

// C++은 반드시 정적 멤버 변수를 반드시 클래스 외부 정의를 제공해야 합니다.
Database* DatabaseTest::database = 0;

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

// SetUp - suite fixture setup			: 객체가 생성되기 전이므로 static으로 선언해야 한다.
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

// google의 네이밍 컨벤션에서 public 함수는 대문자로 시작


// 정리
//	1. 스위트 픽스쳐 설치/해체의 기능은 xUnit Test Framework에서 제공하는 기능입니다.
//	2. 픽스쳐의 설치/해체로 인해 느린 테스트의 문제가 발생한 경우 사용하면 됩니다.

// 문제점 - 중요합니다!!
//	이제 모든 테스트는 더 이상 독립적이지 않습니다.
//	=> 공유 픽스쳐 전략

// 성능에는 도움이 되지만, [변덕스러운 테스트]가 발생할 수 있습니다.
// (테스트 할 때마다 문제가 다르면 디버깅이 어렵다.)
//	=> 테스트 케이스 클래스 안에 너무 많은 테스트 함수가 존재한다면 분리하는 것이 좋습니다.
//		(테스트 케이스 클래스를 나눠서 사용해라)

