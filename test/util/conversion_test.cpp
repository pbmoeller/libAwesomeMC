// AwesomeMC
#include <AwesomeMC/util/conversion.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <vector>
#include <limits>

TEST(conversion, isValidWorldCoordinate)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, isValidRegionCoordinate)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, isValidChunkCoordinate)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, isValidSectionCoordinate)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, xzFromChunkIndex)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(conversion, xzFromChunkIndex_tuple)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}
