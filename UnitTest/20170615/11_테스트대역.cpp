// 11. �׽�Ʈ �뿪

#include <string>
#include <iostream>
#include "gtest/gtest.h"

// SUT
class FileSystem {
public:
	bool isValid(const std::string& filename) {
		// ���� �ý��� �������� �ڵ�
		// NTFS, FAT, HFS, ext3/4
		return true;
	}
};

// SUT
class Logger {
public:
	// [filename].log ���� filename�� 5���� �̻��ΰ�?
	bool isValidFilename(const std::string& filename) {
		// Ȯ���� ����
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		FileSystem system;
		return system.isValid(filename);
	}
	// ����: �����ϴ� ����� ��ū �������� ���ڼ����� ���Ͻý����� �������� �˼��� ����.
	// FileSystem���� ������
	// ���� �׽�Ʈ�� ��Ȯ�� ���� ������ �˷����� �ʴ´� => ����� �ؾ��Ѵ�.
	// �׽�Ʈ ���� ���� �ʿ�
};

class LoggerTest : public ::testing::Test {};

TEST_F(LoggerTest, isValidFilename_NameLongerThan5Chars_True) {
	Logger logger;
	// ���̹�, ���ڿ��� �׽�Ʈ�� ������ ��������
	std::string good_name = "good_name.log";

	// Act�� Assert�� ȥ���
	ASSERT_TRUE(logger.isValidFilename(good_name)) << "���� �̸��� �ټ� ���� �̻��� ��";
}

// �� �ܰ��� �ڵ尡 ���е� �� �ֵ��� �ϴ� ���� �����ϴ�.
TEST_F(LoggerTest, isValidFilename_NameShorterThen5Chars_False) {
	Logger logger;
	std::string bad_name = "bad.log";

	// �׽�Ʈ �ڵ忡���� Act, Assert�� ���еǵ��� �̷��� �� �ٷ� �����ִ°� ����.
	bool actual = logger.isValidFilename(bad_name);
	ASSERT_FALSE(actual) << "���� �̸��� �ټ� ���� �̸��� ��";
}

