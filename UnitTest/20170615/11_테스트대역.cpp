// 11. 테스트 대역

#include <string>
#include <iostream>
#include "gtest/gtest.h"

// SUT
class FileSystem {
public:
	bool isValid(const std::string& filename) {
		// 파일 시스템 의존적인 코드
		// NTFS, FAT, HFS, ext3/4
		return true;
	}
};

// SUT
class Logger {
public:
	// [filename].log 에서 filename이 5글자 이상인가?
	bool isValidFilename(const std::string& filename) {
		// 확장자 제거
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		FileSystem system;
		return system.isValid(filename);
	}
	// 문제: 검증하는 대상이 토큰 제거인지 글자수인지 파일시스템이 문제인지 알수가 없다.
	// FileSystem에도 의존적
	// 단위 테스트가 정확히 문제 지점을 알려주지 않는다 => 디버깅 해야한다.
	// 테스트 가능 설계 필요
};

class LoggerTest : public ::testing::Test {};

TEST_F(LoggerTest, isValidFilename_NameLongerThan5Chars_True) {
	Logger logger;
	// 네이밍, 문자열도 테스트와 연관된 내용으로
	std::string good_name = "good_name.log";

	// Act와 Assert가 혼재됨
	ASSERT_TRUE(logger.isValidFilename(good_name)) << "파일 이름이 다섯 글자 이상일 때";
}

// 각 단계의 코드가 구분될 수 있도록 하는 것이 좋습니다.
TEST_F(LoggerTest, isValidFilename_NameShorterThen5Chars_False) {
	Logger logger;
	std::string bad_name = "bad.log";

	// 테스트 코드에서는 Act, Assert가 구분되도록 이렇게 두 줄로 나눠주는게 낫다.
	bool actual = logger.isValidFilename(bad_name);
	ASSERT_FALSE(actual) << "파일 이름이 다섯 글자 미만일 때";
}

