// AwesomeMC
#include <AwesomeMC/anvil/region.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Region, Constructor)
{
    anvil::Region region;
    EXPECT_EQ(0, region.getX());
    EXPECT_EQ(0, region.getZ());
}

TEST(Region, Constructor_2)
{
    anvil::Region region(32, 12);
    EXPECT_EQ(32, region.getX());
    EXPECT_EQ(12, region.getZ());
}

TEST(Region, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, Equal)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, NotEqual)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getX)
{
    anvil::Region region(31, 11);
    EXPECT_EQ(31, region.getX());
    region.setX(5);
    EXPECT_EQ(5, region.getX());
}

TEST(Region, setX)
{
    anvil::Region region;
    EXPECT_EQ(0, region.getX());
    region.setX(2);
    EXPECT_EQ(2, region.getX());
}

TEST(Region, getZ)
{
    anvil::Region region(31, 11);
    EXPECT_EQ(11, region.getZ());
    region.setZ(4);
    EXPECT_EQ(4, region.getZ());
}

TEST(Region, setZ)
{
    anvil::Region region;
    EXPECT_EQ(0, region.getZ());
    region.setZ(1);
    EXPECT_EQ(1, region.getZ());
}

TEST(Region, getRegionHeader)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getRegionHeader_const)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, setRegionHeader)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getChunks)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getChunkAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getChunkAt_const)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getBiomesAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getBiomeAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, getBlockAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}
