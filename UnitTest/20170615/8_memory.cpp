// Memory
// => Ư�� ����� �̿��Ͽ��� ��, �޸𸮿� ������ �߻��ϴ��� ���θ� �����ϰ� �ʹ�.

#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"

#if 0
class Image {
public:
	void* operator new(size_t size) {
		printf("��ü �Ҵ�..\n");
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("��ü �ı�..\n");
		free(p);
	}
};

TEST(ImageTest, memory)
{
	Image* image = new Image;
	// 1. operator new(sizeof(Image));
	// 2. ������ ȣ��

	delete image;
}
#endif

// �޸� �Ҵ� ������ ���� ī��Ʈ�� �ؼ� �޸� ���� Ȯ��
/*
class Image {
public:
	static int allocCount;
	void* operator new(size_t size) {
		printf("��ü �Ҵ�..\n");
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("��ü �ı�..\n");
		--allocCount;
		free(p);
	}
};

int Image::allocCount = 0;
*/

// �̷��� ������ �ڵ�� �ݺ��ǹǷ� ��ũ�η� ������!

#define DECLARE_LEAK_TEST()				\
public:									\
static int allocCount;					\
void* operator new(size_t size) {		\
	printf("��ü �Ҵ�..\n");				\
	++allocCount;						\
	return malloc(size);				\
}										\
										\
void operator delete(void* p, size_t) { \
		printf("��ü �ı�..\n");			\
		--allocCount;					\
		free(p);						\
}

#define IMPLEMENT_LEAK_TEST(classname)	\
	int classname::allocCount = 0;

class Image {
	DECLARE_LEAK_TEST();
};

IMPLEMENT_LEAK_TEST(Image);


class ImageTest : public ::testing::Test {
protected:
	int count;
	void SetUp() {
		count = Image::allocCount;
	}

	void TearDown() {
		int diff = abs(count - Image::allocCount);
		EXPECT_EQ(0, diff) << "leaked " << diff << " object(s)";
	}
};

void foo()
{
	Image* p1 = new Image;
	Image* p2 = new Image;

	delete p1;
}

TEST_F(ImageTest, foo)
{
	foo();
}


