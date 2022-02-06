// AwesomeMC
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/byte_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>

TEST(EndTag, Constructor)
{
    amc::EndTag endTag;

    EXPECT_EQ(amc::TagType::End, endTag.getType());
    EXPECT_STREQ("", endTag.getName().c_str());
}

TEST(EndTag, CopyConstructor)
{
    // Init
    amc::EndTag tagA;

    // Test Copy
    amc::EndTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
}

TEST(EndTag, MoveConstructor)
{
    // Init
    amc::EndTag tagA;

    // Test Copy
    amc::EndTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), "");
}

TEST(EndTag, CopyAssignment)
{
    // Init
    amc::EndTag tagA;

    // Test Copy
    amc::EndTag tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
}

TEST(EndTag, MoveAssignment)
{
    // Init
    amc::EndTag tagA;

    // Test Copy
    amc::EndTag tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), "");
}

TEST(EndTag, clone)
{
    amc::EndTag endTagA;

    amc::EndTag *endTagB = tag_cast<amc::EndTag*>(endTagA.clone());
    EXPECT_TRUE(endTagA == *endTagB);
    delete endTagB;
}

TEST(EndTag, Equal)
{
    amc::EndTag byteTagA;
    amc::EndTag byteTagB;
    amc::EndTag byteTagC;
    amc::EndTag byteTagD;
    amc::ByteTag byteTagE;
    amc::EndTag endTag;

    EXPECT_TRUE(byteTagA == byteTagA);  // Test same object
    EXPECT_TRUE(byteTagA == byteTagB);  // Test same data #1
    EXPECT_TRUE(byteTagA == byteTagC);  // Test same data #2
    byteTagC.setName("Test3");
    EXPECT_FALSE(byteTagA == byteTagC); // Test different data #2

    EXPECT_FALSE(byteTagE == endTag);   // Test different types
}

TEST(EndTag, NotEqual)
{
    amc::EndTag byteTagA;
    amc::EndTag byteTagB;
    amc::EndTag byteTagC;
    amc::EndTag byteTagD;
    amc::ByteTag byteTagE;
    amc::EndTag endTag;

    EXPECT_FALSE(byteTagA != byteTagA);  // Test same object
    EXPECT_FALSE(byteTagA != byteTagB);  // Test same data #1
    EXPECT_FALSE(byteTagA != byteTagC);  // Test same data #2
    byteTagC.setName("Test3");
    EXPECT_TRUE(byteTagA != byteTagC); // Test different data #2

    EXPECT_TRUE(byteTagE != endTag);   // Test different types
}

TEST(EndTag, getType)
{
    amc::EndTag byteTag;
    EXPECT_EQ(amc::TagType::End, byteTag.getType());
}

TEST(EndTag, getData)
{
    amc::EndTag endTag;

    std::vector<unsigned char> data1 = endTag.getData(true);
    EXPECT_EQ(1, data1.size());
    EXPECT_EQ(0, data1[0]);

    std::vector<unsigned char> data2 = endTag.getData(false);
    EXPECT_EQ(1, data2.size());
    EXPECT_EQ(0, data2[0]);
}

TEST(EndTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::EndTag();

    amc::EndTag *otherTag = tag_cast<amc::EndTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}

