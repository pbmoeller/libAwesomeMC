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
    amc::CompoundTag compound;
    amc::CompoundTag *compoundPtr = nullptr;

    virtual void SetUp()
    {
        // Init stack CompoundTag
        compound = amc::CompoundTag("Compound");
        compound.pushBack(new amc::StringTag("name", "value"));
        compound.pushBack(new amc::StringTag("name2", "value2"));
        compound.pushBack(new amc::IntTag("name3", 4));

        // Init heap CompoundTag
        compoundPtr = new amc::CompoundTag("CompoundPtr");
        compoundPtr->pushBack(new amc::StringTag("name", "value"));
        compoundPtr->pushBack(new amc::StringTag("name2", "value2"));
        compoundPtr->pushBack(new amc::IntTag("name3", 5));
    }

    virtual void TearDown()
    {
        delete compoundPtr;
    }
};

TEST_F(BlockFixture, Constructor)
{
    amc::Block block;
    EXPECT_EQ(0, block.getX());
    EXPECT_EQ(0, block.getY());
    EXPECT_EQ(0, block.getZ());
    EXPECT_STREQ("", block.getName().c_str());
    EXPECT_TRUE(amc::CompoundTag() == block.getProperties());
}

TEST_F(BlockFixture, Constructor_2)
{
    amc::Block block(1, -5, 1024, "minecraft:air");
    EXPECT_EQ(1, block.getX());
    EXPECT_EQ(-5, block.getY());
    EXPECT_EQ(1024, block.getZ());
    EXPECT_STREQ("minecraft:air", block.getName().c_str());
    EXPECT_TRUE(amc::CompoundTag() == block.getProperties());
}

TEST_F(BlockFixture, Constructor_3)
{
    amc::Block block(-11, 64, 12, "minecraft:stone", compound);
    EXPECT_EQ(-11, block.getX());
    EXPECT_EQ(64, block.getY());
    EXPECT_EQ(12, block.getZ());
    EXPECT_STREQ("minecraft:stone", block.getName().c_str());
    EXPECT_TRUE(compound == block.getProperties());
}

TEST_F(BlockFixture, CopyConstructor)
{
    amc::Block block(-11, 64, 12, "minecraft:stone", compound);
    amc::Block block2(block);
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STREQ(block.getName().c_str(), block2.getName().c_str());
    EXPECT_TRUE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, MoveConstructor)
{
    amc::Block block(-11, 64, 12, "minecraft:stone", compound);
    amc::Block block2(std::move(block));
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STRNE(block.getName().c_str(), block2.getName().c_str());
    EXPECT_STREQ("minecraft:stone", block2.getName().c_str());
    EXPECT_FALSE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, CopyAssignment)
{
    amc::Block block(-11, 64, 12, "minecraft:stone", compound);
    amc::Block block2 = block;
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STREQ(block.getName().c_str(), block2.getName().c_str());
    EXPECT_TRUE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, MoveAssignment)
{
    amc::Block block(-11, 64, 12, "minecraft:stone", compound);
    amc::Block block2 = std::move(block);
    EXPECT_EQ(block.getX(), block2.getX());
    EXPECT_EQ(block.getY(), block2.getY());
    EXPECT_EQ(block.getZ(), block2.getZ());
    EXPECT_STRNE(block.getName().c_str(), block2.getName().c_str());
    EXPECT_STREQ("minecraft:stone", block2.getName().c_str());
    EXPECT_FALSE(block.getProperties() == block2.getProperties());
}

TEST_F(BlockFixture, Equal)
{
    amc::Block b1(1, 2, 3, "minecraft:stone", compound);
    amc::Block b2(1, 2, 3, "minecraft:stone", compound);
    amc::Block b3(1, 2, 4, "minecraft:stone", compound);
    amc::Block b4(1, 2, 3, "minecraft:stone", *compoundPtr);

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
    EXPECT_FALSE(b1 == b4);
}

TEST_F(BlockFixture, NotEqual)
{
    amc::Block b1(1, 2, 3, "minecraft:stone", compound);
    amc::Block b2(1, 2, 3, "minecraft:stone", compound);
    amc::Block b3(1, 2, 4, "minecraft:stone", compound);
    amc::Block b4(1, 2, 3, "minecraft:stone", *compoundPtr);

    EXPECT_FALSE(b1 != b2);
    EXPECT_TRUE(b1 != b3);
    EXPECT_TRUE(b1 != b4);
}

TEST_F(BlockFixture, getX)
{
    amc::Block blockA(1, 2, 3, "minecraft:stone");
    amc::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_EQ(1, blockA.getX());
    EXPECT_EQ(-5, blockB.getX());
}

TEST_F(BlockFixture, setX)
{
    amc::Block block;
    EXPECT_EQ(0, block.getX());
    block.setX(3);
    EXPECT_EQ(3, block.getX());
    block.setX(1000);
    EXPECT_EQ(1000, block.getX());
}

TEST_F(BlockFixture, getY)
{
    amc::Block blockA(1, 2, 3, "minecraft:stone");
    amc::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_EQ(2, blockA.getY());
    EXPECT_EQ(64, blockB.getY());
}

TEST_F(BlockFixture, setY)
{
    amc::Block block;
    EXPECT_EQ(0, block.getY());
    block.setY(3);
    EXPECT_EQ(3, block.getY());
    block.setY(1000);
    EXPECT_EQ(1000, block.getY());
}

TEST_F(BlockFixture, getZ)
{
    amc::Block blockA(1, 2, 3, "minecraft:stone");
    amc::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_EQ(3, blockA.getZ());
    EXPECT_EQ(-1000, blockB.getZ());
}

TEST_F(BlockFixture, setZ)
{
    amc::Block block;
    EXPECT_EQ(0, block.getZ());
    block.setZ(3);
    EXPECT_EQ(3, block.getZ());
    block.setZ(1000);
    EXPECT_EQ(1000, block.getZ());
}

TEST_F(BlockFixture, setXYZ)
{
    amc::Block block;
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
    amc::Block blockA(1, 2, 3, "minecraft:stone");
    amc::Block blockB(-5, 64, -1000, "minecraft:dirt");
    EXPECT_STREQ(blockA.getName().c_str(), "minecraft:stone");
    EXPECT_STREQ(blockB.getName().c_str(), "minecraft:dirt");
}

TEST_F(BlockFixture, setName)
{
    amc::Block block;
    EXPECT_STREQ(block.getName().c_str(), "");
    block.setName("minecraft:stone");
    EXPECT_STREQ(block.getName().c_str(), "minecraft:stone");
    block.setName("minecraft:dirt");
    EXPECT_STREQ(block.getName().c_str(), "minecraft:dirt");
}

TEST_F(BlockFixture, getProperties)
{
    amc::Block block;
    EXPECT_EQ(block.getProperties().size(), 0);
    
    amc::Block block2(0, 0, 0, "minecraft:stone", compound);
    EXPECT_EQ(block2.getProperties().size(), 3);
    EXPECT_EQ(block2.getProperties(), compound);

    amc::Block block3(0, 0, 0, "minecraft:stone", *compoundPtr);
    EXPECT_EQ(block3.getProperties().size(), 3);
    EXPECT_EQ(block3.getProperties(), *compoundPtr);
}

TEST_F(BlockFixture, setProperties)
{
    amc::Block block;
    EXPECT_EQ(block.getProperties().size(), 0);
    block.setProperties(compound);
    EXPECT_EQ(block.getProperties().size(), 3);
    EXPECT_EQ(block.getProperties(), compound);
    block.setProperties(*compoundPtr);
    EXPECT_EQ(block.getProperties().size(), 3);
    EXPECT_EQ(block.getProperties(), *compoundPtr);
}
