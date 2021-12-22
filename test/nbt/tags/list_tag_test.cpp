#include "nbt/tags/list_tag.hpp"
#include "nbt/tags/end_tag.hpp"
#include "nbt/tags/byte_tag.hpp"
#include "nbt/tags/int_tag.hpp"
#include "nbt/tags/float_tag.hpp"
#include "nbt/tags/long_tag.hpp"
#include "util/byte_swap.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ListTag, Constructor)
{
    nbt::ListTag listTag;
    EXPECT_STREQ("", listTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::List, listTag.getType());
    EXPECT_EQ(nbt::TagType::Byte, listTag.getListType());
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_2)
{
    nbt::ListTag listTag("Tagname");
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::List, listTag.getType());
    EXPECT_EQ(nbt::TagType::Byte, listTag.getListType());
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_3)
{
    nbt::ListTag listTag("Tagname");
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::List, listTag.getType());
    EXPECT_EQ(nbt::TagType::Byte, listTag.getListType());
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_4)
{
    nbt::ListTag listTag("Tagname", nbt::TagType::Float);
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::List, listTag.getType());
    EXPECT_EQ(nbt::TagType::Float, listTag.getListType());
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, CopyConstructor)
{
    std::string name = "CopyConstructor";

    // Init A
    nbt::ListTag listTagA(name, nbt::TagType::Byte);
    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Test Copy Assignment
    nbt::ListTag listTagB(listTagA);
    EXPECT_STREQ(listTagB.getName().c_str(), listTagA.getName().c_str());
    EXPECT_EQ(3, listTagB.size());
}

TEST(ListTag, MoveConstructor)
{
    std::string name = "MoveConstructor";

    // Init A
    nbt::ListTag listTagA(name, nbt::TagType::Byte);
    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Test Copy Assignment
    nbt::ListTag listTagB(std::move(listTagA));
    EXPECT_STREQ(listTagB.getName().c_str(), name.c_str());
    EXPECT_EQ(3, listTagB.size());
}

TEST(ListTag, CopyAssignment)
{
    std::string name = "CopyAssignment";

    // Init A
    nbt::ListTag listTagA(name, nbt::TagType::Byte);
    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Init B
    nbt::ListTag listTagB;
    ASSERT_STREQ(listTagB.getName().c_str(), "");
    ASSERT_EQ(0, listTagB.size());

    // Test Copy Assignment
    listTagB = listTagA;
    EXPECT_STREQ(listTagB.getName().c_str(), listTagA.getName().c_str());
    EXPECT_EQ(3, listTagB.size());
}

TEST(ListTag, MoveAssignment)
{
    std::string name = "MoveAssignment";

    // Init A
    nbt::ListTag listTagA(name, nbt::TagType::Byte);
    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Init B
    nbt::ListTag listTagB;
    ASSERT_STREQ(listTagB.getName().c_str(), "");
    ASSERT_EQ(0, listTagB.size());

    // Test Move Assignment
    listTagB = std::move(listTagA);
    EXPECT_STREQ(listTagB.getName().c_str(), name.c_str());
    EXPECT_EQ(3, listTagB.size());
}

TEST(ListTag, clone)
{
    // Init List A
    nbt::ListTag listTagA(nbt::TagType::Byte);

    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, listTagA.size());

    nbt::ListTag *listClone = (nbt::ListTag *)listTagA.clone();

    EXPECT_TRUE(listTagA == *listClone);
}

TEST(ListTag, Equal)
{
    // Init List A
    nbt::ListTag listTagA(nbt::TagType::Byte);

    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, listTagA.size());

    // Init List B
    nbt::ListTag listTagB(nbt::TagType::Byte);

    listTagB.pushBack(new nbt::ByteTag("A", 1));
    listTagB.pushBack(new nbt::ByteTag("B", 2));
    listTagB.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, listTagB.size());

    EXPECT_TRUE(listTagA == listTagA);
    EXPECT_TRUE(listTagA == listTagB);

    // Change B
    listTagB.erase(2);
    EXPECT_FALSE(listTagA == listTagB);

    // Make equal again
    listTagA.erase(2);
    EXPECT_TRUE(listTagA == listTagB);

    listTagA.setName("bla");
    EXPECT_FALSE(listTagA == listTagB);
}

TEST(ListTag, NotEqual)
{
    // Init List A
    nbt::ListTag listTagA(nbt::TagType::Byte);

    listTagA.pushBack(new nbt::ByteTag("A", 1));
    listTagA.pushBack(new nbt::ByteTag("B", 2));
    listTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, listTagA.size());

    // Init List B
    nbt::ListTag listTagB(nbt::TagType::Byte);

    listTagB.pushBack(new nbt::ByteTag("A", 1));
    listTagB.pushBack(new nbt::ByteTag("B", 2));
    listTagB.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, listTagB.size());

    EXPECT_FALSE(listTagA != listTagA);
    EXPECT_FALSE(listTagA != listTagB);

    // Change B
    listTagB.erase(2);
    EXPECT_TRUE(listTagA != listTagB);

    // Make equal again
    listTagA.erase(2);
    EXPECT_FALSE(listTagA != listTagB);

    // Change name
    listTagA.setName("bla");
    EXPECT_TRUE(listTagA != listTagB);
}

TEST(ListTag, getType)
{
    nbt::ListTag listTag;
    EXPECT_EQ(nbt::TagType::List, listTag.getType());
}

TEST(ListTag, getListType)
{
    nbt::ListTag listTag;
    EXPECT_EQ(nbt::TagType::Byte, listTag.getListType());

    nbt::ListTag listTag2(nbt::TagType::Float);
    EXPECT_EQ(nbt::TagType::Float, listTag2.getListType());
}

TEST(ListTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x09, 0x00, 0x0F, 0x6C, 0x69, 0x73, 0x74, 0x54,
        0x65, 0x73, 0x74, 0x20, 0x28, 0x6C, 0x6F, 0x6E,
        0x67, 0x29, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F
    };

    nbt::ListTag listTag("listTest (long)", nbt::TagType::Long);
    listTag.pushBack(new nbt::LongTag(11));
    listTag.pushBack(new nbt::LongTag(12));
    listTag.pushBack(new nbt::LongTag(13));
    listTag.pushBack(new nbt::LongTag(14));
    listTag.pushBack(new nbt::LongTag(15));

    std::vector<unsigned char> data = listTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = listTag.getData(true);
    EXPECT_EQ(45, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 18, testData.end()));
}

TEST(ListTag, isEmpty)
{
    nbt::ListTag listTag(nbt::TagType::Byte);
    EXPECT_TRUE(listTag.isEmpty());
    
    // Test adding a new Item
    EXPECT_TRUE(listTag.pushBack(new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());
    EXPECT_FALSE(listTag.isEmpty());
}

TEST(ListTag, clear)
{
    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);

    nbt::ListTag list;
    ASSERT_TRUE(list.pushBack(a));
    ASSERT_TRUE(list.pushBack(b));
    ASSERT_EQ(2, list.size());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(ListTag, erase)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    // Add 3 Items
    listTag.pushBack(new nbt::ByteTag("A", 1));
    listTag.pushBack(new nbt::ByteTag("B", 2));
    listTag.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, listTag.size());

    // Test index too high
    EXPECT_FALSE(listTag.erase(3));
    EXPECT_FALSE(listTag.erase(900));

    // Erase middle item
    EXPECT_TRUE(listTag.erase(1));
    EXPECT_EQ(2, listTag.size());

    // Check that item 1 and 3 remain
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    nbt::ByteTag *bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    bt = dynamic_cast<nbt::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());

    // Erase last item
    EXPECT_TRUE(listTag.erase(1));
    EXPECT_EQ(1, listTag.size());

    // Check remaining item
    data = listTag.getValue();
    bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());

    // Erase last item
    EXPECT_TRUE(listTag.erase(0));
    EXPECT_EQ(0, listTag.size());
    EXPECT_TRUE(listTag.isEmpty());
}

TEST(ListTag, insert)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    // Test insert nullptr
    EXPECT_FALSE(listTag.insert(0, nullptr));

    // Test insert invalid type
    EXPECT_FALSE(listTag.insert(0, new nbt::EndTag()));

    // Test adding a new Item at invalid index
    EXPECT_FALSE(listTag.insert(1, new nbt::ByteTag("Value", 1)));

    // Add correct item
    EXPECT_TRUE(listTag.insert(0, new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());

    // Add second item at end
    EXPECT_TRUE(listTag.insert(1, new nbt::ByteTag("Value", 3)));
    EXPECT_EQ(2, listTag.size());

    // Add third item in between
    EXPECT_TRUE(listTag.insert(1, new nbt::ByteTag("Value", 2)));
    EXPECT_EQ(3, listTag.size());

    // Test correct order
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    nbt::ByteTag *bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    bt = dynamic_cast<nbt::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(2, bt->getValue());
    bt = dynamic_cast<nbt::ByteTag*>(data[2]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());

}

TEST(ListTag, pushBack)
{
    nbt::ListTag listTag(nbt::TagType::Byte);
    // Test adding a new Item
    EXPECT_TRUE(listTag.pushBack(new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());

    // Test adding an invalid item.
    EXPECT_FALSE(listTag.pushBack(new nbt::EndTag()));
    EXPECT_EQ(1, listTag.size());

    // Test adding a nullptr
    EXPECT_FALSE(listTag.pushBack(nullptr));
    EXPECT_EQ(1, listTag.size());
}

TEST(ListTag, size)
{
    nbt::ListTag listTag(nbt::TagType::Byte);
    // Test adding a new Item
    ASSERT_TRUE(listTag.pushBack(new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());

    // Test adding a second item
    ASSERT_TRUE(listTag.pushBack(new nbt::ByteTag("Value", 2)));
    EXPECT_EQ(2, listTag.size());

    // Test adding a third item
    ASSERT_TRUE(listTag.pushBack(new nbt::ByteTag("Value", 3)));
    EXPECT_EQ(3, listTag.size());

    // Test erasing an item
    ASSERT_TRUE(listTag.erase(0));
    EXPECT_EQ(2, listTag.size());

    // clear
    listTag.clear();
    EXPECT_EQ(0, listTag.size());
}

TEST(ListTag, at)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test at
    nbt::ByteTag *v1 = dynamic_cast<nbt::ByteTag*>(listTag.at(0));
    nbt::ByteTag *v2 = dynamic_cast<nbt::ByteTag*>(listTag.at(1));
    nbt::ByteTag *v3 = dynamic_cast<nbt::ByteTag*>(listTag.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(ListTag, at_const)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    const nbt::ListTag listTag2(listTag);

    // Test at
    const nbt::ByteTag *v1 = dynamic_cast<const nbt::ByteTag*>(listTag2.at(0));
    const nbt::ByteTag *v2 = dynamic_cast<const nbt::ByteTag*>(listTag2.at(1));
    const nbt::ByteTag *v3 = dynamic_cast<const nbt::ByteTag*>(listTag2.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(ListTag, takeAt)
{
    nbt::ListTag listTag(nbt::TagType::Float);

    nbt::FloatTag *a = new nbt::FloatTag("A", 1.4f);
    nbt::FloatTag *b = new nbt::FloatTag("B", 2000.6f);
    nbt::FloatTag *c = new nbt::FloatTag("C", 3.f);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test
    nbt::AbstractTag *bTest = listTag.takeAt(1);
    EXPECT_EQ(2, listTag.size());
    EXPECT_EQ(b, bTest);
    nbt::AbstractTag *aTest = listTag.takeAt(0);
    EXPECT_EQ(1, listTag.size());
    EXPECT_EQ(a, aTest);
    nbt::AbstractTag *cTest = listTag.takeAt(0);
    EXPECT_EQ(0, listTag.size());
    EXPECT_EQ(c, cTest);
}

TEST(ListTag, getValue)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test items
    std::vector<nbt::AbstractTag*> data = listTag.getValue();
    nbt::ByteTag *bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    EXPECT_STREQ("A", bt->getName().c_str());
    bt = dynamic_cast<nbt::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(2, bt->getValue());
    EXPECT_STREQ("B", bt->getName().c_str());
    bt = dynamic_cast<nbt::ByteTag*>(data[2]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());
    EXPECT_STREQ("C", bt->getName().c_str());
}

TEST(ListTag, getValueCopy)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    std::vector<nbt::AbstractTag*> data = listTag.getValueCopy();
    nbt::ByteTag *bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    EXPECT_STREQ("A", bt->getName().c_str());
    bt = dynamic_cast<nbt::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(2, bt->getValue());
    EXPECT_STREQ("B", bt->getName().c_str());
    bt = dynamic_cast<nbt::ByteTag*>(data[2]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());
    EXPECT_STREQ("C", bt->getName().c_str());
}

TEST(ListTag, setValue)
{
    nbt::ListTag listTag(nbt::TagType::Byte);

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    std::vector<nbt::AbstractTag*> data({a, b, c});

    EXPECT_EQ(0, listTag.size());
    listTag.setValue(data);
    EXPECT_EQ(3, listTag.size());

    std::vector<nbt::AbstractTag*> data2 = listTag.getValue();

    EXPECT_TRUE(*data2[0] == *data[0]);
    EXPECT_TRUE(*data2[1] == *data[1]);
    EXPECT_TRUE(*data2[2] == *data[2]);
}

TEST(ListTag, tag_cast)
{
    nbt::AbstractTag *testTag = new nbt::ListTag("A", nbt::TagType::Byte);

    nbt::ListTag *otherTag = tag_cast<nbt::ListTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    nbt::IntTag *nullTag = tag_cast<nbt::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);
}