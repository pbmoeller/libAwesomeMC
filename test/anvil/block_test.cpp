// AwesomeMC
#include <AwesomeMC/anvil/block.hpp>
#include <AwesomeMC/nbt/tags/compound_tag.hpp>
#include <AwesomeMC/nbt/tags/string_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class BlockFixture : public ::testing::Test
{
protected:
    nbt::CompoundTag compound;
    nbt::CompoundTag *compoundPtr = nullptr;

    virtual void SetUp()
    {
        // Init stack CompoundTag
        compound = nbt::CompoundTag("Compound");
        compound.pushBack(new nbt::StringTag("name", "value"));
        compound.pushBack(new nbt::StringTag("name2", "value2"));
        compound.pushBack(new nbt::IntTag("name3", 4));

        // Init heap CompoundTag
        compoundPtr = new nbt::CompoundTag("CompoundPtr");
        compoundPtr->pushBack(new nbt::StringTag("name", "value"));
        compoundPtr->pushBack(new nbt::StringTag("name2", "value2"));
        compoundPtr->pushBack(new nbt::IntTag("name3", 5));
    }

    virtual void TearDown()
    {
        delete compoundPtr;
    }
};

TEST_F(BlockFixture, Constructor)
{
    anvil::Block block;
    EXPECT_EQ(0, block.getX());
    EXPECT_EQ(0, block.getY());
    EXPECT_EQ(0, block.getZ());
    EXPECT_STREQ("", block.getName().c_str());
    EXPECT_TRUE(nbt::CompoundTag() == block.getProperties());
}

TEST_F(BlockFixture, Constructor_2)
{
    anvil::Block block(1, -5, 1024, "minecraft:air");
    EXPECT_EQ(1, block.getX());
    EXPECT_EQ(-5, block.getY());
    EXPECT_EQ(1024, block.getZ());
    EXPECT_STREQ("minecraft:air", block.getName().c_str());
    EXPECT_TRUE(nbt::CompoundTag() == block.getProperties());
}

TEST_F(BlockFixture, Constructor_3)
{
    anvil::Block block(-11, 64, 12, "minecraft:stone", compound);
    EXPECT_EQ(-11, block.getX());
    EXPECT_EQ(64, block.getY());
    EXPECT_EQ(12, block.getZ());
    EXPECT_STREQ("minecraft:stone", block.getName().c_str());
    EXPECT_TRUE(compound == block.getProperties());
}

TEST_F(BlockFixture, CopyConstructor)
{
    anvil::Block block(-11, 64, 12, "minecraft:stone", compound);
    anvil::Block block2(block);
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STREQ(block.getName().c_str(), block2.getName().c_str());
    EXPECT_TRUE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, MoveConstructor)
{
    anvil::Block block(-11, 64, 12, "minecraft:stone", compound);
    anvil::Block block2(std::move(block));
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STRNE(block.getName().c_str(), block2.getName().c_str());
    EXPECT_STREQ("minecraft:stone", block2.getName().c_str());
    EXPECT_FALSE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, CopyAssignment)
{
    anvil::Block block(-11, 64, 12, "minecraft:stone", compound);
    anvil::Block block2 = block;
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STREQ(block.getName().c_str(), block2.getName().c_str());
    EXPECT_TRUE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, MoveAssignment)
{
    anvil::Block block(-11, 64, 12, "minecraft:stone", compound);
    anvil::Block block2 = std::move(block);
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STRNE(block.getName().c_str(), block2.getName().c_str());
    EXPECT_STREQ("minecraft:stone", block2.getName().c_str());
    EXPECT_FALSE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, Equal)
{
    anvil::Block b1(1, 2, 3, "minecraft:stone", compound);
    anvil::Block b2(1, 2, 3, "minecraft:stone", compound);
    anvil::Block b3(1, 2, 4, "minecraft:stone", compound);
    anvil::Block b4(1, 2, 3, "minecraft:stone", *compoundPtr);

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
    EXPECT_FALSE(b1 == b4);
}

TEST_F(BlockFixture, NotEqual)
{
    anvil::Block b1(1, 2, 3, "minecraft:stone", compound);
    anvil::Block b2(1, 2, 3, "minecraft:stone", compound);
    anvil::Block b3(1, 2, 4, "minecraft:stone", compound);
    anvil::Block b4(1, 2, 3, "minecraft:stone", *compoundPtr);

    EXPECT_FALSE(b1 != b2);
    EXPECT_TRUE(b1 != b3);
    EXPECT_TRUE(b1 != b4);
}

TEST_F(BlockFixture, getX)
{
    anvil::Block blockA(1, 2, 3, "minecraft:stone");
    anvil::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_EQ(1, blockA.getX());
    EXPECT_EQ(-5, blockB.getX());
}

TEST_F(BlockFixture, setX)
{
    anvil::Block block;
    EXPECT_EQ(0, block.getX());
    block.setX(3);
    EXPECT_EQ(3, block.getX());
    block.setX(1000);
    EXPECT_EQ(1000, block.getX());
}

TEST_F(BlockFixture, getY)
{
    anvil::Block blockA(1, 2, 3, "minecraft:stone");
    anvil::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_EQ(2, blockA.getY());
    EXPECT_EQ(64, blockB.getY());
}

TEST_F(BlockFixture, setY)
{
    anvil::Block block;
    EXPECT_EQ(0, block.getY());
    block.setY(3);
    EXPECT_EQ(3, block.getY());
    block.setY(1000);
    EXPECT_EQ(1000, block.getY());
}

TEST_F(BlockFixture, getZ)
{
    anvil::Block blockA(1, 2, 3, "minecraft:stone");
    anvil::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_EQ(3, blockA.getZ());
    EXPECT_EQ(-1000, blockB.getZ());
}

TEST_F(BlockFixture, setZ)
{
    anvil::Block block;
    EXPECT_EQ(0, block.getZ());
    block.setZ(3);
    EXPECT_EQ(3, block.getZ());
    block.setZ(1000);
    EXPECT_EQ(1000, block.getZ());
}

TEST_F(BlockFixture, setXYZ)
{
    anvil::Block block;
    EXPECT_EQ(0, block.getX());
    EXPECT_EQ(0, block.getY());
    EXPECT_EQ(0, block.getZ());
    block.setXYZ(-2, 10, -5);
    EXPECT_EQ(-2, block.getX());
    EXPECT_EQ(10, block.getY());
    EXPECT_EQ(-5, block.getZ());
}

TEST_F(BlockFixture, getName)
{
    anvil::Block blockA(1, 2, 3, "minecraft:stone");
    anvil::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_STREQ(blockA.getName().c_str(), "minecraft:stone");
    EXPECT_STREQ(blockB.getName().c_str(), "minecraft:dirt");
}

TEST_F(BlockFixture, setName)
{
    anvil::Block block;
    EXPECT_STREQ(block.getName().c_str(), "");
    block.setName("minecraft:stone");
    EXPECT_STREQ(block.getName().c_str(), "minecraft:stone");
    block.setName("minecraft:dirt");
    EXPECT_STREQ(block.getName().c_str(), "minecraft:dirt");
}

TEST_F(BlockFixture, getProperties)
{
    anvil::Block block;
    EXPECT_EQ(block.getProperties().size(), 0);
    
    anvil::Block block2(0, 0, 0, "minecraft:stone", compound);
    EXPECT_EQ(block2.getProperties().size(), 3);
    EXPECT_EQ(block2.getProperties(), compound);

    anvil::Block block3(0, 0, 0, "minecraft:stone", *compoundPtr);
    EXPECT_EQ(block3.getProperties().size(), 3);
    EXPECT_EQ(block3.getProperties(), *compoundPtr);
}

TEST_F(BlockFixture, setProperties)
{
    anvil::Block block;
    EXPECT_EQ(block.getProperties().size(), 0);
    block.setProperties(compound);
    EXPECT_EQ(block.getProperties().size(), 3);
    EXPECT_EQ(block.getProperties(), compound);
    block.setProperties(*compoundPtr);
    EXPECT_EQ(block.getProperties().size(), 3);
    EXPECT_EQ(block.getProperties(), *compoundPtr);
}
