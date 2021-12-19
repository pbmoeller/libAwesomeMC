#include "anvil/chunk.hpp"
#include "nbt/tags/int_tag.hpp"
#include "nbt/tags/float_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Chunk, Constructor)
{
    anvil::Chunk chunk;
    EXPECT_EQ(nullptr, chunk.getRootTag());
}

TEST(Chunk, CopyConstructor)
{
    anvil::Chunk chunkA;

    nbt::CompoundTag *root = new nbt::CompoundTag("CopyConstructor");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    anvil::Chunk chunkB(chunkA);
    
    nbt::CompoundTag *rootA = chunkA.getRootTag();
    nbt::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootA->getName().c_str(), rootB->getName().c_str());
    EXPECT_EQ(rootA->size(), rootB->size());
}

TEST(Chunk, MoveConstructor)
{
    anvil::Chunk chunkA;

    nbt::CompoundTag *root = new nbt::CompoundTag("MoveConstructor");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    anvil::Chunk chunkB(std::move(chunkA));

    nbt::CompoundTag *rootA = chunkA.getRootTag();
    nbt::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootB->getName().c_str(), "MoveConstructor");
    EXPECT_TRUE(rootA== nullptr);
    EXPECT_EQ(rootB->size(), 1);
}

TEST(Chunk, CopyAssignment)
{
    anvil::Chunk chunkA;

    nbt::CompoundTag *root = new nbt::CompoundTag("CopyAssignment");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    anvil::Chunk chunkB = chunkA;

    nbt::CompoundTag *rootA = chunkA.getRootTag();
    nbt::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootA->getName().c_str(), rootB->getName().c_str());
    EXPECT_EQ(rootA->size(), rootB->size());
}

TEST(Chunk, MoveAssignment)
{
    anvil::Chunk chunkA;

    nbt::CompoundTag *root = new nbt::CompoundTag("MoveAssignment");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    chunkA.setRootTag(root);

    anvil::Chunk chunkB = std::move(chunkA);

    nbt::CompoundTag *rootA = chunkA.getRootTag();
    nbt::CompoundTag *rootB = chunkB.getRootTag();

    EXPECT_TRUE(rootA != rootB);
    EXPECT_STREQ(rootB->getName().c_str(), "MoveAssignment");
    EXPECT_TRUE(rootA == nullptr);
    EXPECT_EQ(rootB->size(), 1);
}

TEST(Chunk, Equal)
{
    nbt::CompoundTag *root = new nbt::CompoundTag("Equal");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    nbt::CompoundTag *root2 = new nbt::CompoundTag("Equal");
    root2->pushBack(new nbt::IntTag("IntTag", 5));

    anvil::Chunk chunkA;
    anvil::Chunk chunkB;
    anvil::Chunk chunkC;
    chunkA.setRootTag(root);
    chunkB.setRootTag(root2);

    EXPECT_TRUE(chunkA == chunkB);
    EXPECT_FALSE(chunkA == chunkC);
    EXPECT_FALSE(chunkB == chunkC);

    chunkA.getRootTag()->pushBack(new nbt::IntTag("IntTag", 9));
    EXPECT_FALSE(chunkA == chunkB);
}

TEST(Chunk, NotEqual)
{
    nbt::CompoundTag *root = new nbt::CompoundTag("NotEqual");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    nbt::CompoundTag *root2 = new nbt::CompoundTag("NotEqual");
    root2->pushBack(new nbt::IntTag("IntTag", 5));

    anvil::Chunk chunkA;
    anvil::Chunk chunkB;
    anvil::Chunk chunkC;
    chunkA.setRootTag(root);
    chunkB.setRootTag(root2);

    EXPECT_FALSE(chunkA != chunkB);
    EXPECT_TRUE(chunkA != chunkC);
    EXPECT_TRUE(chunkB != chunkC);

    chunkA.getRootTag()->pushBack(new nbt::IntTag("IntTag", 9));
    EXPECT_TRUE(chunkA != chunkB);
}

TEST(Chunk, clear)
{
    nbt::CompoundTag *root = new nbt::CompoundTag("clear");
    root->pushBack(new nbt::IntTag("IntTag", 25));

    anvil::Chunk chunk;
    chunk.setRootTag(root);

    nbt::CompoundTag *rootGet = chunk.getRootTag();
    EXPECT_EQ(rootGet->getType(), nbt::TagType::Compound);

    chunk.clear();

    rootGet = chunk.getRootTag();
    EXPECT_EQ(nullptr, rootGet);
}

TEST(Chunk, getRootTag)
{
    nbt::CompoundTag *root = new nbt::CompoundTag("getRootTag");
    root->pushBack(new nbt::IntTag("IntTag", 5));

    anvil::Chunk chunk;
    nbt::CompoundTag *rootGet = chunk.getRootTag();
    EXPECT_EQ(nullptr, rootGet);

    chunk.setRootTag(root);

    nbt::CompoundTag *rootGet2 = chunk.getRootTag();
    EXPECT_EQ(rootGet2, root);
}

TEST(Chunk, setRootTag)
{
    nbt::CompoundTag *root = new nbt::CompoundTag("setRootTag");
    root->pushBack(new nbt::IntTag("IntTag", 5));
    nbt::CompoundTag *root2 = new nbt::CompoundTag("setRootTag2");
    root2->pushBack(new nbt::IntTag("IntTag", 15));

    anvil::Chunk chunk;
    chunk.setRootTag(root);

    EXPECT_EQ(chunk.getRootTag()->getType(), nbt::TagType::Compound);
    EXPECT_STREQ(chunk.getRootTag()->getName().c_str(), "setRootTag");

    chunk.setRootTag(root2);

    EXPECT_EQ(chunk.getRootTag()->getType(), nbt::TagType::Compound);
    EXPECT_STREQ(chunk.getRootTag()->getName().c_str(), "setRootTag2");
    EXPECT_STREQ(chunk.getRootTag()->getValue()[0]->getName().c_str(), "IntTag");
}

TEST(Chunk, getSubTagsByName)
{
    // Init CompoundTag & Chunk
    nbt::CompoundTag *root = new nbt::CompoundTag("getSubTagsByName");
    nbt::IntTag *int1 = new nbt::IntTag("IntTag", 4);
    root->pushBack(int1);

    nbt::CompoundTag *subTag1 = new nbt::CompoundTag("sub1");
    nbt::IntTag *int2 = new nbt::IntTag("IntTag", 5);
    nbt::IntTag *int3 = new nbt::IntTag("IntTag", 6);
    nbt::IntTag *int4 = new nbt::IntTag("IntTag", 7);
    root->pushBack(int2);
    root->pushBack(int3);
    root->pushBack(int4);

    nbt::CompoundTag *subTag2 = new nbt::CompoundTag("sub2");
    nbt::FloatTag *float1 = new nbt::FloatTag("FloatTag", 55.f);
    nbt::FloatTag *float2 = new nbt::FloatTag("FloatTag", 56.f);
    nbt::FloatTag *float3 = new nbt::FloatTag("FloatTag", 57.f);
    root->pushBack(float1);
    root->pushBack(float2);
    root->pushBack(float3);

    root->pushBack(subTag1);
    root->pushBack(subTag2);

    anvil::Chunk chunk;
    chunk.setRootTag(root);

    // Test
    std::vector<nbt::AbstractTag*> tags1 = chunk.getSubTagsByName("getSubTagsByName");
    EXPECT_EQ(1, tags1.size());
    EXPECT_EQ(tags1[0], root);

    std::vector<nbt::AbstractTag*> tags2 = chunk.getSubTagsByName("sub1");
    EXPECT_EQ(1, tags2.size());
    EXPECT_EQ(tags2[0], subTag1);

    std::vector<nbt::AbstractTag*> tags3 = chunk.getSubTagsByName("sub2");
    EXPECT_EQ(1, tags3.size());
    EXPECT_EQ(tags3[0], subTag2);

    std::vector<nbt::AbstractTag*> tags4 = chunk.getSubTagsByName("IntTag");
    EXPECT_EQ(4, tags4.size());
    EXPECT_EQ(tags4[0], int1);
    EXPECT_EQ(tags4[1], int2);
    EXPECT_EQ(tags4[2], int3);
    EXPECT_EQ(tags4[3], int4);

    std::vector<nbt::AbstractTag*> tags5 = chunk.getSubTagsByName("FloatTag");
    EXPECT_EQ(3, tags5.size());
    EXPECT_EQ(tags5[0], float1);
    EXPECT_EQ(tags5[1], float2);
    EXPECT_EQ(tags5[2], float3);
}