// AwesomeMC
#include <AwesomeMC/nbt/tags/list_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/byte_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/nbt/tags/float_tag.hpp>
#include <AwesomeMC/nbt/tags/double_tag.hpp>
#include <AwesomeMC/nbt/tags/long_tag.hpp>
#include <AwesomeMC/util/byte_swap.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ListTag, Constructor)
{
    amc::ListTag listTag;
    EXPECT_STREQ("", listTag.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_2)
{
    amc::ListTag listTag("Tagname");
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_3)
{
    amc::ListTag listTag("Tagname");
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_4)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    amc::ListTag listTag(amc::TagType::Byte, {a, b, c});
    EXPECT_STREQ("", listTag.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(3, data.size());

    amc::ByteTag *v1 = tag_cast<amc::ByteTag*>(listTag.at(0));
    amc::ByteTag *v2 = tag_cast<amc::ByteTag*>(listTag.at(1));
    amc::ByteTag *v3 = tag_cast<amc::ByteTag*>(listTag.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);

    // Test not matching list type
    amc::ByteTag *a2 = new amc::ByteTag("A", 1);
    amc::ByteTag *b2 = new amc::ByteTag("B", 2);
    amc::ByteTag *c2 = new amc::ByteTag("C", 3);
    amc::ListTag listTag2(amc::TagType::Float, {a2, b2, c2});
    EXPECT_STREQ("", listTag2.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag2.getType());
    EXPECT_EQ(amc::TagType::Float, listTag2.getListType());
    std::vector<amc::AbstractTag*> data2 = listTag2.getValue();
    EXPECT_EQ(0, data2.size());
    delete a2;
    delete b2;
    delete c2;

    // Test nullptr
    amc::ByteTag *a3 = new amc::ByteTag("A", 1);
    amc::ListTag listTag3(amc::TagType::Byte, {a3, nullptr});
    EXPECT_STREQ("", listTag3.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag3.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag3.getListType());
    std::vector<amc::AbstractTag*> data3 = listTag3.getValue();
    EXPECT_EQ(1, data3.size());
}

TEST(ListTag, Constructor_5)
{
    amc::ListTag listTag("Tagname", amc::TagType::Float);
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag.getType());
    EXPECT_EQ(amc::TagType::Float, listTag.getListType());
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ListTag, Constructor_6)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    amc::ListTag listTag("Tagname", amc::TagType::Byte, {a, b, c});
    EXPECT_STREQ("Tagname", listTag.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    EXPECT_EQ(3, data.size());

    amc::ByteTag *v1 = tag_cast<amc::ByteTag*>(listTag.at(0));
    amc::ByteTag *v2 = tag_cast<amc::ByteTag*>(listTag.at(1));
    amc::ByteTag *v3 = tag_cast<amc::ByteTag*>(listTag.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);

    // Test not matching list type
    amc::ByteTag *a2 = new amc::ByteTag("A", 1);
    amc::ByteTag *b2 = new amc::ByteTag("B", 2);
    amc::ByteTag *c2 = new amc::ByteTag("C", 3);
    amc::ListTag listTag2("Tagname", amc::TagType::Float, {a2, b2, c2});
    EXPECT_STREQ("Tagname", listTag2.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag2.getType());
    EXPECT_EQ(amc::TagType::Float, listTag2.getListType());
    std::vector<amc::AbstractTag*> data2 = listTag2.getValue();
    EXPECT_EQ(0, data2.size());
    delete a2;
    delete b2;
    delete c2;

    // Test nullptr
    amc::ByteTag *a3 = new amc::ByteTag("A", 1);
    amc::ListTag listTag3("Tagname", amc::TagType::Byte, {a3, nullptr});
    EXPECT_STREQ("Tagname", listTag3.getName().c_str());
    EXPECT_EQ(amc::TagType::List, listTag3.getType());
    EXPECT_EQ(amc::TagType::Byte, listTag3.getListType());
    std::vector<amc::AbstractTag*> data3 = listTag3.getValue();
    EXPECT_EQ(1, data3.size());
}

TEST(ListTag, CopyConstructor)
{
    std::string name = "CopyConstructor";

    // Init A
    amc::ListTag listTagA(name, amc::TagType::Byte);
    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Test Copy Assignment
    amc::ListTag listTagB(listTagA);
    EXPECT_STREQ(listTagB.getName().c_str(), listTagA.getName().c_str());
    EXPECT_EQ(3, listTagB.size());
}

TEST(ListTag, MoveConstructor)
{
    std::string name = "MoveConstructor";

    // Init A
    amc::ListTag listTagA(name, amc::TagType::Byte);
    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Test Copy Assignment
    amc::ListTag listTagB(std::move(listTagA));
    EXPECT_STREQ(listTagB.getName().c_str(), name.c_str());
    EXPECT_EQ(3, listTagB.size());
}

TEST(ListTag, CopyAssignment)
{
    std::string name = "CopyAssignment";

    // Init A
    amc::ListTag listTagA(name, amc::TagType::Byte);
    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Init B
    amc::ListTag listTagB;
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
    amc::ListTag listTagA(name, amc::TagType::Byte);
    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_STREQ(listTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, listTagA.size());

    // Init B
    amc::ListTag listTagB;
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
    amc::ListTag listTagA(amc::TagType::Byte);

    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, listTagA.size());

    amc::ListTag *listClone = tag_cast<amc::ListTag*>(listTagA.clone());

    EXPECT_TRUE(listTagA == *listClone);
    delete listClone;
}

TEST(ListTag, Equal)
{
    // Init List A
    amc::ListTag listTagA(amc::TagType::Byte);

    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, listTagA.size());

    // Init List B
    amc::ListTag listTagB(amc::TagType::Byte);

    listTagB.pushBack(new amc::ByteTag("A", 1));
    listTagB.pushBack(new amc::ByteTag("B", 2));
    listTagB.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, listTagB.size());

    // Init List C
    amc::ListTag listTagC(amc::TagType::Int);

    listTagC.pushBack(new amc::IntTag("A", 1));
    listTagC.pushBack(new amc::IntTag("B", 2));
    listTagC.pushBack(new amc::IntTag("C", 3));
    ASSERT_EQ(3, listTagC.size());

    EXPECT_TRUE(listTagA == listTagA);
    EXPECT_TRUE(listTagA == listTagB);
    EXPECT_FALSE(listTagA == listTagC);

    // Change B
    listTagB.eraseAt(2);
    EXPECT_FALSE(listTagA == listTagB);

    // Make equal again
    listTagA.eraseAt(2);
    EXPECT_TRUE(listTagA == listTagB);

    listTagA.setName("bla");
    EXPECT_FALSE(listTagA == listTagB);
}

TEST(ListTag, NotEqual)
{
    // Init List A
    amc::ListTag listTagA(amc::TagType::Byte);

    listTagA.pushBack(new amc::ByteTag("A", 1));
    listTagA.pushBack(new amc::ByteTag("B", 2));
    listTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, listTagA.size());

    // Init List B
    amc::ListTag listTagB(amc::TagType::Byte);

    listTagB.pushBack(new amc::ByteTag("A", 1));
    listTagB.pushBack(new amc::ByteTag("B", 2));
    listTagB.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, listTagB.size());

    // Init List C
    amc::ListTag listTagC(amc::TagType::Int);

    listTagC.pushBack(new amc::IntTag("A", 1));
    listTagC.pushBack(new amc::IntTag("B", 2));
    listTagC.pushBack(new amc::IntTag("C", 3));
    ASSERT_EQ(3, listTagC.size());

    EXPECT_FALSE(listTagA != listTagA);
    EXPECT_FALSE(listTagA != listTagB);
    EXPECT_TRUE(listTagA != listTagC);

    // Change B
    listTagB.eraseAt(2);
    EXPECT_TRUE(listTagA != listTagB);

    // Make equal again
    listTagA.eraseAt(2);
    EXPECT_FALSE(listTagA != listTagB);

    // Change name
    listTagA.setName("bla");
    EXPECT_TRUE(listTagA != listTagB);
}

TEST(ListTag, getType)
{
    amc::ListTag listTag;
    EXPECT_EQ(amc::TagType::List, listTag.getType());
}

TEST(ListTag, getListType)
{
    amc::ListTag listTag;
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());

    amc::ListTag listTag2(amc::TagType::Float);
    EXPECT_EQ(amc::TagType::Float, listTag2.getListType());
}

TEST(ListTag, setListType)
{
    amc::ListTag listTag;
    EXPECT_EQ(amc::TagType::Byte, listTag.getListType());

    EXPECT_TRUE(listTag.setListType(amc::TagType::Double));
    EXPECT_EQ(amc::TagType::Double, listTag.getListType());

    listTag.pushBack(new amc::DoubleTag("Test", 3.4));
    EXPECT_FALSE(listTag.setListType(amc::TagType::Float));
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

    amc::ListTag listTag("listTest (long)", amc::TagType::Long);
    listTag.pushBack(new amc::LongTag(11));
    listTag.pushBack(new amc::LongTag(12));
    listTag.pushBack(new amc::LongTag(13));
    listTag.pushBack(new amc::LongTag(14));
    listTag.pushBack(new amc::LongTag(15));

    std::vector<unsigned char> data = listTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = listTag.getData(true);
    EXPECT_EQ(45, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 18, testData.end()));
}

TEST(ListTag, begin)
{
    amc::ListTag listTag(amc::TagType::Byte, {
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    amc::ListTag::iterator it = listTag.begin();
    amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
    ASSERT_TRUE(b != nullptr);
    EXPECT_EQ(*b, amc::ByteTag("A", 1));
}

TEST(ListTag, end)
{
    amc::ListTag listTag(amc::TagType::Byte, {
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    int8_t idx = 0;
    std::string strArray[3] = {"A", "B", "C"};
    for(amc::ListTag::iterator it = listTag.begin(); it != listTag.end(); ++it) {
        amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
        ASSERT_TRUE(b != nullptr);
        EXPECT_EQ(*b, amc::ByteTag(strArray[idx], idx + 1));
        idx++;
    }
}

TEST(ListTag, begin_const)
{
    const amc::ListTag listTag(amc::TagType::Byte, {
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    amc::ListTag::const_iterator it = listTag.begin();
    amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
    ASSERT_TRUE(b != nullptr);
    EXPECT_TRUE(*b == amc::ByteTag("A", 1));
}

TEST(ListTag, end_const)
{
    const amc::ListTag listTag(amc::TagType::Byte, {
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    int8_t idx = 0;
    std::string strArray[3] = {"A", "B", "C"};
    for(amc::ListTag::const_iterator it = listTag.begin(); it != listTag.end(); ++it) {
        amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
        ASSERT_TRUE(b != nullptr);
        EXPECT_EQ(*b, amc::ByteTag(strArray[idx], idx + 1));
        idx++;
    }
}

TEST(ListTag, isEmpty)
{
    amc::ListTag listTag(amc::TagType::Byte);
    EXPECT_TRUE(listTag.isEmpty());
    
    // Test adding a new Item
    EXPECT_TRUE(listTag.pushBack(new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());
    EXPECT_FALSE(listTag.isEmpty());
}

TEST(ListTag, clear)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);

    amc::ListTag list;
    ASSERT_TRUE(list.pushBack(a));
    ASSERT_TRUE(list.pushBack(b));
    ASSERT_EQ(2, list.size());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(ListTag, erase)
{
    amc::ListTag listTag(amc::TagType::Byte);

    // Add 3 Items
    listTag.pushBack(new amc::ByteTag("A", 1));
    listTag.pushBack(new amc::ByteTag("B", 2));
    listTag.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, listTag.size());

    // Test index too high
    EXPECT_FALSE(listTag.eraseAt(3));
    EXPECT_FALSE(listTag.eraseAt(900));

    // Erase middle item
    EXPECT_TRUE(listTag.eraseAt(1));
    EXPECT_EQ(2, listTag.size());

    // Check that item 1 and 3 remain
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    amc::ByteTag *bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    bt = tag_cast<amc::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());

    // Erase last item
    EXPECT_TRUE(listTag.eraseAt(1));
    EXPECT_EQ(1, listTag.size());

    // Check remaining item
    data = listTag.getValue();
    bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());

    // Erase last item
    EXPECT_TRUE(listTag.eraseAt(0));
    EXPECT_EQ(0, listTag.size());
    EXPECT_TRUE(listTag.isEmpty());
}

TEST(ListTag, eraseByValue)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);
    amc::ByteTag *d = new amc::ByteTag("C", 3);

    amc::ListTag listTag(amc::TagType::Byte, {a, b, c});
    ASSERT_EQ(3, listTag.size());

    EXPECT_FALSE(listTag.erase(d));
    ASSERT_EQ(3, listTag.size());

    EXPECT_TRUE(listTag.erase(b));
    ASSERT_EQ(2, listTag.size());

    EXPECT_TRUE(listTag.erase(c));
    ASSERT_EQ(1, listTag.size());

    EXPECT_TRUE(listTag.erase(a));
    ASSERT_EQ(0, listTag.size());

    delete d;
}

TEST(ListTag, insert)
{
    amc::ListTag listTag(amc::TagType::Byte);

    // Test insert nullptr
    EXPECT_FALSE(listTag.insert(0, nullptr));

    // Test insert invalid type
    amc::AbstractTag *invalidTag = new amc::EndTag();
    EXPECT_FALSE(listTag.insert(0, invalidTag));
    delete invalidTag;

    // Test adding a new Item at invalid index
    amc::AbstractTag *invalidTag2 = new amc::ByteTag("Value", 1);
    EXPECT_FALSE(listTag.insert(1, invalidTag2));
    delete invalidTag2;

    // Add correct item
    EXPECT_TRUE(listTag.insert(0, new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());

    // Add second item at end
    EXPECT_TRUE(listTag.insert(1, new amc::ByteTag("Value", 3)));
    EXPECT_EQ(2, listTag.size());

    // Add third item in between
    EXPECT_TRUE(listTag.insert(1, new amc::ByteTag("Value", 2)));
    EXPECT_EQ(3, listTag.size());

    // Test correct order
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    amc::ByteTag *bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    bt = tag_cast<amc::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(2, bt->getValue());
    bt = tag_cast<amc::ByteTag*>(data[2]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());

}

TEST(ListTag, pushBack)
{
    amc::ListTag listTag(amc::TagType::Byte);
    // Test adding a new Item
    EXPECT_TRUE(listTag.pushBack(new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());

    // Test adding an invalid item.
    amc::AbstractTag *invalidTag = new amc::EndTag();
    EXPECT_FALSE(listTag.pushBack(invalidTag));
    EXPECT_EQ(1, listTag.size());
    delete invalidTag;

    // Test adding a nullptr
    EXPECT_FALSE(listTag.pushBack(nullptr));
    EXPECT_EQ(1, listTag.size());
}

TEST(ListTag, size)
{
    amc::ListTag listTag(amc::TagType::Byte);
    // Test adding a new Item
    ASSERT_TRUE(listTag.pushBack(new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, listTag.size());

    // Test adding a second item
    ASSERT_TRUE(listTag.pushBack(new amc::ByteTag("Value", 2)));
    EXPECT_EQ(2, listTag.size());

    // Test adding a third item
    ASSERT_TRUE(listTag.pushBack(new amc::ByteTag("Value", 3)));
    EXPECT_EQ(3, listTag.size());

    // Test erasing an item
    ASSERT_TRUE(listTag.eraseAt(0));
    EXPECT_EQ(2, listTag.size());

    // clear
    listTag.clear();
    EXPECT_EQ(0, listTag.size());
}

TEST(ListTag, at)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test at
    amc::ByteTag *v1 = tag_cast<amc::ByteTag*>(listTag.at(0));
    amc::ByteTag *v2 = tag_cast<amc::ByteTag*>(listTag.at(1));
    amc::ByteTag *v3 = tag_cast<amc::ByteTag*>(listTag.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);

    // Test exception
    EXPECT_THROW(listTag.at(3), std::out_of_range);
}

TEST(ListTag, at_const)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    const amc::ListTag listTag2(listTag);

    // Test at
    const amc::ByteTag *v1 = tag_cast<const amc::ByteTag*>(listTag2.at(0));
    const amc::ByteTag *v2 = tag_cast<const amc::ByteTag*>(listTag2.at(1));
    const amc::ByteTag *v3 = tag_cast<const amc::ByteTag*>(listTag2.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);

    // Test exception
    EXPECT_THROW(listTag2.at(3), std::out_of_range);
}

TEST(ListTag, takeAt)
{
    amc::ListTag listTag(amc::TagType::Float);

    amc::FloatTag *a = new amc::FloatTag("A", 1.4f);
    amc::FloatTag *b = new amc::FloatTag("B", 2000.6f);
    amc::FloatTag *c = new amc::FloatTag("C", 3.f);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test
    amc::AbstractTag *bTest = listTag.takeAt(1);
    EXPECT_EQ(2, listTag.size());
    EXPECT_EQ(b, bTest);
    amc::AbstractTag *aTest = listTag.takeAt(0);
    EXPECT_EQ(1, listTag.size());
    EXPECT_EQ(a, aTest);
    amc::AbstractTag *cTest = listTag.takeAt(0);
    EXPECT_EQ(0, listTag.size());
    EXPECT_EQ(c, cTest);

    delete aTest;
    delete bTest;
    delete cTest;
}

TEST(ListTag, take)
{
    amc::ListTag listTag(amc::TagType::Float);

    amc::FloatTag *a = new amc::FloatTag("A", 1.4f);
    amc::FloatTag *b = new amc::FloatTag("B", 2000.6f);
    amc::FloatTag *c = new amc::FloatTag("C", 3.f);
    amc::FloatTag *d = new amc::FloatTag("C", 3.f);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test
    amc::AbstractTag *invalidTag = listTag.take(d);
    EXPECT_TRUE(invalidTag == nullptr);
    
    amc::AbstractTag *aRet = listTag.take(a);
    EXPECT_EQ(aRet, a);
    EXPECT_EQ(2, listTag.size());

    delete a;
    delete d;
}

TEST(ListTag, subscript)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test at
    amc::ByteTag *v1 = tag_cast<amc::ByteTag*>(listTag[0]);
    amc::ByteTag *v2 = tag_cast<amc::ByteTag*>(listTag[1]);
    amc::ByteTag *v3 = tag_cast<amc::ByteTag*>(listTag[2]);

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(ListTag, subscript_const)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    const amc::ListTag listTag2(listTag);

    // Test at
    const amc::ByteTag *v1 = tag_cast<const amc::ByteTag*>(listTag2[0]);
    const amc::ByteTag *v2 = tag_cast<const amc::ByteTag*>(listTag2[1]);
    const amc::ByteTag *v3 = tag_cast<const amc::ByteTag*>(listTag2[2]);

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(ListTag, getValue)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    // Test items
    std::vector<amc::AbstractTag*> data = listTag.getValue();
    amc::ByteTag *bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    EXPECT_STREQ("A", bt->getName().c_str());
    bt = tag_cast<amc::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(2, bt->getValue());
    EXPECT_STREQ("B", bt->getName().c_str());
    bt = tag_cast<amc::ByteTag*>(data[2]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());
    EXPECT_STREQ("C", bt->getName().c_str());
}

TEST(ListTag, getValueCopy)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    listTag.pushBack(a);
    listTag.pushBack(b);
    listTag.pushBack(c);
    ASSERT_EQ(3, listTag.size());

    std::vector<amc::AbstractTag*> data = listTag.getValueCopy();
    amc::ByteTag *bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    EXPECT_STREQ("A", bt->getName().c_str());
    bt = tag_cast<amc::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(2, bt->getValue());
    EXPECT_STREQ("B", bt->getName().c_str());
    bt = tag_cast<amc::ByteTag*>(data[2]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());
    EXPECT_STREQ("C", bt->getName().c_str());

    delete data[0];
    delete data[1];
    delete data[2];
}

TEST(ListTag, setValue)
{
    amc::ListTag listTag(amc::TagType::Byte);

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    std::vector<amc::AbstractTag*> data({a, b, c});

    EXPECT_EQ(0, listTag.size());
    listTag.setValue(data);
    EXPECT_EQ(3, listTag.size());

    std::vector<amc::AbstractTag*> data2 = listTag.getValue();

    EXPECT_TRUE(*data2[0] == *data[0]);
    EXPECT_TRUE(*data2[1] == *data[1]);
    EXPECT_TRUE(*data2[2] == *data[2]);

    delete a;
    delete b;
    delete c;
}

TEST(ListTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::ListTag("A", amc::TagType::Byte);

    amc::ListTag *otherTag = tag_cast<amc::ListTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}