// AwesomeMC
#include <AwesomeMC/nbt/tags/compound_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/byte_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/nbt/tags/float_tag.hpp>
#include <AwesomeMC/nbt/tags/double_tag.hpp>
#include <AwesomeMC/nbt/tags/string_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(CompoundTag, Constructor)
{
    amc::CompoundTag compoundTag;
    EXPECT_STREQ("", compoundTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Compound, compoundTag.getType());
    std::vector<amc::AbstractTag*> data = compoundTag.getValue();
    EXPECT_EQ(0, data.size());
    EXPECT_TRUE(compoundTag.isEmpty());
}

TEST(CompoundTag, Constructor_2)
{
    amc::CompoundTag compoundTag("Tagname");
    EXPECT_STREQ("Tagname", compoundTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Compound, compoundTag.getType());
    std::vector<amc::AbstractTag*> data = compoundTag.getValue();
    EXPECT_EQ(0, data.size());
    EXPECT_TRUE(compoundTag.isEmpty());
}

TEST(CompoundTag, Constructor_3)
{
    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::ByteTag *a2    = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);

    amc::CompoundTag compoundTag({a, b, c});
    EXPECT_EQ(3, compoundTag.size());

    amc::AbstractTag *aTest = compoundTag.getChildByName("A");
    EXPECT_EQ(a, aTest);
    amc::AbstractTag *bTest = compoundTag.getChildByName("B");
    EXPECT_EQ(b, bTest);
    amc::AbstractTag *cTest = compoundTag.getChildByName("C");
    EXPECT_EQ(c, cTest);

    amc::CompoundTag compoundTag2({a2, nullptr});
    EXPECT_EQ(1, compoundTag2.size());
    amc::AbstractTag *aTest2 = compoundTag2.getChildByName("A");
    EXPECT_EQ(a2, aTest2);
}

TEST(CompoundTag, Constructor_4)
{
    std::string name    = "Constructor_4";
    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::ByteTag *a2    = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);

    amc::CompoundTag compoundTag(name, {a, b, c});
    EXPECT_EQ(3, compoundTag.size());
    EXPECT_STREQ(name.c_str(), compoundTag.getName().c_str());

    amc::AbstractTag *aTest = compoundTag.getChildByName("A");
    EXPECT_EQ(a, aTest);
    amc::AbstractTag *bTest = compoundTag.getChildByName("B");
    EXPECT_EQ(b, bTest);
    amc::AbstractTag *cTest = compoundTag.getChildByName("C");
    EXPECT_EQ(c, cTest);

    amc::CompoundTag compoundTag2(name, {a2, nullptr});
    EXPECT_EQ(1, compoundTag2.size());
    amc::AbstractTag *aTest2 = compoundTag2.getChildByName("A");
    EXPECT_EQ(a2, aTest2);
}

TEST(CompoundTag, CopyConstructor)
{
    std::string name = "CopyConstructor";

    // Init A
    amc::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new amc::IntTag("A", 1));
    compoundTagA.pushBack(new amc::FloatTag("B", 2.5f));
    compoundTagA.pushBack(new amc::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Copy Constructor
    amc::CompoundTag compoundTagB(compoundTagA);
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagB.getName().c_str(), compoundTagA.getName().c_str());
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(compoundTagB.size(), compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), amc::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), amc::TagType::Float);
    EXPECT_EQ(compoundTagB.at(2)->getType(), amc::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, MoveConstructor)
{
    std::string name = "MoveConstructor";

    // Init A
    amc::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new amc::IntTag("A", 1));
    compoundTagA.pushBack(new amc::FloatTag("B", 2.5f));
    compoundTagA.pushBack(new amc::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Copy Constructor
    amc::CompoundTag compoundTagB(std::move(compoundTagA));
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagA.getName().c_str(), "");
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(0, compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), amc::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), amc::TagType::Float);
    EXPECT_EQ(compoundTagB.at(2)->getType(), amc::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, CopyAssignment)
{
    std::string name = "CopyAssignment";

    // Init A
    amc::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new amc::IntTag("A", 1));
    compoundTagA.pushBack(new amc::DoubleTag("B", 2.5));
    compoundTagA.pushBack(new amc::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Copy Assignment
    amc::CompoundTag compoundTagB = compoundTagA;
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagB.getName().c_str(), compoundTagA.getName().c_str());
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(compoundTagB.size(), compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), amc::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), amc::TagType::Double);
    EXPECT_EQ(compoundTagB.at(2)->getType(), amc::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, MoveAssignment)
{
    std::string name = "MoveAssignment";

    // Init A
    amc::CompoundTag compoundTagA(name);
    compoundTagA.pushBack(new amc::IntTag("A", 1));
    compoundTagA.pushBack(new amc::FloatTag("B", 2.5f));
    compoundTagA.pushBack(new amc::StringTag("C", "Hallo"));
    ASSERT_STREQ(compoundTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(3, compoundTagA.size());

    // Test Move Assignment
    amc::CompoundTag compoundTagB = std::move(compoundTagA);
    EXPECT_STREQ(compoundTagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(compoundTagA.getName().c_str(), "");
    EXPECT_EQ(3, compoundTagB.size());
    EXPECT_EQ(0, compoundTagA.size());

    EXPECT_EQ(compoundTagB.at(0)->getType(), amc::TagType::Int);
    EXPECT_EQ(compoundTagB.at(1)->getType(), amc::TagType::Float);
    EXPECT_EQ(compoundTagB.at(2)->getType(), amc::TagType::String);
    EXPECT_STREQ(compoundTagB.at(0)->getName().c_str(), "A");
    EXPECT_STREQ(compoundTagB.at(1)->getName().c_str(), "B");
    EXPECT_STREQ(compoundTagB.at(2)->getName().c_str(), "C");
}

TEST(CompoundTag, clone)
{
    // Init A
    amc::CompoundTag compoundTagA;

    compoundTagA.pushBack(new amc::IntTag("A", 1));
    compoundTagA.pushBack(new amc::IntTag("B", 2));
    compoundTagA.pushBack(new amc::IntTag("C", 3));
    ASSERT_EQ(3, compoundTagA.size());

    amc::CompoundTag *clone = tag_cast<amc::CompoundTag*>(compoundTagA.clone());

    EXPECT_TRUE(compoundTagA == *clone);

    delete clone;
}

TEST(CompoundTag, Equal)
{
    // Init A
    amc::CompoundTag compoundTagA;

    compoundTagA.pushBack(new amc::ByteTag("A", 1));
    compoundTagA.pushBack(new amc::ByteTag("B", 2));
    compoundTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagA.size());

    // Init B
    amc::CompoundTag compoundTagB;

    compoundTagB.pushBack(new amc::ByteTag("A", 1));
    compoundTagB.pushBack(new amc::ByteTag("B", 2));
    compoundTagB.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagB.size());

    EXPECT_TRUE(compoundTagA == compoundTagA);
    EXPECT_TRUE(compoundTagA == compoundTagB);

    // Change B
    compoundTagB.eraseAt(2);
    EXPECT_FALSE(compoundTagA == compoundTagB);

    // Make equal again
    compoundTagA.eraseAt(2);
    EXPECT_TRUE(compoundTagA == compoundTagB);

    compoundTagA.setName("bla");
    EXPECT_FALSE(compoundTagA == compoundTagB);
}

TEST(CompoundTag, NotEqual)
{
    // Init List A
    amc::CompoundTag compoundTagA;

    compoundTagA.pushBack(new amc::ByteTag("A", 1));
    compoundTagA.pushBack(new amc::ByteTag("B", 2));
    compoundTagA.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagA.size());

    // Init List B
    amc::CompoundTag compoundTagB;

    compoundTagB.pushBack(new amc::ByteTag("A", 1));
    compoundTagB.pushBack(new amc::ByteTag("B", 2));
    compoundTagB.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTagB.size());

    EXPECT_FALSE(compoundTagA != compoundTagA);
    EXPECT_FALSE(compoundTagA != compoundTagB);

    // Change B
    compoundTagB.eraseAt(2);
    EXPECT_TRUE(compoundTagA != compoundTagB);

    // Make equal again
    compoundTagA.eraseAt(2);
    EXPECT_FALSE(compoundTagA != compoundTagB);

    // Change name
    compoundTagA.setName("bla");
    EXPECT_TRUE(compoundTagA != compoundTagB);
}

TEST(CompoundTag, getType)
{
    amc::CompoundTag compoundTag;
    EXPECT_EQ(amc::TagType::Compound, compoundTag.getType());
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

    amc::CompoundTag compoundTag("egg");
    compoundTag.pushBack(new amc::StringTag("name", "Eggbert"));
    compoundTag.pushBack(new amc::FloatTag("value", 0.5));

    std::vector<unsigned char> data = compoundTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = compoundTag.getData(true);
    EXPECT_EQ(29, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 6, testData.end()));
}

TEST(CompoundTag, begin)
{
    amc::CompoundTag compoundTag({
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    amc::CompoundTag::iterator it = compoundTag.begin();
    amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
    ASSERT_TRUE(b != nullptr);
    EXPECT_EQ(*b, amc::ByteTag("A", 1));
}

TEST(CompoundTag, end)
{
    amc::CompoundTag compoundTag({
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    int8_t idx = 0;
    std::string strArray[3] = {"A", "B", "C"};
    for(amc::CompoundTag::iterator it = compoundTag.begin(); it != compoundTag.end(); ++it) {
        amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
        ASSERT_TRUE(b != nullptr);
        EXPECT_EQ(*b, amc::ByteTag(strArray[idx], idx + 1));
        idx++;
    }
}

TEST(CompoundTag, begin_const)
{
    const amc::CompoundTag compoundTag({ 
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    amc::CompoundTag::const_iterator it = compoundTag.begin();
    amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
    ASSERT_TRUE(b != nullptr);
    EXPECT_TRUE(*b == amc::ByteTag("A", 1));
}

TEST(CompoundTag, end_const)
{
    const amc::CompoundTag compoundTag({
        new amc::ByteTag("A", 1),
        new amc::ByteTag("B", 2),
        new amc::ByteTag("C", 3)
    });

    int8_t idx = 0;
    std::string strArray[3] = {"A", "B", "C"};
    for(amc::CompoundTag::const_iterator it = compoundTag.begin(); it != compoundTag.end(); ++it) {
        amc::ByteTag *b = amc::tag_cast<amc::ByteTag*>(*it);
        ASSERT_TRUE(b != nullptr);
        EXPECT_EQ(*b, amc::ByteTag(strArray[idx], idx + 1));
        idx++;
    }
}

TEST(CompoundTag, isEmpty)
{
    amc::CompoundTag compoundTag;
    EXPECT_TRUE(compoundTag.isEmpty());

    // Test adding a new Item
    EXPECT_TRUE(compoundTag.pushBack(new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());
    EXPECT_FALSE(compoundTag.isEmpty());
}

TEST(CompoundTag, clear)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::IntTag  *b = new amc::IntTag("B", 2);

    amc::CompoundTag list;
    ASSERT_TRUE(list.pushBack(a));
    ASSERT_TRUE(list.pushBack(b));
    ASSERT_EQ(2, list.size());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(CompoundTag, erase)
{
    amc::CompoundTag compoundTag;

    // Add 3 Items
    compoundTag.pushBack(new amc::ByteTag("A", 1));
    compoundTag.pushBack(new amc::ByteTag("B", 2));
    compoundTag.pushBack(new amc::ByteTag("C", 3));
    ASSERT_EQ(3, compoundTag.size());

    // Test index too high
    EXPECT_FALSE(compoundTag.eraseAt(3));
    EXPECT_FALSE(compoundTag.eraseAt(900));

    // Erase middle item
    EXPECT_TRUE(compoundTag.eraseAt(1));
    EXPECT_EQ(2, compoundTag.size());

    // Check that item 1 and 3 remain
    std::vector<amc::AbstractTag*> data = compoundTag.getValue();
    amc::ByteTag *bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());
    bt = tag_cast<amc::ByteTag*>(data[1]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(3, bt->getValue());

    // Erase last item
    EXPECT_TRUE(compoundTag.eraseAt(1));
    EXPECT_EQ(1, compoundTag.size());

    // Check remaining item
    data = compoundTag.getValue();
    bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(1, bt->getValue());

    // Erase last item
    EXPECT_TRUE(compoundTag.eraseAt(0));
    EXPECT_EQ(0, compoundTag.size());
    EXPECT_TRUE(compoundTag.isEmpty());
}

TEST(CompoundTag, eraseByValue)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);
    amc::ByteTag *d = new amc::ByteTag("D", 4);

    amc::CompoundTag compoundTag({a, b, c});
    ASSERT_EQ(3, compoundTag.size());

    EXPECT_FALSE(compoundTag.erase(d));
    ASSERT_EQ(3, compoundTag.size());

    EXPECT_TRUE(compoundTag.erase(b));
    ASSERT_EQ(2, compoundTag.size());

    EXPECT_TRUE(compoundTag.erase(c));
    ASSERT_EQ(1, compoundTag.size());

    EXPECT_TRUE(compoundTag.erase(a));
    ASSERT_EQ(0, compoundTag.size());

    delete d;
}

TEST(CompoundTag, insert)
{
    amc::CompoundTag compoundTag;

    // Test insert nullptr
    EXPECT_FALSE(compoundTag.insert(0, nullptr));

    // Test adding a new Item at invalid index
    amc::AbstractTag *invalidTag = new amc::ByteTag("Value", 1);
    EXPECT_FALSE(compoundTag.insert(1, invalidTag));
    delete invalidTag;

    // Add correct item
    EXPECT_TRUE(compoundTag.insert(0, new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());

    // Add second item at end
    EXPECT_TRUE(compoundTag.insert(1, new amc::ByteTag("Value", 3)));
    EXPECT_EQ(2, compoundTag.size());

    // Add third item in between
    EXPECT_TRUE(compoundTag.insert(1, new amc::ByteTag("Value", 2)));
    EXPECT_EQ(3, compoundTag.size());

    // Test correct order
    std::vector<amc::AbstractTag*> data = compoundTag.getValue();
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

TEST(CompoundTag, pushBack)
{
    amc::CompoundTag compoundTag;
    // Test adding a new Item
    EXPECT_TRUE(compoundTag.pushBack(new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());

    // Test adding another tag
    EXPECT_TRUE(compoundTag.pushBack(new amc::StringTag("A", "B")));
    EXPECT_EQ(2, compoundTag.size());

    // Test adding a nullptr
    EXPECT_FALSE(compoundTag.pushBack(nullptr));
    EXPECT_EQ(2, compoundTag.size());
}

TEST(CompoundTag, size)
{
    amc::CompoundTag compoundTag;
    // Test adding a new Item
    ASSERT_TRUE(compoundTag.pushBack(new amc::ByteTag("Value", 1)));
    EXPECT_EQ(1, compoundTag.size());

    // Test adding a second item
    ASSERT_TRUE(compoundTag.pushBack(new amc::IntTag("Value", 2)));
    EXPECT_EQ(2, compoundTag.size());

    // Test adding a third item
    ASSERT_TRUE(compoundTag.pushBack(new amc::StringTag("Value", "V")));
    EXPECT_EQ(3, compoundTag.size());

    // Test erasing an item
    ASSERT_TRUE(compoundTag.eraseAt(0));
    EXPECT_EQ(2, compoundTag.size());

    // clear
    compoundTag.clear();
    EXPECT_EQ(0, compoundTag.size());
}

TEST(CompoundTag, indexOf)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);
    amc::CompoundTag compoundTag({a, b, c});

    EXPECT_EQ(0, compoundTag.indexOf(a));
    EXPECT_EQ(1, compoundTag.indexOf(b));
    EXPECT_EQ(2, compoundTag.indexOf(c));
}

TEST(CompoundTag, swap)
{
    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);
    amc::CompoundTag compoundTag({a, b, c});

    ASSERT_EQ(0, compoundTag.indexOf(a));
    ASSERT_EQ(1, compoundTag.indexOf(b));
    ASSERT_EQ(2, compoundTag.indexOf(c));

    compoundTag.swap(0, 1);

    ASSERT_EQ(0, compoundTag.indexOf(b));
    ASSERT_EQ(1, compoundTag.indexOf(a));
}

TEST(CompoundTag, at)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test at
    amc::ByteTag *v1 = tag_cast<amc::ByteTag*>(compoundTag.at(0));
    amc::ByteTag *v2 = tag_cast<amc::ByteTag*>(compoundTag.at(1));
    amc::ByteTag *v3 = tag_cast<amc::ByteTag*>(compoundTag.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);

    // Test exception
    EXPECT_THROW(compoundTag.at(3), std::out_of_range);
}

TEST(CompoundTag, at_const)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    const amc::CompoundTag compoundTag2(compoundTag);

    // Test at
    const amc::ByteTag *v1 = tag_cast<const amc::ByteTag*>(compoundTag2.at(0));
    const amc::ByteTag *v2 = tag_cast<const amc::ByteTag*>(compoundTag2.at(1));
    const amc::ByteTag *v3 = tag_cast<const amc::ByteTag*>(compoundTag2.at(2));

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);

    // Test exception
    EXPECT_THROW(compoundTag2.at(3), std::out_of_range);
}

TEST(CompoundTag, takeAt)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test
    amc::AbstractTag *bTest = compoundTag.takeAt(1);
    EXPECT_EQ(2, compoundTag.size());
    EXPECT_EQ(b, bTest);
    amc::AbstractTag *aTest = compoundTag.takeAt(0);
    EXPECT_EQ(1, compoundTag.size());
    EXPECT_EQ(a, aTest);
    amc::AbstractTag *cTest = compoundTag.takeAt(0);
    EXPECT_EQ(0, compoundTag.size());
    EXPECT_EQ(c, cTest);

    delete aTest;
    delete bTest;
    delete cTest;
}

TEST(CompoundTag, subscript)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test at
    amc::ByteTag *v1 = tag_cast<amc::ByteTag*>(compoundTag[0]);
    amc::ByteTag *v2 = tag_cast<amc::ByteTag*>(compoundTag[1]);
    amc::ByteTag *v3 = tag_cast<amc::ByteTag*>(compoundTag[2]);

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(CompoundTag, subscript_const)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    const amc::CompoundTag compoundTag2(compoundTag);

    // Test at
    const amc::ByteTag *v1 = tag_cast<const amc::ByteTag*>(compoundTag2[0]);
    const amc::ByteTag *v2 = tag_cast<const amc::ByteTag*>(compoundTag2[1]);
    const amc::ByteTag *v3 = tag_cast<const amc::ByteTag*>(compoundTag2[2]);

    EXPECT_TRUE(*a == *v1);
    EXPECT_TRUE(*b == *v2);
    EXPECT_TRUE(*c == *v3);
}

TEST(CompoundTag, hasChild)
{
    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);

    amc::CompoundTag compoundTag({a, b, c});
    ASSERT_EQ(3, compoundTag.size());

    EXPECT_TRUE(compoundTag.hasChild("A"));
    EXPECT_TRUE(compoundTag.hasChild("B"));
    EXPECT_TRUE(compoundTag.hasChild("C"));
    EXPECT_FALSE(compoundTag.hasChild("D"));
}

TEST(CompoundTag, getChildByName)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test
    amc::AbstractTag *aTest = compoundTag.getChildByName("A");
    EXPECT_EQ(3, compoundTag.size());
    EXPECT_EQ(a, aTest);
    amc::AbstractTag *bTest = compoundTag.getChildByName("B");
    EXPECT_EQ(3, compoundTag.size());
    EXPECT_EQ(b, bTest);
    amc::AbstractTag *cTest = compoundTag.getChildByName("C");
    EXPECT_EQ(3, compoundTag.size());
    EXPECT_EQ(c, cTest);
    amc::AbstractTag *dTest = compoundTag.getChildByName("D");
    EXPECT_EQ(3, compoundTag.size());
    EXPECT_EQ(nullptr, dTest);
}

TEST(CompoundTag, getChildByName_const)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test
    const amc::CompoundTag *testTag = &compoundTag;
    const amc::AbstractTag *aTest = testTag->getChildByName("A");
    EXPECT_EQ(3, testTag->size());
    EXPECT_EQ(a, aTest);
    const amc::AbstractTag *bTest = testTag->getChildByName("B");
    EXPECT_EQ(3, testTag->size());
    EXPECT_EQ(b, bTest);
    const amc::AbstractTag *cTest = testTag->getChildByName("C");
    EXPECT_EQ(3, testTag->size());
    EXPECT_EQ(c, cTest);
    const amc::AbstractTag *dTest = testTag->getChildByName("D");
    EXPECT_EQ(3, testTag->size());
    EXPECT_EQ(nullptr, dTest);
}

TEST(CompoundTag, getChildrenByName)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a     = new amc::ByteTag("A", 1);
    amc::IntTag *b      = new amc::IntTag("B", 2000);
    amc::FloatTag *c    = new amc::FloatTag("C", 3.f);
    amc::FloatTag *d    = new amc::FloatTag("C", 35.f);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    compoundTag.pushBack(d);
    ASSERT_EQ(4, compoundTag.size());

    // Test
    std::vector<amc::AbstractTag*> aTest = compoundTag.getChildrenByName("A");
    EXPECT_EQ(4, compoundTag.size());
    EXPECT_EQ(1, aTest.size());
    EXPECT_EQ(a, aTest[0]);
    std::vector<amc::AbstractTag*> bTest = compoundTag.getChildrenByName("B");
    EXPECT_EQ(4, compoundTag.size());
    EXPECT_EQ(1, bTest.size());
    EXPECT_EQ(b, bTest[0]);
    std::vector<amc::AbstractTag*> cTest = compoundTag.getChildrenByName("C");
    EXPECT_EQ(4, compoundTag.size());
    EXPECT_EQ(2, cTest.size());
    EXPECT_EQ(c, cTest[0]);
    EXPECT_EQ(d, cTest[1]);
    std::vector<amc::AbstractTag*> dTest = compoundTag.getChildrenByName("D");
    EXPECT_EQ(4, compoundTag.size());
    EXPECT_EQ(0, dTest.size());
}

TEST(CompoundTag, getValue)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag    *a = new amc::ByteTag("A", 1);
    amc::IntTag     *b = new amc::IntTag("B", 2);
    amc::StringTag  *c = new amc::StringTag("C", "B");

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    // Test items
    std::vector<amc::AbstractTag*> data = compoundTag.getValue();

    amc::ByteTag *bt = tag_cast<amc::ByteTag*>(data[0]);
    EXPECT_TRUE(bt != nullptr);
    EXPECT_EQ(amc::TagType::Byte, bt->getType());
    EXPECT_EQ(1, bt->getValue());
    EXPECT_STREQ("A", bt->getName().c_str());

    amc::IntTag *it = tag_cast<amc::IntTag*>(data[1]);
    EXPECT_TRUE(it != nullptr);
    EXPECT_EQ(amc::TagType::Int, it->getType());
    EXPECT_EQ(2, it->getValue());
    EXPECT_STREQ("B", it->getName().c_str());

    amc::StringTag *st = tag_cast<amc::StringTag*>(data[2]);
    EXPECT_TRUE(st != nullptr);
    EXPECT_EQ(amc::TagType::String, st->getType());
    EXPECT_STREQ("B", st->getValue().c_str());
    EXPECT_STREQ("C", st->getName().c_str());
}

TEST(CompoundTag, getValueCopy)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    // Add 3 Items
    compoundTag.pushBack(a);
    compoundTag.pushBack(b);
    compoundTag.pushBack(c);
    ASSERT_EQ(3, compoundTag.size());

    std::vector<amc::AbstractTag*> data = compoundTag.getValueCopy();
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

TEST(CompoundTag, setValue)
{
    amc::CompoundTag compoundTag;

    amc::ByteTag *a = new amc::ByteTag("A", 1);
    amc::ByteTag *b = new amc::ByteTag("B", 2);
    amc::ByteTag *c = new amc::ByteTag("C", 3);

    std::vector<amc::AbstractTag*> data({a, b, c});

    EXPECT_EQ(0, compoundTag.size());
    compoundTag.setValue(data);
    EXPECT_EQ(3, compoundTag.size());

    std::vector<amc::AbstractTag*> data2 = compoundTag.getValue();

    EXPECT_TRUE(*data2[0] == *data[0]);
    EXPECT_TRUE(*data2[1] == *data[1]);
    EXPECT_TRUE(*data2[2] == *data[2]);

    delete a;
    delete b;
    delete c;
}

TEST(CompoundTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::CompoundTag("A");

    amc::CompoundTag *otherTag = tag_cast<amc::CompoundTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}