// AwesomeMC
#include <AwesomeMC/util/bit.hpp>

// gtest
#include <gtest/gtest.h>

TEST(bit, setNLeastSignificantBits16)
{
    EXPECT_EQ(0b00000000'00000000u, amc::setNLeastSignificantBits16(0));
    EXPECT_EQ(0b00000000'00000111u, amc::setNLeastSignificantBits16(3));
    EXPECT_EQ(0b00000000'11111111u, amc::setNLeastSignificantBits16(8));
    EXPECT_EQ(0b11111111'11111111u, amc::setNLeastSignificantBits16(16));
}

TEST(bit, setNLeastSignificantBits32)
{
    EXPECT_EQ(0b00000000'00000000'00000000'00000000u, amc::setNLeastSignificantBits32(0));
    EXPECT_EQ(0b00000000'00000000'00000000'00000111u, amc::setNLeastSignificantBits32(3));
    EXPECT_EQ(0b00000000'00000000'00000000'11111111u, amc::setNLeastSignificantBits32(8));
    EXPECT_EQ(0b00000000'00000000'11111111'11111111u, amc::setNLeastSignificantBits32(16));
    EXPECT_EQ(0b00000000'11111111'11111111'11111111u, amc::setNLeastSignificantBits32(24));
    EXPECT_EQ(0b11111111'11111111'11111111'11111111u, amc::setNLeastSignificantBits32(32));
}

TEST(bit, setNLeastSignificantBits64)
{
    EXPECT_EQ(0x0000'0000'0000'0000ULL, amc::setNLeastSignificantBits64(0));
    EXPECT_EQ(0x0000'0000'0000'0007ULL, amc::setNLeastSignificantBits64(3));
    EXPECT_EQ(0x0000'0000'0000'00FFULL, amc::setNLeastSignificantBits64(8));
    EXPECT_EQ(0x0000'0000'0000'FFFFULL, amc::setNLeastSignificantBits64(16));
    EXPECT_EQ(0x0000'0000'FFFF'FFFFULL, amc::setNLeastSignificantBits64(32));
    EXPECT_EQ(0x0000'FFFF'FFFF'FFFFULL, amc::setNLeastSignificantBits64(48));
    EXPECT_EQ(0xFFFF'FFFF'FFFF'FFFFULL, amc::setNLeastSignificantBits64(64));
}