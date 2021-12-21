#include "nbt/tags/compound_tag.hpp"
#include "nbt/tags/end_tag.hpp"
#include "nbt/tags/byte_tag.hpp"
#include "nbt/tags/int_tag.hpp"
#include "nbt/tags/float_tag.hpp"
#include "nbt/tags/double_tag.hpp"
#include "nbt/tags/string_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(CompoundTag, Constructor)
{
    nbt::CompoundTag compoundTag;
    EXPECT_STREQ("", compoundTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Compound, compoundTag.getType());
    std::vector<nbt::AbstractTag*> data = compoundTag.getValue();
    EXPECT_EQ(0, data.size());
    EXPECT_TRUE(compoundTag.isEmpty());
}

TEST(CompoundTag, Constructor_2)
{
    nbt::CompoundTag compoundTag("Tagname");
    EXPECT_STREQ("Tagname", compoundTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Compound, compoundTag.getType());
    std::vector<nbt::AbstractTag*> data = compoundTag.getValue();
    EXPECT_EQ(0, data.size());
    EXPECT_TRUE(compoundTag.isEmpty());
}

TEST(CompoundTag, CopyConstructor)
{
    std::string name = "CopyConstructor";

    // Init A
    nbt::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new nbt::IntTag("A", 1));
    compoundTagA.pushBack(new nbt::FloatTag("B", 2.5f));
    compoundTagA.pushBack(new nbt::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Copy Constructor
    nbt::CompoundTag compoundTagB(compoundTagA);
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagB.getName().c_str(), compoundTagA.getName().c_str());
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(compoundTagB.size(), compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), nbt::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), nbt::TagType::Float);
    EXPECT_EQ(compoundTagB.at(2)->getType(), nbt::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, MoveConstructor)
{
    std::string name = "MoveConstructor";

    // Init A
    nbt::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new nbt::IntTag("A", 1));
    compoundTagA.pushBack(new nbt::FloatTag("B", 2.5f));
    compoundTagA.pushBack(new nbt::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Copy Constructor
    nbt::CompoundTag compoundTagB(std::move(compoundTagA));
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagA.getName().c_str(), "");
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(0, compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), nbt::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), nbt::TagType::Float);
    EXPECT_EQ(compoundTagB.at(2)->getType(), nbt::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, CopyAssignment)
{
    std::string name = "CopyAssignment";

    // Init A
    nbt::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new nbt::IntTag("A", 1));
    compoundTagA.pushBack(new nbt::DoubleTag("B", 2.5));
    compoundTagA.pushBack(new nbt::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Copy Assignment
    nbt::CompoundTag compoundTagB = compoundTagA;
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagB.getName().c_str(), compoundTagA.getName().c_str());
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(compoundTagB.size(), compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), nbt::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), nbt::TagType::Double);
    EXPECT_EQ(compoundTagB.at(2)->getType(), nbt::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, MoveAssignment)
{
    std::string name = "MoveAssignment";

    // Init A
    nbt::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new nbt::IntTag("A", 1));
    compoundTagA.pushBack(new nbt::FloatTag("B", 2.5f));
    compoundTagA.pushBack(new nbt::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Move Assignment
    nbt::CompoundTag compoundTagB = std::move(compoundTagA);
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagA.getName().c_str(), "");
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(0, compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), nbt::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), nbt::TagType::Float);
    EXPECT_EQ(compoundTagB.at(2)->getType(), nbt::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, clone)
{
    // Init A
    nbt::CompoundTag compoundTagA;

    compoundTagA.pushBack(new nbt::IntTag("A", 1));
    compoundTagA.pushBack(new nbt::IntTag("B", 2));
    compoundTagA.pushBack(new nbt::IntTag("C", 3));
    ASSERT_EQ(3, compoundTagA.size());

    nbt::CompoundTag *clone = (nbt::CompoundTag *)compoundTagA.clone();

    EXPECT_TRUE(compoundTagA == *clone);
}

TEST(CompoundTag, Equal)
{
    // Init A
    nbt::CompoundTag compoundTagA;

    compoundTagA.pushBack(new nbt::ByteTag("A", 1));
    compoundTagA.pushBack(new nbt::ByteTag("B", 2));
    compoundTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagA.size());

    // Init B
    nbt::CompoundTag compoundTagB;

    compoundTagB.pushBack(new nbt::ByteTag("A", 1));
    compoundTagB.pushBack(new nbt::ByteTag("B", 2));
    compoundTagB.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagB.size());

    EXPECT_TRUE(compoundTagA == compoundTagA);
    EXPECT_TRUE(compoundTagA == compoundTagB);

    // Change B
    compoundTagB.erase(2);
    EXPECT_FALSE(compoundTagA == compoundTagB);

    // Make equal again
    compoundTagA.erase(2);
    EXPECT_TRUE(compoundTagA == compoundTagB);

    compoundTagA.setName("bla");
    EXPECT_FALSE(compoundTagA == compoundTagB);
}

TEST(CompoundTag, NotEqual)
{
    // Init List A
    nbt::CompoundTag compoundTagA;

    compoundTagA.pushBack(new nbt::ByteTag("A", 1));
    compoundTagA.pushBack(new nbt::ByteTag("B", 2));
    compoundTagA.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagA.size());

    // Init List B
    nbt::CompoundTag compoundTagB;

    compoundTagB.pushBack(new nbt::ByteTag("A", 1));
    compoundTagB.pushBack(new nbt::ByteTag("B", 2));
    compoundTagB.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagB.size());

    EXPECT_FALSE(compoundTagA != compoundTagA);
    EXPECT_FALSE(compoundTagA != compoundTagB);

    // Change B
    compoundTagB.erase(2);
    EXPECT_TRUE(compoundTagA != compoundTagB);

    // Make equal again
    compoundTagA.erase(2);
    EXPECT_FALSE(compoundTagA != compoundTagB);

    // Change name
    compoundTagA.setName("bla");
    EXPECT_TRUE(compoundTagA != compoundTagB);
}

TEST(CompoundTag, getType)
{
    nbt::CompoundTag compoundTag;
    EXPECT_EQ(nbt::TagType::Compound, compoundTag.getType());
}

TEST(CompoundTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x0A, 0x00, 0x03, 0x65, 0x67, 0x67, 0x08, 0x00,
        0x04, 0x6E, 0x61, 0x6D, 0x65, 0x00, 0x07, 0x45,
        0x67, 0x67, 0x62, 0x65, 0x72, 0x74, 0x05, 0x00,
        0x05, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3F, 0x00,
        0x00, 0x00, 0x00
    };

    nbt::CompoundTag compoundTag("egg");
    compoundTag.pushBack(new nbt::StringTag("name", "Eggbert"));
    compoundTag.pushBack(new nbt::FloatTag("value", 0.5));

    std::vector<unsigned char> data = compoundTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = compoundTag.getData(true);
    EXPECT_EQ(29, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 6, testData.end()));
}

TEST(CompoundTag, isEmpty)
{
    nbt::CompoundTag compoundTag;
    EXPECT_TRUE(compoundTag.isEmpty());

    // Test adding a new Item
    EXPECT_TRUE(compoundTag.pushBack(new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());
    EXPECT_FALSE(compoundTag.isEmpty());
}

TEST(CompoundTag, clear)
{
    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::IntTag  *b = new nbt::IntTag("B", 2);

    nbt::CompoundTag list;
    ASSERT_TRUE(list.pushBack(a));
    ASSERT_TRUE(list.pushBack(b));
    ASSERT_EQ(2, list.size());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(CompoundTag, erase)
{
    nbt::CompoundTag compoundTag;

    // Add 3 Items
    compoundTag.pushBack(new nbt::ByteTag("A", 1));
    compoundTag.pushBack(new nbt::ByteTag("B", 2));
    compoundTag.pushBack(new nbt::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTag.size());

    // Test index too high
    EXPECT_FALSE(compoundTag.erase(3));
    EXPECT_FALSE(compoundTag.erase(900));

    // Erase middle item
    EXPECT_TRUE(compoundTag.erase(1));
    EXPECT_EQ(2, compoundTag.size());

    // Check that item 1 and 3 remain
    std::vector<nbt::AbstractTag*> data = compoundTag.getValue();
    nbt::ByteTag *bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    bt = dynamic_cast<nbt::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());

    // Erase last item
    EXPECT_TRUE(compoundTag.erase(1));
    EXPECT_EQ(1, compoundTag.size());

    // Check remaining item
    data = compoundTag.getValue();
    bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());

    // Erase last item
    EXPECT_TRUE(compoundTag.erase(0));
    EXPECT_EQ(0, compoundTag.size());
    EXPECT_TRUE(compoundTag.isEmpty());
}

TEST(CompoundTag, insert)
{
    nbt::CompoundTag compoundTag;

    // Test insert nullptr
    EXPECT_FALSE(compoundTag.insert(0, nullptr));

    // Test adding a new Item at invalid index
    EXPECT_FALSE(compoundTag.insert(1, new nbt::ByteTag("Value", 1)));

    // Add correct item
    EXPECT_TRUE(compoundTag.insert(0, new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());

    // Add second item at end
    EXPECT_TRUE(compoundTag.insert(1, new nbt::ByteTag("Value", 3)));
    EXPECT_EQ(2, compoundTag.size());

    // Add third item in between
    EXPECT_TRUE(compoundTag.insert(1, new nbt::ByteTag("Value", 2)));
    EXPECT_EQ(3, compoundTag.size());

    // Test correct order
    std::vector<nbt::AbstractTag*> data = compoundTag.getValue();
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

TEST(CompoundTag, pushBack)
{
    nbt::CompoundTag compoundTag;
    // Test adding a new Item
    EXPECT_TRUE(compoundTag.pushBack(new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());

    // Test adding another tag
    EXPECT_TRUE(compoundTag.pushBack(new nbt::StringTag("A", "B")));
    EXPECT_EQ(2, compoundTag.size());

    // Test adding a nullptr
    EXPECT_FALSE(compoundTag.pushBack(nullptr));
    EXPECT_EQ(2, compoundTag.size());
}

TEST(CompoundTag, size)
{
    nbt::CompoundTag compoundTag;
    // Test adding a new Item
    ASSERT_TRUE(compoundTag.pushBack(new nbt::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());

    // Test adding a second item
    ASSERT_TRUE(compoundTag.pushBack(new nbt::IntTag("Value", 2)));
    EXPECT_EQ(2, compoundTag.size());

    // Test adding a third item
    ASSERT_TRUE(compoundTag.pushBack(new nbt::StringTag("Value", "V")));
    EXPECT_EQ(3, compoundTag.size());

    // Test erasing an item
    ASSERT_TRUE(compoundTag.erase(0));
    EXPECT_EQ(2, compoundTag.size());

    // clear
    compoundTag.clear();
    EXPECT_EQ(0, compoundTag.size());
}

TEST(CompoundTag, at)
{
    nbt::CompoundTag compoundTag;

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test at
    nbt::ByteTag *v1 = dynamic_cast<nbt::ByteTag*>(compoundTag.at(0));
    nbt::ByteTag *v2 = dynamic_cast<nbt::ByteTag*>(compoundTag.at(1));
    nbt::ByteTag *v3 = dynamic_cast<nbt::ByteTag*>(compoundTag.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(CompoundTag, at_const)
{
    nbt::CompoundTag compoundTag;

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    const nbt::CompoundTag compoundTag2(compoundTag);

    // Test at
    const nbt::ByteTag *v1 = dynamic_cast<const nbt::ByteTag*>(compoundTag2.at(0));
    const nbt::ByteTag *v2 = dynamic_cast<const nbt::ByteTag*>(compoundTag2.at(1));
    const nbt::ByteTag *v3 = dynamic_cast<const nbt::ByteTag*>(compoundTag2.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(CompoundTag, takeAt)
{
    nbt::CompoundTag compoundTag;

    nbt::ByteTag *a     = new nbt::ByteTag("A", 1);
    nbt::IntTag *b      = new nbt::IntTag("B", 2000);
    nbt::FloatTag *c    = new nbt::FloatTag("C", 3.f);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test
    nbt::AbstractTag *bTest = compoundTag.takeAt(1);
    EXPECT_EQ(2, compoundTag.size());
    EXPECT_EQ(b, bTest);
    nbt::AbstractTag *aTest = compoundTag.takeAt(0);
    EXPECT_EQ(1, compoundTag.size());
    EXPECT_EQ(a, aTest);
    nbt::AbstractTag *cTest = compoundTag.takeAt(0);
    EXPECT_EQ(0, compoundTag.size());
    EXPECT_EQ(c, cTest);
}

TEST(CompoundTag, getValue)
{
    nbt::CompoundTag compoundTag;

    nbt::ByteTag    *a = new nbt::ByteTag("A", 1);
    nbt::IntTag     *b = new nbt::IntTag("B", 2);
    nbt::StringTag  *c = new nbt::StringTag("C", "B");

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test items
    std::vector<nbt::AbstractTag*> data = compoundTag.getValue();

    nbt::ByteTag *bt = dynamic_cast<nbt::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(nbt::TagType::Byte, bt->getType());
    EXPECT_EQ(1, bt->getValue());
    EXPECT_STREQ("A", bt->getName().c_str());

    nbt::IntTag *it = dynamic_cast<nbt::IntTag*>(data[1]);
    EXPECT_TRUE(it != nullptr);
    EXPECT_EQ(nbt::TagType::Int, it->getType());
    EXPECT_EQ(2, it->getValue());
    EXPECT_STREQ("B", it->getName().c_str());

    nbt::StringTag *st = dynamic_cast<nbt::StringTag*>(data[2]);
    EXPECT_TRUE(st != nullptr);
    EXPECT_EQ(nbt::TagType::String, st->getType());
    EXPECT_STREQ("B", st->getValue().c_str());
    EXPECT_STREQ("C", st->getName().c_str());
}

TEST(CompoundTag, getValueCopy)
{
    nbt::CompoundTag compoundTag;

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    std::vector<nbt::AbstractTag*> data = compoundTag.getValueCopy();
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

TEST(CompoundTag, setValue)
{
    nbt::CompoundTag compoundTag;

    nbt::ByteTag *a = new nbt::ByteTag("A", 1);
    nbt::ByteTag *b = new nbt::ByteTag("B", 2);
    nbt::ByteTag *c = new nbt::ByteTag("C", 3);

    std::vector<nbt::AbstractTag*> data({a, b, c});

    EXPECT_EQ(0, compoundTag.size());
    compoundTag.setValue(data);
    EXPECT_EQ(3, compoundTag.size());

    std::vector<nbt::AbstractTag*> data2 = compoundTag.getValue();

    EXPECT_TRUE(*data2[0] == *data[0]);
    EXPECT_TRUE(*data2[1] == *data[1]);
    EXPECT_TRUE(*data2[2] == *data[2]);
}