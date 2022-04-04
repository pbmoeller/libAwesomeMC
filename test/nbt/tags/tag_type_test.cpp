// AwesomeMC
#include <AwesomeMC/nbt/tags/tag_type.hpp>

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

TEST(TagType, isValueTag)
{
    EXPECT_FALSE(isValueTag(amc::TagType::End));
    EXPECT_TRUE(isValueTag(amc::TagType::Byte));
    EXPECT_TRUE(isValueTag(amc::TagType::Short));
    EXPECT_TRUE(isValueTag(amc::TagType::Int));
    EXPECT_TRUE(isValueTag(amc::TagType::Long));
    EXPECT_TRUE(isValueTag(amc::TagType::Float));
    EXPECT_TRUE(isValueTag(amc::TagType::Double));
    EXPECT_FALSE(isValueTag(amc::TagType::ByteArray));
    EXPECT_TRUE(isValueTag(amc::TagType::String));
    EXPECT_FALSE(isValueTag(amc::TagType::List));
    EXPECT_FALSE(isValueTag(amc::TagType::Compound));
    EXPECT_FALSE(isValueTag(amc::TagType::IntArray));
    EXPECT_FALSE(isValueTag(amc::TagType::LongArray));
    EXPECT_FALSE(isValueTag(amc::TagType::Unknown));
}

TEST(TagType, isArrayTag)
{
    EXPECT_FALSE(isArrayTag(amc::TagType::End));
    EXPECT_FALSE(isArrayTag(amc::TagType::Byte));
    EXPECT_FALSE(isArrayTag(amc::TagType::Short));
    EXPECT_FALSE(isArrayTag(amc::TagType::Int));
    EXPECT_FALSE(isArrayTag(amc::TagType::Long));
    EXPECT_FALSE(isArrayTag(amc::TagType::Float));
    EXPECT_FALSE(isArrayTag(amc::TagType::Double));
    EXPECT_TRUE(isArrayTag(amc::TagType::ByteArray));
    EXPECT_FALSE(isArrayTag(amc::TagType::String));
    EXPECT_FALSE(isArrayTag(amc::TagType::List));
    EXPECT_FALSE(isArrayTag(amc::TagType::Compound));
    EXPECT_TRUE(isArrayTag(amc::TagType::IntArray));
    EXPECT_TRUE(isArrayTag(amc::TagType::LongArray));
    EXPECT_FALSE(isArrayTag(amc::TagType::Unknown));
}

TEST(TagType, isContainerTag)
{
    EXPECT_FALSE(isContainerTag(amc::TagType::End));
    EXPECT_FALSE(isContainerTag(amc::TagType::Byte));
    EXPECT_FALSE(isContainerTag(amc::TagType::Short));
    EXPECT_FALSE(isContainerTag(amc::TagType::Int));
    EXPECT_FALSE(isContainerTag(amc::TagType::Long));
    EXPECT_FALSE(isContainerTag(amc::TagType::Float));
    EXPECT_FALSE(isContainerTag(amc::TagType::Double));
    EXPECT_FALSE(isContainerTag(amc::TagType::ByteArray));
    EXPECT_FALSE(isContainerTag(amc::TagType::String));
    EXPECT_TRUE(isContainerTag(amc::TagType::List));
    EXPECT_TRUE(isContainerTag(amc::TagType::Compound));
    EXPECT_FALSE(isContainerTag(amc::TagType::IntArray));
    EXPECT_FALSE(isContainerTag(amc::TagType::LongArray));
    EXPECT_FALSE(isContainerTag(amc::TagType::Unknown));
}

TEST(TagType, getTagTypeName)
{
    EXPECT_STREQ("End",             amc::getTagTypeName(amc::TagType::End).c_str());
    EXPECT_STREQ("Byte",            amc::getTagTypeName(amc::TagType::Byte).c_str());
    EXPECT_STREQ("Short",           amc::getTagTypeName(amc::TagType::Short).c_str());
    EXPECT_STREQ("Int",             amc::getTagTypeName(amc::TagType::Int).c_str());
    EXPECT_STREQ("Long",            amc::getTagTypeName(amc::TagType::Long).c_str());
    EXPECT_STREQ("Float",           amc::getTagTypeName(amc::TagType::Float).c_str());
    EXPECT_STREQ("Double",          amc::getTagTypeName(amc::TagType::Double).c_str());
    EXPECT_STREQ("ByteArray",       amc::getTagTypeName(amc::TagType::ByteArray).c_str());
    EXPECT_STREQ("String",          amc::getTagTypeName(amc::TagType::String).c_str());
    EXPECT_STREQ("List",            amc::getTagTypeName(amc::TagType::List).c_str());
    EXPECT_STREQ("Compound",        amc::getTagTypeName(amc::TagType::Compound).c_str());
    EXPECT_STREQ("IntArray",        amc::getTagTypeName(amc::TagType::IntArray).c_str());
    EXPECT_STREQ("LongArray",       amc::getTagTypeName(amc::TagType::LongArray).c_str());
}

TEST(TagType, getTagName)
{
    EXPECT_STREQ("EndTag",          amc::getTagName(amc::TagType::End).c_str());
    EXPECT_STREQ("ByteTag",         amc::getTagName(amc::TagType::Byte).c_str());
    EXPECT_STREQ("ShortTag",        amc::getTagName(amc::TagType::Short).c_str());
    EXPECT_STREQ("IntTag",          amc::getTagName(amc::TagType::Int).c_str());
    EXPECT_STREQ("LongTag",         amc::getTagName(amc::TagType::Long).c_str());
    EXPECT_STREQ("FloatTag",        amc::getTagName(amc::TagType::Float).c_str());
    EXPECT_STREQ("DoubleTag",       amc::getTagName(amc::TagType::Double).c_str());
    EXPECT_STREQ("ByteArrayTag",    amc::getTagName(amc::TagType::ByteArray).c_str());
    EXPECT_STREQ("StringTag",       amc::getTagName(amc::TagType::String).c_str());
    EXPECT_STREQ("ListTag",         amc::getTagName(amc::TagType::List).c_str());
    EXPECT_STREQ("CompoundTag",     amc::getTagName(amc::TagType::Compound).c_str());
    EXPECT_STREQ("IntArrayTag",     amc::getTagName(amc::TagType::IntArray).c_str());
    EXPECT_STREQ("LongArrayTag",    amc::getTagName(amc::TagType::LongArray).c_str());
}