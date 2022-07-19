// AwesomeMC
#include <AwesomeMC/anvil/chunk.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/nbt/tags/float_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Chunk, Constructor)
{
    amc::Chunk chunk;
    EXPECT_EQ(nullptr, chunk.getRootTag());
}

TEST(Chunk, CopyConstructor)
{
    amc::Chunk chunkA;

    amc::CompoundTag *root = new amc::CompoundTag("CopyConstructor");
    root->pushBack(new amc::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    amc::Chunk chunkB(chunkA);
    
    amc::CompoundTag *rootA = chunkA.getRootTag();
    amc::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootA->getName().c_str(), rootB->getName().c_str());
    EXPECT_EQ(rootA->size(), rootB->size());
}

TEST(Chunk, MoveConstructor)
{
    amc::Chunk chunkA;

    amc::CompoundTag *root = new amc::CompoundTag("MoveConstructor");
    root->pushBack(new amc::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    amc::Chunk chunkB(std::move(chunkA));

    amc::CompoundTag *rootA = chunkA.getRootTag();
    amc::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootB->getName().c_str(), "MoveConstructor");
    EXPECT_TRUE(rootA== nullptr);
    EXPECT_EQ(rootB->size(), 1);
}

TEST(Chunk, CopyAssignment)
{
    amc::Chunk chunkA;

    amc::CompoundTag *root = new amc::CompoundTag("CopyAssignment");
    root->pushBack(new amc::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    amc::Chunk chunkB = chunkA;

    amc::CompoundTag *rootA = chunkA.getRootTag();
    amc::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootA->getName().c_str(), rootB->getName().c_str());
    EXPECT_EQ(rootA->size(), rootB->size());
}

TEST(Chunk, MoveAssignment)
{
    amc::Chunk chunkA;

    amc::CompoundTag *root = new amc::CompoundTag("MoveAssignment");
    root->pushBack(new amc::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    amc::Chunk chunkB = std::move(chunkA);

    amc::CompoundTag *rootA = chunkA.getRootTag();
    amc::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootB->getName().c_str(), "MoveAssignment");
    EXPECT_TRUE(rootA == nullptr);
    EXPECT_EQ(rootB->size(), 1);
}

TEST(Chunk, Equal)
{
    amc::CompoundTag *root = new amc::CompoundTag("Equal");
    root->pushBack(new amc::IntTag("IntTag", 5));
    amc::CompoundTag *root2 = new amc::CompoundTag("Equal");
    root2->pushBack(new amc::IntTag("IntTag", 5));

    amc::Chunk chunkA;
    amc::Chunk chunkB;
    amc::Chunk chunkC;
    chunkA.setRootTag(root);
    chunkB.setRootTag(root2);

    EXPECT_TRUE(chunkA == chunkB);
    EXPECT_FALSE(chunkA == chunkC);
    EXPECT_FALSE(chunkB == chunkC);

    chunkA.getRootTag()->pushBack(new amc::IntTag("IntTag", 9));
    EXPECT_FALSE(chunkA == chunkB);
}

TEST(Chunk, NotEqual)
{
    amc::CompoundTag *root = new amc::CompoundTag("NotEqual");
    root->pushBack(new amc::IntTag("IntTag", 5));
    amc::CompoundTag *root2 = new amc::CompoundTag("NotEqual");
    root2->pushBack(new amc::IntTag("IntTag", 5));

    amc::Chunk chunkA;
    amc::Chunk chunkB;
    amc::Chunk chunkC;
    chunkA.setRootTag(root);
    chunkB.setRootTag(root2);

    EXPECT_FALSE(chunkA != chunkB);
    EXPECT_TRUE(chunkA != chunkC);
    EXPECT_TRUE(chunkB != chunkC);

    chunkA.getRootTag()->pushBack(new amc::IntTag("IntTag", 9));
    EXPECT_TRUE(chunkA != chunkB);
}

TEST(Chunk, clear)
{
    amc::CompoundTag *root = new amc::CompoundTag("clear");
    root->pushBack(new amc::IntTag("IntTag", 25));

    amc::Chunk chunk;
    chunk.setRootTag(root);

    amc::CompoundTag *rootGet = chunk.getRootTag();
    EXPECT_EQ(rootGet->getType(), amc::TagType::Compound);

    chunk.clear();

    rootGet = chunk.getRootTag();
    EXPECT_EQ(nullptr, rootGet);
}

TEST(Chunk, isEmpty)
{
    amc::CompoundTag *root = new amc::CompoundTag("clear");

    amc::Chunk chunk;
    EXPECT_TRUE(chunk.isEmpty());

    chunk.setRootTag(root);
    EXPECT_FALSE(chunk.isEmpty());

    chunk.clear();
    EXPECT_TRUE(chunk.isEmpty());
}

TEST(Chunk, getRootTag)
{
    amc::CompoundTag *root = new amc::CompoundTag("getRootTag");
    root->pushBack(new amc::IntTag("IntTag", 5));

    amc::Chunk chunk;
    amc::CompoundTag *rootGet = chunk.getRootTag();
    EXPECT_EQ(nullptr, rootGet);

    chunk.setRootTag(root);

    amc::CompoundTag *rootGet2 = chunk.getRootTag();
    EXPECT_EQ(rootGet2, root);
}

TEST(Chunk, setRootTag)
{
    amc::CompoundTag *root = new amc::CompoundTag("setRootTag");
    root->pushBack(new amc::IntTag("IntTag", 5));
    amc::CompoundTag *root2 = new amc::CompoundTag("setRootTag2");
    root2->pushBack(new amc::IntTag("IntTag", 15));

    amc::Chunk chunk;
    chunk.setRootTag(root);

    EXPECT_EQ(chunk.getRootTag()->getType(), amc::TagType::Compound);
    EXPECT_STREQ(chunk.getRootTag()->getName().c_str(), "setRootTag");

    chunk.setRootTag(root2);

    EXPECT_EQ(chunk.getRootTag()->getType(), amc::TagType::Compound);
    EXPECT_STREQ(chunk.getRootTag()->getName().c_str(), "setRootTag2");
    EXPECT_STREQ(chunk.getRootTag()->getValue()[0]->getName().c_str(), "IntTag");
}

TEST(Chunk, getSubTagsByName)
{
    // Init CompoundTag & Chunk
    amc::CompoundTag *root = new amc::CompoundTag("getSubTagsByName");
    amc::IntTag *int1 = new amc::IntTag("IntTag", 4);
    root->pushBack(int1);

    amc::CompoundTag *subTag1 = new amc::CompoundTag("sub1");
    amc::IntTag *int2 = new amc::IntTag("IntTag", 5);
    amc::IntTag *int3 = new amc::IntTag("IntTag", 6);
    amc::IntTag *int4 = new amc::IntTag("IntTag", 7);
    root->pushBack(int2);
    root->pushBack(int3);
    root->pushBack(int4);

    amc::CompoundTag *subTag2 = new amc::CompoundTag("sub2");
    amc::FloatTag *float1 = new amc::FloatTag("FloatTag", 55.f);
    amc::FloatTag *float2 = new amc::FloatTag("FloatTag", 56.f);
    amc::FloatTag *float3 = new amc::FloatTag("FloatTag", 57.f);
    root->pushBack(float1);
    root->pushBack(float2);
    root->pushBack(float3);

    root->pushBack(subTag1);
    root->pushBack(subTag2);

    amc::Chunk chunk;
    chunk.setRootTag(root);

    // Test
    std::vector<amc::AbstractTag*> tags1 = chunk.getSubTagsByName("getSubTagsByName");
    EXPECT_EQ(1, tags1.size());
    EXPECT_EQ(tags1[0], root);

    std::vector<amc::AbstractTag*> tags2 = chunk.getSubTagsByName("sub1");
    EXPECT_EQ(1, tags2.size());
    EXPECT_EQ(tags2[0], subTag1);

    std::vector<amc::AbstractTag*> tags3 = chunk.getSubTagsByName("sub2");
    EXPECT_EQ(1, tags3.size());
    EXPECT_EQ(tags3[0], subTag2);

    std::vector<amc::AbstractTag*> tags4 = chunk.getSubTagsByName("IntTag");
    EXPECT_EQ(4, tags4.size());
    EXPECT_EQ(tags4[0], int1);
    EXPECT_EQ(tags4[1], int2);
    EXPECT_EQ(tags4[2], int3);
    EXPECT_EQ(tags4[3], int4);

    std::vector<amc::AbstractTag*> tags5 = chunk.getSubTagsByName("FloatTag");
    EXPECT_EQ(3, tags5.size());
    EXPECT_EQ(tags5[0], float1);
    EXPECT_EQ(tags5[1], float2);
    EXPECT_EQ(tags5[2], float3);
}

TEST(Chunk, getBiomes)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Chunk, getBiomeAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Chunk, getBlockAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Chunk, getPaletteAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}