// 15_Spy.cpp

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

// DLog: 타겟을 기록한다?
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

// 테스트 대역 용도 3.
//	: SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어 테스트가 안된 요구사항이 있다.
//	=> Test Spy Pattern

// Test Spy: 목격한 일을 기록해 두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
// 여기서는 DLog에 대해 Spy Target을 만들어주자.
// 로그를 했는지 확인할 수 있게 하자.

#include <algorithm>

class SpyTarget : public Target {
	// 모든 메시지를 하나의 문자열로 저장
	std::vector<std::string> history;
	std::string concat(Level level, const std::string& message) {
		static const char* table[] = {
			"INFO", "WARN", "CRITICAL"
		};
		return std::string(table[level]) + "@" + message;
	}
public:
	// 받았는지 확인, 이미 검증된 알고리즘 이용하는 것이 신뢰성에 도움이 된다.
	bool received(Level level, const std::string& message) {
		std::string log = concat(level, message);
		return std::find(begin(history), end(history), log) != end(history);
	}

	void write(Level level, const std::string& message) {
		history.push_back(concat(level, message));
	}
};

// 빈 테스트 클래스를 만드는 이유
// 실제로 테스트를 하기로 하면 암묵적 설치/해체는 필수이기 때문
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
	// log에서 지금까지 받은 정보를 target(spy)에게 주고
	// spy에서 이를 받았는지 확인
	EXPECT_TRUE(spy1.received(test_level, test_message));
	EXPECT_TRUE(spy2.received(test_level, test_message));
}

// 하다보니 테스트 코드보다 테스트 TEST_F 위의 테스트 대역 코드가 더 많이 필요하다.
//	=> 테스트 코드의 유지보수성이 떨어져
//		제품 코드가 변하면 테스트 코드도 보수해줘야
// 개념만 이해하는게 낫다.

// 테스트 프레임워크의 핵심 설계 기술, 언어 자체에서 제공하는 기술
//	: 리플렉션 (Reflection)
//	C++에서는 제공하지 않아 테스트가 어려워

