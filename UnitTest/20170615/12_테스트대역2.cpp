// 11. 테스트 대역

#include <string>
#include <iostream>
#include "gtest/gtest.h"

// 11_테스트대역.cpp 코드는 테스트 대역을 적용할 수 없는 설계입니다.
// 테스트 대역이 적용 가능한 설계의 핵심
//	=> 약한 결합

// 강한 결합: 협력 객체를 이용할 때, 구체적인 타입을 사용하는 것
// 약한 결합: 협력 객체를 이용할 때, 추상적인 타입을 사용하는 것
//		추상적인 타입: 추상 클래스 / 인터페이스

// 강한 결합 => 약한 결합 : 틈새 만들기
//	보통은 리팩토링이지만 테스트에서는 틈새 만들기

// 1. 협력 객체를 인터페이스나 추상 클래스를 통해 이용해야 한다.
//		=> DIP (의존관계 역전 원칙)

// 2. 의존하는 협력 객체를 직접 생성하는 것이 아니라,
//		외부에서 생성해서 전달 받아야 합니다. - 핵심!!
//		new는 반드시 구체적인 타입을 알아야 사용할 수 있습니다.
//		=> 의존성 주입(Dependency Injection)

// 의존성 주입을 할 수 밖에 없는 프레임워크
// Java: Spring framework
// Web: React, Angular

// 3. 의존성 주입 방법 2가지
//	1) 생성자 주입: 협력객체가 필수적일 때
//	2) 메소드 주입: 협력객체가 필수적이지 않을 때

// 4. 의존성 주입 문제점 - '보일러플레이트'
//	보일러플레이트: 반드시 필요하지만, 반복되는 코드
//	의존성 주입 프레임워크를 이용하면, 보일러플레이트를 효과적으로 관리하 할 수 있습니다.
//		(근데 C++에서는 썩 좋은 의존석 주입 프레임워크 없어... Java/Android는 Dagger2가 있다.)

// 가난한 자의 의존성 주입
// A* a = new A;
// B* a = new B;
// C* a = new C;
// User* user = new User(a,b,c);
// 객체를 생성할 때마다 이런 코드가 반복된다.



struct IFileSystem {
	virtual bool isValid(const std::string& filename) = 0;
	virtual ~IFileSystem() {}	// C++ 인터페이스에서는 반드시 가상소멸자 구현
};

// SUT
class FileSystem : public IFileSystem {
public:
	bool isValid(const std::string& filename) {
		// 파일 시스템 의존적인 코드
		// NTFS, FAT, HFS, ext3/4
		return true;
	}
};

// SUT
class Logger {
	IFileSystem* filesystem;
public:
	// 틈새 만들기: 기존에 객체를 생성하던 방식을 유지하는 것이 좋습니다.
	// 그냥 쓰면 기본 생성자 쓰는 기존 코드에서 에러남
	explicit Logger(IFileSystem* p=0) : filesystem(p) {
		if (p == 0)
			filesystem = new FileSystem;
	}

	// [filename].log 에서 filename이 5글자 이상인가?
	bool isValidFilename(const std::string& filename) {
		// 확장자 제거
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		// 이것도 여전히 구체 클래스인 FileSystem 필요! 아직 강한 결합
//		IFileSystem* system = new FileSystem;
		// 이제 약한 결합
		return filesystem->isValid(filename);
	}
};

// 무조건 True를 리턴하는 stub
// 고로 SUT인 Logger 내부에 대해서만 테스트할 수 있다!
// Fail이 뜨면 토큰 제거나 파일 이름 길이에서만 문제가 있는것이다.

class StubFileSystem : public IFileSystem {
public:
	bool isValid(const std::string& fielname) {
		return true;
	}
};

class LoggerTest : public ::testing::Test {};

TEST_F(LoggerTest, isValidFilename_NameLongerThan5Chars_True) {
	StubFileSystem stub;
	Logger logger(&stub);

	std::string good_name = "good_name.log";
	ASSERT_TRUE(logger.isValidFilename(good_name)) << "파일 이름이 다섯 글자 이상일 때";
}

// 각 단계의 코드가 구분될 수 있도록 하는 것이 좋습니다.
TEST_F(LoggerTest, isValidFilename_NameShorterThen5Chars_False) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string bad_name = "bad.log";

	bool actual = logger.isValidFilename(bad_name);
	ASSERT_FALSE(actual) << "파일 이름이 다섯 글자 미만일 때";
}

// 테스트 대역 목적: 테스트 대상 코드를 격리한다.
// 테스트 대역 종류 4가지
// 1. Test Stub
// 2. Fake Object
// 3. Test Spy
// 4. Mock Object


