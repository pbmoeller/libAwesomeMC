// AwesomeMC
#include <AwesomeMC/util/bit.hpp>

// gtest
#include <gtest/gtest.h>

TEST(bit, setNLeastSignificantBits16)
{
    EXPECT_EQ(0b00000000'00000000, util::setNLeastSignificantBits16(0));
    EXPECT_EQ(0b00000000'00000111, util::setNLeastSignificantBits16(3));
    EXPECT_EQ(0b00000000'11111111, util::setNLeastSignificantBits16(8));
    EXPECT_EQ(0b11111111'11111111, util::setNLeastSignificantBits16(16));
}

TEST(bit, setNLeastSignificantBits32)
{
    EXPECT_EQ(0b00000000'00000000'00000000'00000000, util::setNLeastSignificantBits32(0));
    EXPECT_EQ(0b00000000'00000000'00000000'00000111, util::setNLeastSignificantBits32(3));
    EXPECT_EQ(0b00000000'00000000'00000000'11111111, util::setNLeastSignificantBits32(8));
    EXPECT_EQ(0b00000000'00000000'11111111'11111111, util::setNLeastSignificantBits32(16));
    EXPECT_EQ(0b00000000'11111111'11111111'11111111, util::setNLeastSignificantBits32(24));
    EXPECT_EQ(0b11111111'11111111'11111111'11111111, util::setNLeastSignificantBits32(32));
}

TEST(bit, setNLeastSignificantBits64)
{
    EXPECT_EQ(0x0000'0000'0000'0000, util::setNLeastSignificantBits64(0));
    EXPECT_EQ(0x0000'0000'0000'0007, util::setNLeastSignificantBits64(3));
    EXPECT_EQ(0x0000'0000'0000'00FF, util::setNLeastSignificantBits64(8));
    EXPECT_EQ(0x0000'0000'0000'FFFF, util::setNLeastSignificantBits64(16));
    EXPECT_EQ(0x0000'0000'FFFF'FFFF, util::setNLeastSignificantBits64(32));
    EXPECT_EQ(0x0000'FFFF'FFFF'FFFF, util::setNLeastSignificantBits64(48));
    EXPECT_EQ(0xFFFF'FFFF'FFFF'FFFF, util::setNLeastSignificantBits64(64));
}