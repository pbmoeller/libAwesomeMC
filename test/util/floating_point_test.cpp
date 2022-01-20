// AwesomeMC
#include <AwesomeMC/util/floating_point.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <cmath>

namespace detail
{

float sqrt(float value) {
    return std::sqrtf(value);
}

double sqrt(double value) {
    return std::sqrt(value);
}

} // namespace detail

template<typename T, typename U>
class FloatingPointFixture : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        (*(U *)&negZero) = one << (sizeof(U) * 8 -1);
        (*(U *)&smallestDenormal) += 1;

        nan1 = detail::sqrt(static_cast<T>(-1));
        nan2 = zero1 / zero2;
        inf = static_cast<T>(1) / zero1;
        nan3 = inf - inf;
        nan4 = nan3;

        (*(U *)&nan4) += static_cast<U>(1);
    }

    virtual void TearDown()
    {

    }

    const U one = 1;
    const T zero1 = 0.0f;
    const T zero2 = 0.0f;
    T nan1;
    T nan2;
    T inf;
    T nan3 = inf - inf;
    T nan4 = nan3;
    T negZero = 0;
    T smallestDenormal;
};

using FloatFixture = FloatingPointFixture<float, int32_t>;
using DoubleFixture = FloatingPointFixture<double, int64_t>;

// Float

TEST_F(FloatFixture, zero_negZero)
{
    EXPECT_TRUE(util::almostEqualUlps(zero1, negZero, 10));
}

TEST_F(FloatFixture, negZero_zero)
{
    EXPECT_TRUE(util::almostEqualUlps(negZero, zero1, 10));
}

TEST_F(FloatFixture, nearbyNumbers)
{
    EXPECT_TRUE(util::almostEqualUlps(2.0f, 1.9999999f, 10));
}

TEST_F(FloatFixture, nearbyNumbersSwitched)
{
    EXPECT_TRUE(util::almostEqualUlps(2.0f, 1.9999999f, 10));
}

TEST_F(FloatFixture, closeNumbers)
{
    EXPECT_TRUE(util::almostEqualUlps(2.0f, 1.9999995f, 10));
}

TEST_F(FloatFixture, closeNumbersSwitched)
{
    EXPECT_TRUE(util::almostEqualUlps(1.9999995f, 2.0f, 10));
}

TEST_F(FloatFixture, inf_negInf)
{
    EXPECT_FALSE(util::almostEqualUlps(inf, -inf, 16 * 1024 * 1024));
}

TEST_F(FloatFixture, max_inf)
{
    EXPECT_FALSE(util::almostEqualUlps(FLT_MAX, inf, 10));
}

TEST_F(FloatFixture, same_nan)
{
    EXPECT_FALSE(util::almostEqualUlps(nan2, nan2, 10));
}

TEST_F(FloatFixture, different_nan)
{
    EXPECT_FALSE(util::almostEqualUlps(nan2, nan3, 10));
}

TEST_F(FloatFixture, smallestDenormal)
{
    EXPECT_FALSE(util::almostEqualUlps(smallestDenormal, -smallestDenormal, 10));
}

// Double

TEST_F(DoubleFixture, zero_negZero)
{
    EXPECT_TRUE(util::almostEqualUlps(zero1, negZero, (int64_t)10));
}

TEST_F(DoubleFixture, negZero_zero)
{
    EXPECT_TRUE(util::almostEqualUlps(negZero, zero1, (int64_t)10));
}

TEST_F(DoubleFixture, nearbyNumbers)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST_F(DoubleFixture, nearbyNumbersSwitched)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST_F(DoubleFixture, closeNumbers)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST_F(DoubleFixture, closeNumbersSwitched)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST_F(DoubleFixture, inf_negInf)
{
    EXPECT_FALSE(util::almostEqualUlps(inf, -inf, (int64_t)16 * 1024 * 1024));
}

TEST_F(DoubleFixture, max_inf)
{
    EXPECT_FALSE(util::almostEqualUlps(DBL_MAX, inf, (int64_t)10));
}

TEST_F(DoubleFixture, same_nan)
{
    EXPECT_FALSE(util::almostEqualUlps(nan2, nan2, (int64_t)10));
}

TEST_F(DoubleFixture, different_nan)
{
    EXPECT_FALSE(util::almostEqualUlps(nan2, nan3, (int64_t)10));
}

TEST_F(DoubleFixture, smallestDenormal)
{
    EXPECT_FALSE(util::almostEqualUlps(smallestDenormal, -smallestDenormal, (int64_t)10));
}
