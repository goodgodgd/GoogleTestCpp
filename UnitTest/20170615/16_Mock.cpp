// 16_Mock
// ���� ��ü, spy�� ���� ���� ���� ������ �ذ��ϴ� ������ ���Ƽ�.

// �׽�Ʈ �뿪 �뵵 4.
//	SUT�� �Լ��� ȣ���Ͽ��� �� ������ �� �ִ� �μ�ȿ���� ����.
//	�׽�Ʈ �ȵ� �䱸������ �����ϰ� �ʹ�.
//	1) Test Spy Pattern
//		=> ���� ��� ����
//	2) Mock Object Pattern
//		=> ���� ��� ����

// ���� �׽�Ʈ�� �ۼ��ϴ� 2���� ���
//	1) ���� ����
//	: SUT�� �����ؾ� �ϴ� ���°� ���� ��
//	=> SUT�� �����ϰ�, ���¸� ���� ��밪�� ���Ѵ�.

//	2) ���� ����
//	: SUT�� �����ؾ� �ϴ� ���°� ���� ��
//	=> �Լ��� ��ȯ���� ���ų�, ��ȯ���� Ȯ���ϴ� �͸����� ����� ���������� �����ϱ� ����� ��
//		1) �Լ��� ȣ�� ����
//		2) �Լ��� ȣ�� Ƚ��
//		3) �Լ��� ȣ�� ����

// Mock Object�� ���� �����ؼ� ����ϴ� ���� �ƴ϶�, Mock Framework�� ����ϸ� �˴ϴ�.
// C++ - Google Mock
// Java: jMock, EasyMock, Mockito

// �Լ��� ���α׷��� �з�����
//	�Һ� ��ü ����: ��ü�� ������ ���Ŀ� ���°� ������ �ʴ� ��ü, ��Ƽ ������ ����
//	�Һ� ��ü ����: ���±�� ������ �Ұ� => ���� ���� �ʿ�

// TDD(�׽�Ʈ �ֵ� ����) vs BDD(���� �ֵ� ����)
// ���� ����					Mock�� ���� ���

// Google Mock ����
// 1. ���� ���̺귯���� �����ϴ� ���� ��Ģ�Դϴ�.
// 2. Google Mock�� Google Test�� �������� �ֽ��ϴ�.
//		src �� �߰��� ����
//			gtest-all.cc
//			gmock-all.cc
//			gmock-main.cc
//		include path �� �߰��� ���
//			$googletest
//			$googletest\include
//			$googlemock
//			$googletest\include

//	Test Proejct
//	1. Include Path
//		$googletest\include
//		$googlemoc\include

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// gmock_main.cc�� gmock ������Ʈ�� �߰��ؼ� �����ϸ� �Ʒ��� main�� �ʿ����� �ʴ�.
#if 0
int main(int argc, char** argv)
{
//	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	// �� �ȿ��� InitGoogleTest�� ����Ǳ� ������ ������ �ʱ�ȭ�� �ʿ����� �ʽ��ϴ�.

	return RUN_ALL_TESTS();
}
#endif

// ���������� gmock�� �����ϴ� ���
// scripts/fuse_gmock_files.py �����ϸ� gtest�� gmock�� ������ ������ ���´�.
// gmock/gmock.h, gtest/gtest.h, gmock-gtest-all.cc
// gmock_main.cc �� �������� �����ؿ���.

// $ g++ gmock-gtest-all.cc -c -I.	// �����ϸ� object file ����
// $ g++ gmock-main.cc -c -I.		// main �ҽ��� �����ؿͼ� ����
// $ ar crv gtest.a gmock-gtest-all.o gmock_main.o
//	=> gtest.a ����

// �����ϴ� ����� �����س����� ����.
// markdown���� �����ؼ� github���� �����ϸ� ����.

// DLog: Ÿ���� ����Ѵ�?
//	FileTarget => File
//	NetworkTarget => Network

enum Level {
	INFO, WARN, CRITICAL
};

struct Target {
	virtual void write(Level level, const std::string& message) = 0;
	virtual ~Target() {}
};

class DLog {
	std::vector<Target*> targets;
public:
	void addTarget(Target* p) {
		targets.push_back(p);
	}

	void write(Level level, const std::string& message) {
		for (Target* e : targets) {
			e->write(level, message);
		}
	}
};

class SpyTarget : public Target {
	// ��� �޽����� �ϳ��� ���ڿ��� ����
	std::vector<std::string> history;
	std::string concat(Level level, const std::string& message) {
		static const char* table[] = {
			"INFO", "WARN", "CRITICAL"
		};
		return std::string(table[level]) + "@" + message;
	}
public:
	// �޾Ҵ��� Ȯ��, �̹� ������ �˰��� �̿��ϴ� ���� �ŷڼ��� ������ �ȴ�.
	bool received(Level level, const std::string& message) {
		std::string log = concat(level, message);
		return std::find(begin(history), end(history), log) != end(history);
	}

	void write(Level level, const std::string& message) {
		history.push_back(concat(level, message));
	}
};


//==============================================

class MockTarget : public Target {
public:
	MOCK_METHOD2(write, void(Level level, const std::string& message));
};

class DLogTest : public ::testing::Test {};

TEST_F(DLogTest, write)
{
	MockTarget mock1, mock2;
	DLog log;
	log.addTarget(&mock1);
	log.addTarget(&mock2);
	Level level = INFO;
	std::string message = "test_message";

	EXPECT_CALL(mock1, write(level, message));
	EXPECT_CALL(mock2, write(level, message));

	log.write(level, message);
}

// spy���ٴ� mock�� ���� ������ mock framework�� ���ؼ� �ذ��ϴ� ���� �����ϰ� ����.
