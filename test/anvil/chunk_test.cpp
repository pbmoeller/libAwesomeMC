#include "anvil/chunk.hpp"
#include "nbt/tags/int_tag.hpp"

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