// AwesomeMC
#include <AwesomeMC/util/conversion.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <vector>
#include <limits>

TEST(conversion, isValidWorldCoordinate)
{
    // Test valid coordinates
    EXPECT_TRUE(amc::isValidWorldCoordinate(0, 0, 0));
    EXPECT_TRUE(amc::isValidWorldCoordinate(120000, 120, 5131311));

    // Test X Coodinate
    EXPECT_FALSE(amc::isValidWorldCoordinate(-30000000, 0, 0));
    EXPECT_TRUE(amc::isValidWorldCoordinate(-500000, 0, 0));
    EXPECT_TRUE(amc::isValidWorldCoordinate(1250000, 0, 0));
    EXPECT_FALSE(amc::isValidWorldCoordinate(30000000, 0, 0));

    // Test Z Coodinate
    EXPECT_FALSE(amc::isValidWorldCoordinate(0, 0, -30000000));
    EXPECT_TRUE(amc::isValidWorldCoordinate(0, 0, -500000));
    EXPECT_TRUE(amc::isValidWorldCoordinate(0, 0, 2500000));
    EXPECT_FALSE(amc::isValidWorldCoordinate(0, 0, 30000000));

    // Test Y Coodinate
    EXPECT_FALSE(amc::isValidWorldCoordinate(0, -65, 0));
    EXPECT_TRUE(amc::isValidWorldCoordinate(0, -64, 0));
    EXPECT_TRUE(amc::isValidWorldCoordinate(0, 319, 0));
    EXPECT_FALSE(amc::isValidWorldCoordinate(0, 320, 0));
}

TEST(conversion, isValidRegionCoordinate)
{
    // Test valid coordinates
    EXPECT_TRUE(amc::isValidRegionCoordinate(0, 0, 0));
    EXPECT_TRUE(amc::isValidRegionCoordinate(511, 120, 511));

    // Test X Coodinate
    EXPECT_FALSE(amc::isValidRegionCoordinate(-1, 0, 0));
    EXPECT_TRUE(amc::isValidRegionCoordinate(345, 0, 0));
    EXPECT_FALSE(amc::isValidRegionCoordinate(512, 0, 0));

    // Test Z Coodinate
    EXPECT_FALSE(amc::isValidRegionCoordinate(0, 0, -1));
    EXPECT_TRUE(amc::isValidRegionCoordinate(0, 0, 75));
    EXPECT_FALSE(amc::isValidRegionCoordinate(0, 0, 512));

    // Test Y Coodinate
    EXPECT_FALSE(amc::isValidRegionCoordinate(0, -65, 0));
    EXPECT_TRUE(amc::isValidRegionCoordinate(0, -64, 0));
    EXPECT_TRUE(amc::isValidRegionCoordinate(0, 319, 0));
    EXPECT_FALSE(amc::isValidRegionCoordinate(0, 320, 0));
}

TEST(conversion, isValidChunkCoordinate)
{
    // Test valid coordinates
    EXPECT_TRUE(amc::isValidChunkCoordinate(0, 0, 0));
    EXPECT_TRUE(amc::isValidChunkCoordinate(15, 120, 15));
    
    // Test X Coodinate
    EXPECT_FALSE(amc::isValidChunkCoordinate(-1, 0, 0));
    EXPECT_TRUE(amc::isValidChunkCoordinate(5, 0, 0));
    EXPECT_FALSE(amc::isValidChunkCoordinate(16, 0, 0));
    
    // Test Z Coodinate
    EXPECT_FALSE(amc::isValidChunkCoordinate(0, 0, -1));
    EXPECT_TRUE(amc::isValidChunkCoordinate(0, 0, 6));
    EXPECT_FALSE(amc::isValidChunkCoordinate(0, 0, 16));

    // Test Y Coodinate
    EXPECT_FALSE(amc::isValidChunkCoordinate(0, -65, 0));
    EXPECT_TRUE(amc::isValidChunkCoordinate(0, -64, 0));
    EXPECT_TRUE(amc::isValidChunkCoordinate(0, 319, 0));
    EXPECT_FALSE(amc::isValidChunkCoordinate(0, 320, 0));
}

TEST(conversion, isValidSectionCoordinate)
{
    // Test valid coordinates
    EXPECT_TRUE(amc::isValidSectionCoordinate(0, 0, 0));
    EXPECT_TRUE(amc::isValidSectionCoordinate(15, 15, 15));

    // Test X Coordinates
    EXPECT_FALSE(amc::isValidSectionCoordinate(-1, 0, 0));
    EXPECT_TRUE(amc::isValidSectionCoordinate(5, 0, 0));
    EXPECT_FALSE(amc::isValidSectionCoordinate(16, 0, 0));

    // Test Z Coordinates
    EXPECT_FALSE(amc::isValidSectionCoordinate(0, -1, 0));
    EXPECT_TRUE(amc::isValidSectionCoordinate(0, 4, 0));
    EXPECT_FALSE(amc::isValidSectionCoordinate(0, 16, 0));

    // Test Y Coordinates
    EXPECT_FALSE(amc::isValidSectionCoordinate(0, 0, -1));
    EXPECT_TRUE(amc::isValidSectionCoordinate(0, 0, 7));
    EXPECT_FALSE(amc::isValidSectionCoordinate(0, 0, 16));
}

const std::vector<std::vector<int>> blockCoordinates1 = {
    { 0, 0, 0 },
    { -1, 0, 0 },
    { -1, 0, -1 },
    { 0, 0, -1 },
    { 512, 0, 0 },
    { -1456, 0, 0 },
    { 12000, 0, 1023 },
    { 1024, 0, 666 }
};

const std::vector<std::vector<int>> regionCoordinates1 = {
    { 0, 0 },
    { -1, 0 },
    { -1, -1 },
    { 0, -1 },
    { 1, 0 },
    { -3, 0 },
    { 23, 1 },
    { 2, 1 }
};

const std::vector<std::vector<int>> chunkCoordinates1 = {
    { 0, 0 },
    { -1, 0 },
    { -1, -1 },
    { 0, -1 },
    { 32, 0 },
    { -91, 0 },
    { 750, 63 },
    { 64, 41 }
};

const std::vector<std::vector<int>> relativeChunkCoordinates1 = {
    { 0, 0 },
    { 31, 0 },
    { 31, 31 },
    { 0, 31 },
    { 0, 0 },
    { 5, 0 },
    { 14, 31 },
    { 0, 9 }
};

TEST(conversion, convertBlockWorld2Region)
{
    int regionX = std::numeric_limits<int>::max();
    int regionZ = std::numeric_limits<int>::max();
    ASSERT_EQ(blockCoordinates1.size(), regionCoordinates1.size());
    for(size_t i = 0; i < blockCoordinates1.size(); ++i) {
        amc::convertBlockWorld2Region(blockCoordinates1[i][0],
                                      blockCoordinates1[i][2],
                                      regionX,
                                      regionZ);
        EXPECT_EQ(regionX, regionCoordinates1[i][0]);
        EXPECT_EQ(regionZ, regionCoordinates1[i][1]);
    }
}

TEST(conversion, convertBlockWorld2ChunkWorld)
{
    int chunkX = std::numeric_limits<int>::max();
    int chunkZ = std::numeric_limits<int>::max();
    ASSERT_EQ(blockCoordinates1.size(), chunkCoordinates1.size());
    for(size_t i = 0; i < blockCoordinates1.size(); ++i) {
        amc::convertBlockWorld2ChunkWorld(blockCoordinates1[i][0],
                                          blockCoordinates1[i][2],
                                          chunkX,
                                          chunkZ);
        EXPECT_EQ(chunkX, chunkCoordinates1[i][0]);
        EXPECT_EQ(chunkZ, chunkCoordinates1[i][1]);
    }
}

TEST(conversion, convertBlockWorld2ChunkRegion)
{
    int chunkX = std::numeric_limits<int>::max();
    int chunkZ = std::numeric_limits<int>::max();
    ASSERT_EQ(blockCoordinates1.size(), relativeChunkCoordinates1.size());
    for(size_t i = 0; i < blockCoordinates1.size(); ++i) {
        amc::convertBlockWorld2ChunkRegion(blockCoordinates1[i][0],
                                           blockCoordinates1[i][2],
                                           chunkX,
                                           chunkZ);
        EXPECT_EQ(chunkX, relativeChunkCoordinates1[i][0]);
        EXPECT_EQ(chunkZ, relativeChunkCoordinates1[i][1]);
    }
}

const std::vector<std::vector<int>> blockCoordinates2 = {
    { 0, 68, 0 },
    { 59, 63, 39 },
    { -16, 68, 23 },
    { 0, 69, -1 },
    { -1, 69, -1 },
    { -1, 69, 0 },
    { 0, 67, -16 },
    { 513, 67, -456 }
};

const std::vector<std::vector<int>> blockCoordinatesChunk2 = {
    { 0, 4, 0 },
    { 11, 15, 7 },
    { 0, 4, 7 },
    { 0, 5, 15 },
    { 15, 5, 15 },
    { 15, 5, 0 },
    { 0, 3, 0 },
    { 1, 3, 8 }
};

const std::vector<std::vector<int>> blockCoordinatesRegion2 = {
    { 0, 4, 0 },
    { 59, 15, 39 },
    { 496, 4, 23 },
    { 0, 5, 511 },
    { 511, 5, 511 },
    { 511, 5, 0 },
    { 0, 3, 496 },
    { 1, 3, 56 }
};

TEST(conversion, convertBlockWorld2BlockRegion)
{
    int blockRegionX = std::numeric_limits<int>::max();
    int blockRegionZ = std::numeric_limits<int>::max();
    ASSERT_EQ(blockCoordinates2.size(), blockCoordinatesRegion2.size());
    for(size_t i = 0; i < blockCoordinates2.size(); ++i) {
        amc::convertBlockWorld2BlockRegion(blockCoordinates2[i][0],
                                           blockCoordinates2[i][2],
                                           blockRegionX,
                                           blockRegionZ);
        EXPECT_EQ(blockRegionX, blockCoordinatesRegion2[i][0]);
        EXPECT_EQ(blockRegionZ, blockCoordinatesRegion2[i][2]);
    }
}

TEST(conversion, convertBlockWorld2BlockChunk)
{
    int blockChunkX = std::numeric_limits<int>::max();
    int blockChunkZ = std::numeric_limits<int>::max();
    ASSERT_EQ(blockCoordinates2.size(), blockCoordinatesChunk2.size());
    for(size_t i = 0; i < blockCoordinates2.size(); ++i) {
        amc::convertBlockWorld2BlockChunk(blockCoordinates2[i][0],
                                          blockCoordinates2[i][2],
                                          blockChunkX,
                                          blockChunkZ);
        EXPECT_EQ(blockChunkX, blockCoordinatesChunk2[i][0]);
        EXPECT_EQ(blockChunkZ, blockCoordinatesChunk2[i][2]);
    }
}

TEST(conversion, convertBlockWorld2BlockChunk_2)
{
    int blockChunkX = std::numeric_limits<int>::max();
    int blockChunkY = std::numeric_limits<int>::max();
    int blockChunkZ = std::numeric_limits<int>::max();
    ASSERT_EQ(blockCoordinates2.size(), blockCoordinatesChunk2.size());
    for(size_t i = 0; i < blockCoordinates2.size(); ++i) {
        amc::convertBlockWorld2BlockChunk(blockCoordinates2[i][0],
                                          blockCoordinates2[i][1],
                                          blockCoordinates2[i][2],
                                          blockChunkX,
                                          blockChunkY,
                                          blockChunkZ);
        EXPECT_EQ(blockChunkX, blockCoordinatesChunk2[i][0]);
        EXPECT_EQ(blockChunkY, blockCoordinatesChunk2[i][1]);
        EXPECT_EQ(blockChunkZ, blockCoordinatesChunk2[i][2]);
    }
}

TEST(conversion, convertChunkWorld2ChunkRegion)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, convertChunkRegion2ChunkWorld)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, chunkIndexFromXZ)
{
    EXPECT_EQ(0, amc::chunkIndexFromXZ(0, 0));
    EXPECT_EQ(31, amc::chunkIndexFromXZ(31, 0));
    EXPECT_EQ(992, amc::chunkIndexFromXZ(0, 31));
    EXPECT_EQ(1023, amc::chunkIndexFromXZ(31, 31));
}

TEST(conversion, xzFromChunkIndex)
{
    int chunkX = -1;
    int chunkZ = -1;

    amc::xzFromChunkIndex(0, chunkX, chunkZ);
    EXPECT_EQ(0, chunkX);
    EXPECT_EQ(0, chunkZ);
    amc::xzFromChunkIndex(31, chunkX, chunkZ);
    EXPECT_EQ(31, chunkX);
    EXPECT_EQ(0, chunkZ);
    amc::xzFromChunkIndex(992, chunkX, chunkZ);
    EXPECT_EQ(0, chunkX);
    EXPECT_EQ(31, chunkZ);
    amc::xzFromChunkIndex(1023, chunkX, chunkZ);
    EXPECT_EQ(31, chunkX);
    EXPECT_EQ(31, chunkZ);
}

TEST(conversion, xzFromChunkIndex_tuple)
{
    {
        auto [chunkX, chunkZ] = amc::xzFromChunkIndex(0);
        EXPECT_EQ(0, chunkX);
        EXPECT_EQ(0, chunkZ);
    }
    {
        auto [chunkX, chunkZ] = amc::xzFromChunkIndex(31);
        EXPECT_EQ(31, chunkX);
        EXPECT_EQ(0, chunkZ);
    }
    {
        auto [chunkX, chunkZ] = amc::xzFromChunkIndex(992);
        EXPECT_EQ(0, chunkX);
        EXPECT_EQ(31, chunkZ);
    }
    {
        auto [chunkX, chunkZ] = amc::xzFromChunkIndex(1023);
        EXPECT_EQ(31, chunkX);
        EXPECT_EQ(31, chunkZ);
    }
}

// Death Tests (Only Debug)
#ifndef NDEBUG

TEST(conversion, chunkIndexFromXZ_death)
{
    // less
    EXPECT_DEATH(amc::chunkIndexFromXZ(-1, -1), "");
    EXPECT_DEATH(amc::chunkIndexFromXZ(-1, 0), "");
    EXPECT_DEATH(amc::chunkIndexFromXZ(0, -1), "");

    // greater
    EXPECT_DEATH(amc::chunkIndexFromXZ(1023, 1024), "");
    EXPECT_DEATH(amc::chunkIndexFromXZ(1024, 1023), "");
    EXPECT_DEATH(amc::chunkIndexFromXZ(1024, 1024), "");
}

TEST(conversion, xzFromChunkIndex_death)
{
    int chunkX = -1;
    int chunkZ = -1;

    EXPECT_DEATH(amc::xzFromChunkIndex(-1, chunkX, chunkZ), "");
    EXPECT_DEATH(amc::xzFromChunkIndex(1024, chunkX, chunkZ), "");
}

TEST(conversion, xzFromChunkIndex_tuple_death)
{
    EXPECT_DEATH(amc::xzFromChunkIndex(-1), "");
    EXPECT_DEATH(amc::xzFromChunkIndex(1024), "");
}

#endif // DEBUG
