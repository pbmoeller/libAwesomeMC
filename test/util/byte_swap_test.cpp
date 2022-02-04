// AwesomeMC
#include <AwesomeMC/util/byte_swap.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <climits>
#include <cstdint>

union Float
{
    float value;
    unsigned char bytes[4];
};
union Double
{
    double value;
    unsigned char bytes[8];
};

void compareBytes(const Float &f1, const Float &f2)
{
    EXPECT_EQ(f1.bytes[0], f2.bytes[3]);
    EXPECT_EQ(f1.bytes[1], f2.bytes[2]);
    EXPECT_EQ(f1.bytes[2], f2.bytes[1]);
    EXPECT_EQ(f1.bytes[3], f2.bytes[0]);
}

void compareBytes(const Double &d1, const Double &d2)
{
    EXPECT_EQ(d1.bytes[0], d2.bytes[7]);
    EXPECT_EQ(d1.bytes[1], d2.bytes[6]);
    EXPECT_EQ(d1.bytes[2], d2.bytes[5]);
    EXPECT_EQ(d1.bytes[3], d2.bytes[4]);
    EXPECT_EQ(d1.bytes[4], d2.bytes[3]);
    EXPECT_EQ(d1.bytes[5], d2.bytes[2]);
    EXPECT_EQ(d1.bytes[6], d2.bytes[1]);
    EXPECT_EQ(d1.bytes[7], d2.bytes[0]);
}

TEST(bswap, 1B)
{
    int8_t value_1 = -128;
    int8_t value_2 = 0;
    int8_t value_3 = 127;

    uint8_t value_4 = 0;
    uint8_t value_5 = 127;
    uint8_t value_6 = 255;

    EXPECT_EQ(value_1, util::bswap(value_1));
    EXPECT_EQ(value_2, util::bswap(value_2));
    EXPECT_EQ(value_3, util::bswap(value_3));
    EXPECT_EQ(value_4, util::bswap(value_4));
    EXPECT_EQ(value_5, util::bswap(value_5));
    EXPECT_EQ(value_6, util::bswap(value_6));
}

TEST(bswap, 2B)
{
    int16_t value_1     = 0x1000;
    int16_t value_1_exp = 0x0010;
    int16_t value_2     = 0x0000;
    int16_t value_2_exp = 0x0000;
    int16_t value_3     = 0x7FFF;
    int16_t value_3_exp = 0xFF7Fu;

    uint16_t value_4        = 0x1000;
    uint16_t value_4_exp    = 0x0010;
    uint16_t value_5        = 0x00FF;
    uint16_t value_5_exp    = 0xFF00;
    uint16_t value_6        = 0x7FFF;
    uint16_t value_6_exp    = 0xFF7F;
    uint16_t value_7        = 0xABCD;
    uint16_t value_7_exp    = 0xCDAB;

    EXPECT_EQ(value_1_exp, util::bswap(value_1));
    EXPECT_EQ(value_2_exp, util::bswap(value_2));
    EXPECT_EQ(value_3_exp, util::bswap(value_3));
    EXPECT_EQ(value_4_exp, util::bswap(value_4));
    EXPECT_EQ(value_5_exp, util::bswap(value_5));
    EXPECT_EQ(value_6_exp, util::bswap(value_6));
    EXPECT_EQ(value_7_exp, util::bswap(value_7));
}

TEST(bswap, 4B)
{
    int32_t value_1     = 0x10000000;
    int32_t value_1_exp = 0x00000010;
    int32_t value_2     = 0x00000000;
    int32_t value_2_exp = 0x00000000;
    int32_t value_3     = 0x7FFFFFFF;
    int32_t value_3_exp = 0xFFFFFF7F;

    uint32_t value_4        = 0x10000000;
    uint32_t value_4_exp    = 0x00000010;
    uint32_t value_5        = 0x00FF00FF;
    uint32_t value_5_exp    = 0xFF00FF00;
    uint32_t value_6        = 0x7FFFFFFF;
    uint32_t value_6_exp    = 0xFFFFFF7F;
    uint32_t value_7        = 0xABCDEF01;
    uint32_t value_7_exp    = 0x01EFCDAB;

    EXPECT_EQ(value_1_exp, util::bswap(value_1));
    EXPECT_EQ(value_2_exp, util::bswap(value_2));
    EXPECT_EQ(value_3_exp, util::bswap(value_3));
    EXPECT_EQ(value_4_exp, util::bswap(value_4));
    EXPECT_EQ(value_5_exp, util::bswap(value_5));
    EXPECT_EQ(value_6_exp, util::bswap(value_6));
    EXPECT_EQ(value_7_exp, util::bswap(value_7));
}

TEST(bswap, 8B)
{
    int64_t value_1     = 0x1000000000000000;
    int64_t value_1_exp = 0x0000000000000010;
    int64_t value_2     = 0x0000000000000000;
    int64_t value_2_exp = 0x0000000000000000;
    int64_t value_3     = 0x7FFFFFFFFFFFFFFF;
    int64_t value_3_exp = 0xFFFFFFFFFFFFFF7F;

    uint64_t value_4        = 0x1000000000000000;
    uint64_t value_4_exp    = 0x0000000000000010;
    uint64_t value_5        = 0x00FF00FF00FF00FF;
    uint64_t value_5_exp    = 0xFF00FF00FF00FF00;
    uint64_t value_6        = 0x7FFFFFFFFFFFFFFF;
    uint64_t value_6_exp    = 0xFFFFFFFFFFFFFF7F;
    uint64_t value_7        = 0xABCDEF0123456789;
    uint64_t value_7_exp    = 0x8967452301EFCDAB;
    uint64_t value_8        = 0x0AB00CD00EF00120;
    uint64_t value_8_exp    = 0x2001F00ED00CB00A;

    EXPECT_EQ(value_1_exp, util::bswap(value_1));
    EXPECT_EQ(value_2_exp, util::bswap(value_2));
    EXPECT_EQ(value_3_exp, util::bswap(value_3));
    EXPECT_EQ(value_4_exp, util::bswap(value_4));
    EXPECT_EQ(value_5_exp, util::bswap(value_5));
    EXPECT_EQ(value_6_exp, util::bswap(value_6));
    EXPECT_EQ(value_7_exp, util::bswap(value_7));
    EXPECT_EQ(value_8_exp, util::bswap(value_8));
}

TEST(bswap, Float)
{
    Float value1{1.0f};
    Float actual1{util::bswap(value1.value)};
    compareBytes(value1, actual1);

    Float value2{123.456789f};
    Float actual2{util::bswap(value2.value)};
    compareBytes(value2, actual2);

    Float value3{-1.0f};
    Float actual3{util::bswap(value3.value)};
    compareBytes(value3, actual3);

    Float value4{0.0f};
    Float actual4{util::bswap(value4.value)};
    compareBytes(value4, actual4);

    Float value5{std::numeric_limits<float>::max()};
    Float actual5{util::bswap(value5.value)};
    compareBytes(value5, actual5);

    Float value6{std::numeric_limits<float>::min()};
    Float actual6{util::bswap(value6.value)};
    compareBytes(value6, actual6);
}

TEST(bswap, Double)
{
    Double value1{1.0};
    Double actual1{util::bswap(value1.value)};
    compareBytes(value1, actual1);

    Double value2{123.456789};
    Double actual2{util::bswap(value2.value)};
    compareBytes(value2, actual2);

    Double value3{-1.0};
    Double actual3{util::bswap(value3.value)};
    compareBytes(value3, actual3);

    Double value4{0.0};
    Double actual4{util::bswap(value4.value)};
    compareBytes(value4, actual4);

    Double value5{std::numeric_limits<double>::max()};
    Double actual5{util::bswap(value5.value)};
    compareBytes(value5, actual5);

    Double value6{std::numeric_limits<double>::min()};
    Double actual6{util::bswap(value6.value)};
    compareBytes(value6, actual6);
}