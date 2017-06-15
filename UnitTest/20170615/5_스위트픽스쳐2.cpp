// ����Ʈ �Ƚ���

#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace std;

#include <Windows.h>	// #include <unistd.h>
#define delay(sec)		Sleep(1000*sec); // sleep(sec)

// SUT
class Database {
public:
	// connect�� disconnect�� ���� �۾��Դϴ�.
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

// C++�� �ݵ�� ���� ��� ������ �ݵ�� Ŭ���� �ܺ� ���Ǹ� �����ؾ� �մϴ�.
Database* DatabaseTest::database = 0;

TEST_F(DatabaseTest, login)
{
	database->login("test_id", "test_password");
	ASSERT_TRUE(database->isLogin()) << "�α��� �Ͽ��� ��";
}

TEST_F(DatabaseTest, logout)
{
	database->login("test_id", "test_password");
	database->logout();

	ASSERT_FALSE(database->isLogin()) << "�α׾ƿ� �Ͽ��� ��";
}

// �Ƚ����� ��ġ / ��ü�� ���� ���
// : �׽�Ʈ�� �߰��� ������, ���� �� ��������.

// ���� �׽�Ʈ(Slow Test) ����
//	: �׽�Ʈ�� �ʹ� ������, SUT�� ����Ǿ �����ڵ��� �Ź� �׽�Ʈ�� �������� �ʴ´�.
//	=> �׽�Ʈ�� �����ϴ� �������� ���꼺�� ����߸���.

//	=> ����Ʈ �Ƚ��� ��ġ/��ü�� ���ؼ� �ذ� �� �� �ֽ��ϴ�.
//	: ���� ��� �Լ��� ��ӵǾ� �ֽ��ϴ�.

// SetUp - suite fixture setup			: ��ü�� �����Ǳ� ���̹Ƿ� static���� �����ؾ� �Ѵ�.
// TestCase testcase = new TestCase;
// testcase.SetUp
// testcase.foo
// testcase.TearDown

// TestCase testcase = new TestCase;
// testcase.SetUp
// testcase.goo
// testcase.TearDown
// TearDown - suite fixture teardown

// ��ġ ��ü�� xUnit framework���� �ѹ��� �����ϰ� �����Ѵ�.

// google�� ���̹� �����ǿ��� public �Լ��� �빮�ڷ� ����


// ����
//	1. ����Ʈ �Ƚ��� ��ġ/��ü�� ����� xUnit Test Framework���� �����ϴ� ����Դϴ�.
//	2. �Ƚ����� ��ġ/��ü�� ���� ���� �׽�Ʈ�� ������ �߻��� ��� ����ϸ� �˴ϴ�.

// ������ - �߿��մϴ�!!
//	���� ��� �׽�Ʈ�� �� �̻� ���������� �ʽ��ϴ�.
//	=> ���� �Ƚ��� ����

// ���ɿ��� ������ ������, [���������� �׽�Ʈ]�� �߻��� �� �ֽ��ϴ�.
// (�׽�Ʈ �� ������ ������ �ٸ��� ������� ��ƴ�.)
//	=> �׽�Ʈ ���̽� Ŭ���� �ȿ� �ʹ� ���� �׽�Ʈ �Լ��� �����Ѵٸ� �и��ϴ� ���� �����ϴ�.
//		(�׽�Ʈ ���̽� Ŭ������ ������ ����ض�)

