// 11. �׽�Ʈ �뿪

#include <string>
#include <iostream>
#include "gtest/gtest.h"

// 11_�׽�Ʈ�뿪.cpp �ڵ�� �׽�Ʈ �뿪�� ������ �� ���� �����Դϴ�.
// �׽�Ʈ �뿪�� ���� ������ ������ �ٽ�
//	=> ���� ����

// ���� ����: ���� ��ü�� �̿��� ��, ��ü���� Ÿ���� ����ϴ� ��
// ���� ����: ���� ��ü�� �̿��� ��, �߻����� Ÿ���� ����ϴ� ��
//		�߻����� Ÿ��: �߻� Ŭ���� / �������̽�

// ���� ���� => ���� ���� : ƴ�� �����
//	������ �����丵������ �׽�Ʈ������ ƴ�� �����

// 1. ���� ��ü�� �������̽��� �߻� Ŭ������ ���� �̿��ؾ� �Ѵ�.
//		=> DIP (�������� ���� ��Ģ)

// 2. �����ϴ� ���� ��ü�� ���� �����ϴ� ���� �ƴ϶�,
//		�ܺο��� �����ؼ� ���� �޾ƾ� �մϴ�. - �ٽ�!!
//		new�� �ݵ�� ��ü���� Ÿ���� �˾ƾ� ����� �� �ֽ��ϴ�.
//		=> ������ ����(Dependency Injection)

// ������ ������ �� �� �ۿ� ���� �����ӿ�ũ
// Java: Spring framework
// Web: React, Angular

// 3. ������ ���� ��� 2����
//	1) ������ ����: ���°�ü�� �ʼ����� ��
//	2) �޼ҵ� ����: ���°�ü�� �ʼ������� ���� ��

// 4. ������ ���� ������ - '���Ϸ��÷���Ʈ'
//	���Ϸ��÷���Ʈ: �ݵ�� �ʿ�������, �ݺ��Ǵ� �ڵ�
//	������ ���� �����ӿ�ũ�� �̿��ϸ�, ���Ϸ��÷���Ʈ�� ȿ�������� ������ �� �� �ֽ��ϴ�.
//		(�ٵ� C++������ �� ���� ������ ���� �����ӿ�ũ ����... Java/Android�� Dagger2�� �ִ�.)

// ������ ���� ������ ����
// A* a = new A;
// B* a = new B;
// C* a = new C;
// User* user = new User(a,b,c);
// ��ü�� ������ ������ �̷� �ڵ尡 �ݺ��ȴ�.



struct IFileSystem {
	virtual bool isValid(const std::string& filename) = 0;
	virtual ~IFileSystem() {}	// C++ �������̽������� �ݵ�� ����Ҹ��� ����
};

// SUT
class FileSystem : public IFileSystem {
public:
	bool isValid(const std::string& filename) {
		// ���� �ý��� �������� �ڵ�
		// NTFS, FAT, HFS, ext3/4
		return true;
	}
};

// SUT
class Logger {
	IFileSystem* filesystem;
public:
	// ƴ�� �����: ������ ��ü�� �����ϴ� ����� �����ϴ� ���� �����ϴ�.
	// �׳� ���� �⺻ ������ ���� ���� �ڵ忡�� ������
	explicit Logger(IFileSystem* p=0) : filesystem(p) {
		if (p == 0)
			filesystem = new FileSystem;
	}

	// [filename].log ���� filename�� 5���� �̻��ΰ�?
	bool isValidFilename(const std::string& filename) {
		// Ȯ���� ����
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		// �̰͵� ������ ��ü Ŭ������ FileSystem �ʿ�! ���� ���� ����
//		IFileSystem* system = new FileSystem;
		// ���� ���� ����
		return filesystem->isValid(filename);
	}
};

// ������ True�� �����ϴ� stub
// ��� SUT�� Logger ���ο� ���ؼ��� �׽�Ʈ�� �� �ִ�!
// Fail�� �߸� ��ū ���ų� ���� �̸� ���̿����� ������ �ִ°��̴�.

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
	ASSERT_TRUE(logger.isValidFilename(good_name)) << "���� �̸��� �ټ� ���� �̻��� ��";
}

// �� �ܰ��� �ڵ尡 ���е� �� �ֵ��� �ϴ� ���� �����ϴ�.
TEST_F(LoggerTest, isValidFilename_NameShorterThen5Chars_False) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string bad_name = "bad.log";

	bool actual = logger.isValidFilename(bad_name);
	ASSERT_FALSE(actual) << "���� �̸��� �ټ� ���� �̸��� ��";
}

// �׽�Ʈ �뿪 ����: �׽�Ʈ ��� �ڵ带 �ݸ��Ѵ�.
// �׽�Ʈ �뿪 ���� 4����
// 1. Test Stub
// 2. Fake Object
// 3. Test Spy
// 4. Mock Object


