// 15_Spy.cpp

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

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

// �׽�Ʈ �뿪 �뵵 3.
//	: SUT�� �Լ��� ȣ���Ͽ��� ��, �߻��ϴ� �μ� ȿ���� ������ �� ���� �׽�Ʈ�� �ȵ� �䱸������ �ִ�.
//	=> Test Spy Pattern

// Test Spy: ����� ���� ����� �ξ��ٰ�, ���߿� �׽�Ʈ���� Ȯ���� �� �ֵ��� ������� �׽�Ʈ �뿪
// ���⼭�� DLog�� ���� Spy Target�� ���������.
// �α׸� �ߴ��� Ȯ���� �� �ְ� ����.

#include <algorithm>

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

// �� �׽�Ʈ Ŭ������ ����� ����
// ������ �׽�Ʈ�� �ϱ�� �ϸ� �Ϲ��� ��ġ/��ü�� �ʼ��̱� ����
class DLogTest : public ::testing::Test {
};

TEST_F(DLogTest, write)
{
	DLog log;
	SpyTarget spy1, spy2;
	log.addTarget(&spy1);
	log.addTarget(&spy2);
	Level test_level = INFO;
	std::string test_message = "test_logging_message";
	log.write(test_level, test_message);
	// log���� ���ݱ��� ���� ������ target(spy)���� �ְ�
	// spy���� �̸� �޾Ҵ��� Ȯ��
	EXPECT_TRUE(spy1.received(test_level, test_message));
	EXPECT_TRUE(spy2.received(test_level, test_message));
}

// �ϴٺ��� �׽�Ʈ �ڵ庸�� �׽�Ʈ TEST_F ���� �׽�Ʈ �뿪 �ڵ尡 �� ���� �ʿ��ϴ�.
//	=> �׽�Ʈ �ڵ��� ������������ ������
//		��ǰ �ڵ尡 ���ϸ� �׽�Ʈ �ڵ嵵 ���������
// ���丸 �����ϴ°� ����.

// �׽�Ʈ �����ӿ�ũ�� �ٽ� ���� ���, ��� ��ü���� �����ϴ� ���
//	: ���÷��� (Reflection)
//	C++������ �������� �ʾ� �׽�Ʈ�� �����

