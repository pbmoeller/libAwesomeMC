#include "nbt/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(EndTag, Constructor)
{
    nbt::EndTag endTag;

    EXPECT_EQ(nbt::TagType::End, endTag.getType());
    EXPECT_STREQ("", endTag.getName().c_str());
}

TEST(EndTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, Equal)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, NotEqual)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, getData)
{
    nbt::EndTag endTag;

    std::vector<unsigned char> data1 = endTag.getData(true);
    EXPECT_EQ(1, data1.size());
    EXPECT_EQ(0, data1[0]);

    std::vector<unsigned char> data2 = endTag.getData(false);
    EXPECT_EQ(1, data2.size());
    EXPECT_EQ(0, data2[0]);
}

