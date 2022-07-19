// AwesomeMC
#include <AwesomeMC/anvil/region.hpp>
#include <AwesomeMC/anvil/heightmap.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <tuple>

const std::string testFolder = "../../../test/testdata/world/";

class RegionFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        
    }

    static void SetUpTestSuite() 
    {
        const std::string filename = testFolder + "libAwesomeMC_TestWorld_1_18_1/region/r.-1.-1.mca";
        region.loadFromFile(filename);
    }

    virtual void TearDown() override
    {

    }

    const std::array<int, amc::BlockCount> expectedHeights = {
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

    const std::vector<int> yCoordinates1 = {-16, 0, 16, 32, 48};
    const std::vector<std::tuple<int, int, std::string>> expectedBlocksRow1 = {
        {-16, -48, "minecraft:white_wool"},
        {-15, -48, "minecraft:orange_wool"},
        {-14, -48, "minecraft:magenta_wool"},
        {-13, -48, "minecraft:light_blue_wool"},
        {-12, -48, "minecraft:yellow_wool"},
        {-11, -48, "minecraft:lime_wool"},
        {-10, -48, "minecraft:pink_wool"},
        {-9,  -48, "minecraft:gray_wool"},
        {-8,  -48, "minecraft:light_gray_wool"},
        {-7,  -48, "minecraft:cyan_wool"},
        {-6,  -48, "minecraft:purple_wool"},
        {-5,  -48, "minecraft:blue_wool"},
        {-4,  -48, "minecraft:brown_wool"},
        {-3,  -48, "minecraft:green_wool"},
        {-2,  -48, "minecraft:red_wool"},
        {-1,  -48, "minecraft:black_wool"}
    };
    const std::vector<int> yCoordinates2 = {0, 16, 32, 48};
    const std::vector<std::tuple<int, int, std::string>> expectedBlocksRow2 = {
        {-16, -47, "minecraft:stone"},
        {-15, -47, "minecraft:granite"},
        {-14, -47, "minecraft:polished_granite"},
        {-13, -47, "minecraft:diorite"},
        {-12, -47, "minecraft:polished_diorite"},
        {-11, -47, "minecraft:andesite"},
        {-10, -47, "minecraft:polished_andesite"},
        {-9,  -47, "minecraft:deepslate"},
        {-8,  -47, "minecraft:polished_deepslate"},
        {-7,  -47, "minecraft:calcite"},
        {-6,  -47, "minecraft:tuff"},
        {-5,  -47, "minecraft:grass_block"},
        {-4,  -47, "minecraft:dripstone_block"},
        {-3,  -47, "minecraft:dirt"},
        {-2,  -47, "minecraft:coarse_dirt"},
        {-1,  -47, "minecraft:podzol"}
    };
    const std::vector<int> yCoordinates16 = {48};
    const std::vector<std::tuple<int, int, std::string>> expectedBlocksRow16 = {
        {-16, -33, "minecraft:white_terracotta"},
        {-15, -33, "minecraft:orange_terracotta"},
        {-14, -33, "minecraft:magenta_terracotta"},
        {-13, -33, "minecraft:light_blue_terracotta"},
        {-12, -33, "minecraft:yellow_terracotta"},
        {-11, -33, "minecraft:lime_terracotta"},
        {-10, -33, "minecraft:pink_terracotta"},
        {-9,  -33, "minecraft:gray_terracotta"},
        {-8,  -33, "minecraft:light_gray_terracotta"},
        {-7,  -33, "minecraft:cyan_terracotta"},
        {-6,  -33, "minecraft:purple_terracotta"},
        {-5,  -33, "minecraft:blue_terracotta"},
        {-4,  -33, "minecraft:brown_terracotta"},
        {-3,  -33, "minecraft:green_terracotta"},
        {-2,  -33, "minecraft:red_terracotta"},
        {-1,  -33, "minecraft:black_terracotta"}
    };

    static amc::Region region;
};

amc::Region RegionFixture::region = amc::Region();

TEST(Region, Constructor)
{
    amc::Region region;
    EXPECT_EQ(0, region.getX());
    EXPECT_EQ(0, region.getZ());
}

TEST(Region, Constructor_2)
{
    amc::Region region(32, 12);
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
    amc::Region region(31, 11);
    EXPECT_EQ(31, region.getX());
    region.setX(5);
    EXPECT_EQ(5, region.getX());
}

TEST(Region, setX)
{
    amc::Region region;
    EXPECT_EQ(0, region.getX());
    region.setX(2);
    EXPECT_EQ(2, region.getX());
}

TEST(Region, getZ)
{
    amc::Region region(31, 11);
    EXPECT_EQ(11, region.getZ());
    region.setZ(4);
    EXPECT_EQ(4, region.getZ());
}

TEST(Region, setZ)
{
    amc::Region region;
    EXPECT_EQ(0, region.getZ());
    region.setZ(1);
    EXPECT_EQ(1, region.getZ());
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

TEST_F(RegionFixture, getBlockAt)
{
    // Test Row 1 Blocks
    for(const int y : yCoordinates1) {
        for(int xOffset = 0; xOffset < 16; ++xOffset) {
            amc::Block block = region.getBlockAt(-16 + xOffset, y, -48);
            auto [expectedX, expectedZ, expectedName] = expectedBlocksRow1[xOffset];
            EXPECT_EQ(block.getX(), expectedX);
            EXPECT_EQ(block.getZ(), expectedZ);
            EXPECT_STREQ(block.getName().c_str(), expectedName.c_str());
        }
    }

    // Test Row 2 Blocks
    for(const int y : yCoordinates2) {
        for(int xOffset = 0; xOffset < 16; ++xOffset) {
            amc::Block block = region.getBlockAt(-16 + xOffset, y, -47);
            auto [expectedX, expectedZ, expectedName] = expectedBlocksRow2[xOffset];
            EXPECT_EQ(block.getX(), expectedX);
            EXPECT_EQ(block.getZ(), expectedZ);
            EXPECT_STREQ(block.getName().c_str(), expectedName.c_str());
        }
    }

    // Test Row 16 Blocks
    for(int xOffset = 0; xOffset < 16; ++xOffset) {
        amc::Block block = region.getBlockAt(-16 + xOffset, yCoordinates16[0], -33);
        auto [expectedX, expectedZ, expectedName] = expectedBlocksRow16[xOffset];
        EXPECT_EQ(block.getX(), expectedX);
        EXPECT_EQ(block.getZ(), expectedZ);
        EXPECT_STREQ(block.getName().c_str(), expectedName.c_str());
    }
}

TEST_F(RegionFixture, getHeightMap)
{
    amc::HeightMap heightmap = region.getHeightMap(-2, -2);

    EXPECT_EQ(expectedHeights, heightmap.getData());
}

TEST(Region, loadFromFile)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, loadPartiallyFromFile)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, loadChunkAt)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, loadAllChunks)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, saveToFile)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, readChunkData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, readRegionHeader)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(Region, validateRegionFilename)
{
    std::string correctFilenames[10] = {
        "r.1.1.mca",
        "r.-1.1.mca",
        "r.1.-1.mca",
        "r.-1.-1.mca",
        "r.100000.-100000.mca",
        "r.0.0.mca",
        "r.0.1.mca",
        "r.1.0.mca",
        "r.-1.0.mca",
        "r.0.-1.mca"
    };
    std::string invalidFilesnames[] = {
        "",
        "a.1.1.mca",
        "r1.1.mca",
        "r.01.1.mca",
        "r.2.3.nbt",
        "r.-2.+3.mca"
    };

    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[0]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[1]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[2]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[3]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[4]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[5]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[6]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[7]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[8]));
    EXPECT_TRUE(amc::Region::validateRegionFilename(correctFilenames[9]));

    EXPECT_FALSE(amc::Region::validateRegionFilename(invalidFilesnames[0]));
    EXPECT_FALSE(amc::Region::validateRegionFilename(invalidFilesnames[1]));
    EXPECT_FALSE(amc::Region::validateRegionFilename(invalidFilesnames[2]));
    EXPECT_FALSE(amc::Region::validateRegionFilename(invalidFilesnames[3]));
    EXPECT_FALSE(amc::Region::validateRegionFilename(invalidFilesnames[4]));
    EXPECT_FALSE(amc::Region::validateRegionFilename(invalidFilesnames[5]));
}

TEST(Region, validateAndParseRegionFilename)
{
    std::string correctFilenames[10] = {
        "r.1.1.mca",
        "r.-1.1.mca",
        "r.1.-1.mca",
        "r.-1.-1.mca",
        "r.100000.-100000.mca",
        "r.0.0.mca",
        "r.0.1.mca",
        "r.1.0.mca",
        "r.-1.0.mca",
        "r.0.-1.mca"
    };
    std::string invalidFilesnames[] = {
        "",
        "a.1.1.mca",
        "r1.1.mca",
        "r.01.1.mca",
        "r.2.3.nbt",
        "r.-2.+3.mca"
    };

    int x = 0;
    int z = 0;

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[0], x, z));
    EXPECT_EQ(x, 1);
    EXPECT_EQ(z, 1);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[1], x, z));
    EXPECT_EQ(x, -1);
    EXPECT_EQ(z, 1);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[2], x, z));
    EXPECT_EQ(x, 1);
    EXPECT_EQ(z, -1);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[3], x, z));
    EXPECT_EQ(x, -1);
    EXPECT_EQ(z, -1);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[4], x, z));
    EXPECT_EQ(x, 100000);
    EXPECT_EQ(z, -100000);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[5], x, z));
    EXPECT_EQ(x, 0);
    EXPECT_EQ(z, 0);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[6], x, z));
    EXPECT_EQ(x, 0);
    EXPECT_EQ(z, 1);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[7], x, z));
    EXPECT_EQ(x, 1);
    EXPECT_EQ(z, 0);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[8], x, z));
    EXPECT_EQ(x, -1);
    EXPECT_EQ(z, 0);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_TRUE(amc::Region::validateAndParseRegionFilename(correctFilenames[9], x, z));
    EXPECT_EQ(x, 0);
    EXPECT_EQ(z, -1);

    // Invalid file names
    x = INT_MAX;
    z = INT_MAX;
    EXPECT_FALSE(amc::Region::validateAndParseRegionFilename(invalidFilesnames[0], x, z));
    EXPECT_EQ(x, INT_MAX);
    EXPECT_EQ(z, INT_MAX);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_FALSE(amc::Region::validateAndParseRegionFilename(invalidFilesnames[1], x, z));
    EXPECT_EQ(x, INT_MAX);
    EXPECT_EQ(z, INT_MAX);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_FALSE(amc::Region::validateAndParseRegionFilename(invalidFilesnames[2], x, z));
    EXPECT_EQ(x, INT_MAX);
    EXPECT_EQ(z, INT_MAX);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_FALSE(amc::Region::validateAndParseRegionFilename(invalidFilesnames[3], x, z));
    EXPECT_EQ(x, INT_MAX);
    EXPECT_EQ(z, INT_MAX);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_FALSE(amc::Region::validateAndParseRegionFilename(invalidFilesnames[4], x, z));
    EXPECT_EQ(x, INT_MAX);
    EXPECT_EQ(z, INT_MAX);

    x = INT_MAX;
    z = INT_MAX;
    EXPECT_FALSE(amc::Region::validateAndParseRegionFilename(invalidFilesnames[5], x, z));
    EXPECT_EQ(x, INT_MAX);
    EXPECT_EQ(z, INT_MAX);

}
