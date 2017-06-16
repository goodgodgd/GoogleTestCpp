// Memory
// => 특정 기능을 이용하였을 때, 메모리에 누수가 발생하는지 여부를 검증하고 싶다.

#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"

#if 0
class Image {
public:
	void* operator new(size_t size) {
		printf("객체 할당..\n");
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("객체 파괴..\n");
		free(p);
	}
};

TEST(ImageTest, memory)
{
	Image* image = new Image;
	// 1. operator new(sizeof(Image));
	// 2. 생성자 호출

	delete image;
}
#endif

// 메모리 할당 해제에 대한 카운트를 해서 메모리 누수 확인
/*
class Image {
public:
	static int allocCount;
	void* operator new(size_t size) {
		printf("객체 할당..\n");
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("객체 파괴..\n");
		--allocCount;
		free(p);
	}
};

int Image::allocCount = 0;
*/

// 이러한 형태의 코드는 반복되므로 매크로로 만들어보자!

#define DECLARE_LEAK_TEST()				\
public:									\
static int allocCount;					\
void* operator new(size_t size) {		\
	printf("객체 할당..\n");				\
	++allocCount;						\
	return malloc(size);				\
}										\
										\
void operator delete(void* p, size_t) { \
		printf("객체 파괴..\n");			\
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


