// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// gtest
#include <gtest/gtest.h>

TEST(TagType, TypdeIds)
{
    EXPECT_EQ(0,  static_cast<int>(amc::TagType::End));
    EXPECT_EQ(1,  static_cast<int>(amc::TagType::Byte));
    EXPECT_EQ(2,  static_cast<int>(amc::TagType::Short));
    EXPECT_EQ(3,  static_cast<int>(amc::TagType::Int));
    EXPECT_EQ(4,  static_cast<int>(amc::TagType::Long));
    EXPECT_EQ(5,  static_cast<int>(amc::TagType::Float));
    EXPECT_EQ(6,  static_cast<int>(amc::TagType::Double));
    EXPECT_EQ(7,  static_cast<int>(amc::TagType::ByteArray));
    EXPECT_EQ(8,  static_cast<int>(amc::TagType::String));
    EXPECT_EQ(9,  static_cast<int>(amc::TagType::List));
    EXPECT_EQ(10, static_cast<int>(amc::TagType::Compound));
    EXPECT_EQ(11, static_cast<int>(amc::TagType::IntArray));
    EXPECT_EQ(12, static_cast<int>(amc::TagType::LongArray));
}