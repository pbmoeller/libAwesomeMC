// AwesomeMC
#include <AwesomeMC/anvil/region.hpp>
#include <AwesomeMC/anvil/heightmap.hpp>
#include <AwesomeMC/anvil/anvil_read.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

const std::string testFolder = "../../../test/testdata/world/";

class RegionFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        
    }

    static void SetUpTestSuite() 
    {
        const std::string filename = testFolder + "libAwesomeMC_TestWorld_1_18_1\\region\\r.-1.-1.mca";
        region = anvil::loadRegion(filename);
    }

    virtual void TearDown() override
    {

    }

    const std::array<int, anvil::BlockCount> expectedHeights = {
        64, 64, 64, 64, 64, 64,  64,  64,  64,  64, 64, 64, 64, 64, 64, 64, // 0
        64, 68, 68, 68, 68, 68,  68,  68,  68,  68, 68, 68, 68, 68, 68, 64, // 1
        64, 68, 73, 73, 73, 73,  73,  73,  73,  73, 73, 73, 73, 73, 68, 64, // 2
        64, 68, 73, 79, 79, 79,  79,  79,  79,  79, 79, 79, 79, 73, 68, 64, // 3
        64, 68, 73, 79, 86, 86,  86,  86,  86,  86, 86, 86, 79, 73, 68, 64, // 4
        64, 68, 73, 79, 86, 94,  94,  94,  94,  94, 94, 86, 79, 73, 68, 64, // 5
        64, 68, 73, 79, 86, 94, 107, 105, 106, 104, 94, 86, 79, 73, 68, 64, // 6
        64, 68, 73, 79, 86, 94, 103, 109, 104, 109, 94, 86, 79, 73, 68, 64, // 7
        64, 68, 73, 79, 86, 94, 105, 106, 108, 107, 94, 86, 79, 73, 68, 64, // 8
        64, 68, 73, 79, 86, 94, 108, 104, 105, 106, 94, 86, 79, 73, 68, 64, // 9
        64, 68, 73, 79, 86, 94,  94,  94,  94,  94, 94, 86, 79, 73, 68, 64, // 10
        64, 68, 73, 79, 86, 86,  86,  86,  86,  86, 86, 86, 79, 73, 68, 64, // 11
        64, 68, 73, 79, 79, 79,  79,  79,  79,  79, 79, 79, 79, 73, 68, 64, // 12
        64, 68, 73, 73, 73, 73,  73,  73,  73,  73, 73, 73, 73, 73, 68, 64, // 13
        64, 68, 68, 68, 68, 68,  68,  68,  68,  68, 68, 68, 68, 68, 68, 64, // 14
        64, 64, 64, 64, 64, 64,  64,  64,  64,  64, 64, 64, 64, 64, 64, 64  // 15
    };

    static anvil::Region region;
};

anvil::Region RegionFixture::region = anvil::Region();

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

TEST_F(RegionFixture, getHeightMap)
{
    anvil::HeightMap heightmap = region.getHeightMap(-2, -2);

    EXPECT_EQ(expectedHeights, heightmap.getData());
}
