// AwesomeMC
#include <AwesomeMC/util/floating_point.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <cmath>

namespace detail
{

float sqrt(float value) {
    return std::sqrt(value);
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
        (*(reinterpret_cast<U*>(&negZero))) = one << (sizeof(U) * 8 - 1);
        (*(reinterpret_cast<U*>(&smallestDenormal))) += 1;

        nan1 = detail::sqrt(static_cast<T>(-1));
        nan2 = zero1 / zero2;
        inf = static_cast<T>(1) / zero1;
        nan3 = inf - inf;
        nan4 = nan3;

        (*(reinterpret_cast<U*>(&nan4))) += static_cast<U>(1);
    }

    virtual void TearDown()
    {

    }

    const U one = 1;
    const T zero1 = 0.0f;
    const T zero2 = 0.0f;
    T nan1 = 0.0f;
    T nan2 = 0.0f;
    T inf = 0.0f;
    T nan3 = 0.0f;
    T nan4 = 0.0f;
    T negZero = 0.0f;
    T smallestDenormal = 0.0f;
};

using FloatFixture = FloatingPointFixture<float, int32_t>;
using DoubleFixture = FloatingPointFixture<double, int64_t>;

// Float

TEST_F(FloatFixture, zero_negZero)
{
    EXPECT_TRUE(amc::almostEqualUlps(zero1, negZero, 10));
}

TEST_F(FloatFixture, negZero_zero)
{
    EXPECT_TRUE(amc::almostEqualUlps(negZero, zero1, 10));
}

TEST_F(FloatFixture, nearbyNumbers)
{
    EXPECT_TRUE(amc::almostEqualUlps(2.0f, 1.9999999f, 10));
}

TEST_F(FloatFixture, nearbyNumbersSwitched)
{
    EXPECT_TRUE(amc::almostEqualUlps(1.9999999f, 2.0f, 10));
}

TEST_F(FloatFixture, closeNumbers)
{
    EXPECT_TRUE(amc::almostEqualUlps(2.0f, 1.9999995f, 10));
}

TEST_F(FloatFixture, closeNumbersSwitched)
{
    EXPECT_TRUE(amc::almostEqualUlps(1.9999995f, 2.0f, 10));
}

TEST_F(FloatFixture, closeNumbers_10ulp)
{
    EXPECT_FALSE(amc::almostEqualUlps(2.0f, 1.9999988f, 9));
    EXPECT_FALSE(amc::almostEqualUlps(2.0f, 1.9999988f, 10));
    EXPECT_TRUE(amc::almostEqualUlps(2.0f, 1.9999988f, 11));
}

TEST_F(FloatFixture, inf_negInf)
{
    EXPECT_FALSE(amc::almostEqualUlps(inf, -inf, 16 * 1024 * 1024));
}

TEST_F(FloatFixture, max_inf)
{
    EXPECT_FALSE(amc::almostEqualUlps(FLT_MAX, inf, 10));
}

TEST_F(FloatFixture, same_nan)
{
    EXPECT_FALSE(amc::almostEqualUlps(nan2, nan2, 10));
}

TEST_F(FloatFixture, different_nan)
{
    EXPECT_FALSE(amc::almostEqualUlps(nan2, nan3, 10));
}

TEST_F(FloatFixture, smallestDenormal)
{
    EXPECT_FALSE(amc::almostEqualUlps(smallestDenormal, -smallestDenormal, 10));
}

// Double

TEST_F(DoubleFixture, zero_negZero)
{
    EXPECT_TRUE(amc::almostEqualUlps(zero1, negZero, 10ULL));
}

TEST_F(DoubleFixture, negZero_zero)
{
    EXPECT_TRUE(amc::almostEqualUlps(negZero, zero1, 10ULL));
}

TEST_F(DoubleFixture, nearbyNumbers)
{
    EXPECT_TRUE(amc::almostEqualUlps(2.0, 1.9999999999999999, 9ULL));
}

TEST_F(DoubleFixture, nearbyNumbersSwitched)
{
    EXPECT_TRUE(amc::almostEqualUlps(1.9999999999999999, 2.0, 9ULL));
}

TEST_F(DoubleFixture, closeNumbers)
{
    EXPECT_TRUE(amc::almostEqualUlps(2.0, 1.9999999999999995, 9ULL));
}

TEST_F(DoubleFixture, closeNumbersSwitched)
{
    EXPECT_TRUE(amc::almostEqualUlps(1.9999999999999995, 2.0, 9ULL));
}

TEST_F(DoubleFixture, closeNumbers_10ulp)
{
    EXPECT_FALSE(amc::almostEqualUlps(2.0, 1.9999999999999977, 9ULL));
    EXPECT_FALSE(amc::almostEqualUlps(2.0, 1.9999999999999977, 10ULL));
    EXPECT_TRUE(amc::almostEqualUlps(2.0, 1.9999999999999977, 11ULL));
}

TEST_F(DoubleFixture, inf_negInf)
{
    EXPECT_FALSE(amc::almostEqualUlps(inf, -inf, static_cast<int64_t>(16 * 1024 * 1024)));
}

TEST_F(DoubleFixture, max_inf)
{
    EXPECT_FALSE(amc::almostEqualUlps(DBL_MAX, inf, 10ULL));
}

TEST_F(DoubleFixture, same_nan)
{
    EXPECT_FALSE(amc::almostEqualUlps(nan2, nan2, 10ULL));
}

TEST_F(DoubleFixture, different_nan)
{
    EXPECT_FALSE(amc::almostEqualUlps(nan2, nan3, 10ULL));
}

TEST_F(DoubleFixture, smallestDenormal)
{
    EXPECT_FALSE(amc::almostEqualUlps(smallestDenormal, -smallestDenormal, 10ULL));
}
