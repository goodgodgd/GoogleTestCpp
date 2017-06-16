// 16_Mock
// 모의 객체, spy와 같은 예제 쓰는 이유는 해결하는 문제가 같아서.

// 테스트 대역 용도 4.
//	SUT의 함수를 호출하였을 때 관찰할 수 있느 부수효과가 없다.
//	테스트 안된 요구사항을 검증하고 싶다.
//	1) Test Spy Pattern
//		=> 상태 기반 검증
//	2) Mock Object Pattern
//		=> 행위 기반 검증

// 단위 테스트를 작성하는 2가지 방법
//	1) 상태 검증
//	: SUT에 검증해야 하는 상태가 있을 때
//	=> SUT를 실행하고, 상태를 보고 기대값과 비교한다.

//	2) 동작 검증
//	: SUT에 검증해야 하는 상태가 없을 때
//	=> 함수에 반환값이 없거나, 반환값을 확인하는 것만으로 제대로 동작했음을 보장하기 어려울 때
//		1) 함수의 호출 여부
//		2) 함수의 호출 횟수
//		3) 함수의 호출 순서

// Mock Object는 직접 구현해서 사용하는 것이 아니라, Mock Framework를 사용하면 됩니다.
// C++ - Google Mock
// Java: jMock, EasyMock, Mockito

// 함수형 프로그래밍 패러다임
//	불변 객체 지향: 객체가 생성된 이후에 상태가 변하지 않는 객체, 멀티 쓰레드 안전
//	불변 객체 문제: 상태기반 검증이 불가 => 동작 검증 필요

// TDD(테스트 주도 개발) vs BDD(행위 주도 개발)
// 상태 검증					Mock을 많이 사용

// Google Mock 세팅
// 1. 정적 라이브러리로 빌드하는 것이 원칙입니다.
// 2. Google Mock은 Google Test에 의존성이 있습니다.
//		src 에 추가할 파일
//			gtest-all.cc
//			gmock-all.cc
//			gmock-main.cc
//		include path 에 추가할 경로
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

// gmock_main.cc를 gmock 프로젝트에 추가해서 빌드하면 아래의 main은 필요하지 않다.
#if 0
int main(int argc, char** argv)
{
//	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	// 이 안에서 InitGoogleTest도 수행되기 때문에 별도의 초기화가 필요하지 않습니다.

	return RUN_ALL_TESTS();
}
#endif

// 리눅스에서 gmock을 빌드하는 방법
// scripts/fuse_gmock_files.py 실행하면 gtest와 gmock이 합쳐진 파일이 나온다.
// gmock/gmock.h, gtest/gtest.h, gmock-gtest-all.cc
// gmock_main.cc 는 수동으로 복사해오자.

// $ g++ gmock-gtest-all.cc -c -I.	// 실행하면 object file 생성
// $ g++ gmock-main.cc -c -I.		// main 소스도 복사해와서 빌드
// $ ar crv gtest.a gmock-gtest-all.o gmock_main.o
//	=> gtest.a 생성

// 세팅하는 방법을 정리해놓으면 좋다.
// markdown으로 정리해서 github으로 관리하면 좋아.

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

// spy보다는 mock을 쓸수 있으면 mock framework를 통해서 해결하는 것이 간단하고 낫다.
