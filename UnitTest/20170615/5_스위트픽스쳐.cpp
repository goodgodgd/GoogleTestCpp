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

	void login(const std::string* id, const std::string& password)
	{}

	void logout() {}

	bool isLogin() { return false; }
};

// �Ʒ� �� �׽�Ʈ�� ��� �ߺ� ����, �Ƚ��� ��ġ ��ü �ߺ�
#if 0
TEST(DatabseTest, login)
{
	Database* database = new Database;
	database->connect();

	database->login("test_id", "test_password");

	ASSERT_TRUE(database->isLogin()) << "�α��� �Ͽ��� ��";

	database->disconnect();
	delete database;
}

TEST(DatabseTest, logout)
{
	Database* database = new Database;
	database->connect();

	database->login("test_id", "test_password");
	database->logout();

	ASSERT_FALSE(database->isLogin()) << "�α׾ƿ� �Ͽ��� ��";

	database->disconnect();
	delete database;
}
#endif

// �Ϲ��� ��ġ ��ü�� ������ �����ϴ°� �ƴ϶� �ϸ鼭 �ߺ��Ǵ� ���� ���ֱ� ���� ��������.

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

// ��ġ ��ü�� xUnit framework���� �ѹ��� �����ϰ� �����Ѵ�.

