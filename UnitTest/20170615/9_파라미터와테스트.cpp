// SUT
bool isPrime(int value) {
	if (value < 2)
		return false;

	for (int i = 2; i < value; i++)
		if (value % i == 0)
			return false;

	return true;
}

#include "gtest/gtest.h"

// 데이터 중심의 테스트를 기존의 테스트와 동일하게 구현하면 쉽게 코드 중복이 발생합니다.
#if 0
TEST(PrimeTest, isPrime)
{
	EXPECT_TRUE(isPrime(2));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(5));
	EXPECT_TRUE(isPrime(7));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(13));
}
#endif

// Parameterized Test (파라미터화테스트)
//	=> 입력데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심의 테스트에서 중복을 없애주는 기법
//	: xUnit Test Framework에서 지원하는 기능

// 1. 상속 => ::testing::TestWithParam<입력데이터타입>
//		TestWithParam : 템플릿 클래스
class PrimeTest : public ::testing::TestWithParam<int> {

};

// 2. 데이터 셋 정의
INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest, ::testing::Values(2, 3, 5, 7, 11, 13));

// 3. 이제는 다양한 테스트 함수를 제공하면 됩니다.
// TEST
// TEST_F => Fixture 설치/해체 공유
// TEST_P => Parameterized
TEST_P(PrimeTest, isPrime)
{
	EXPECT_TRUE(isPrime(GetParam()));
}

TEST_P(PrimeTest, isPrime2)
{
	EXPECT_TRUE(isPrime(GetParam()));
}

// 문제점 (비용)
// 1. 테스트 이름에서 어떤 데이터로 테스트 하는지 알 수 없다.
//		출력값에 테스트 하는 실제값이 안나오고 1,2,3,.. 만 나온다. only gtest의 문제
//		가독성에 문제가 있다. => junit4에서는 해결
// 2. 일반적인 테스트와 데이터 중심의 테스트는 분리되서 관리될 수 밖에 없다.
//		=> junit5에서는 파라미터화 테스트는 사라짐. 통합 테스트

