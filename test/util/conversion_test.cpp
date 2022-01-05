// AwesomeMC
#include <AwesomeMC/util/conversion.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <vector>

TEST(conversion, convertBlockWorld2Region)
{
    // Testdata
    const std::vector<std::vector<int>> blockCoordinates = {
        { 0, 0, 0 },
        { -1, 0, 0 },
        { -1, 0, -1 },
        { 0, 0, -1 },
        { 512, 0, 0 },
        { -1456, 0, 0 },
        { 12000, 0, 1023 },
        { 1024, 0, 666 }
    };

    // Checkdata
    const std::vector<std::vector<int>> regionCoordinates = {
        { 0, 0 },
        { -1, 0 },
        { -1, -1 },
        { 0, -1 },
        { 1, 0 },
        { -3, 0 },
        { 23, 1 },
        { 2, 1 }
    };

    // Tests
    ASSERT_EQ(blockCoordinates.size(), regionCoordinates.size());
    for(int i = 0; i < blockCoordinates.size(); ++i) {
        int regionX = std::numeric_limits<int>::max();
        int regionZ = std::numeric_limits<int>::max();
        util::convertBlockWorld2Region(blockCoordinates[i][0],
                                       blockCoordinates[i][1],
                                       blockCoordinates[i][2],
                                       regionX,
                                       regionZ);
        EXPECT_EQ(regionX, regionCoordinates[i][0]);
        EXPECT_EQ(regionZ, regionCoordinates[i][1]);
    }
}

// Testdata
const std::vector<std::vector<int>> blockCoordinatesWorld = {
    { 0, 68, 0 },
    { 59, 63, 39 },
    { -16, 68, 23 },
    { 0, 69, -1 },
    { -1, 69, -1 },
    { -1, 69, 0 },
    { 0, 67, -16 }
};

// Checkdata
const std::vector<std::vector<int>> blockCoordinatesChunk = {
    { 0, 4, 0, 0, 4, 0 },
    { 11, 15, 7, 3, 3, 2 },
    { 0, 4, 7, -1, 4, 1 },
    { 0, 5, 15, 0, 4, -1 },
    { 15, 5, 15, -1, 4, -1 },
    { 15, 5, 0, -1, 4, 0 },
    { 0, 3, 0, 0, 4, -1 },
};

TEST(conversion, convertBlockWorld2BlockChunk)
{
    ASSERT_EQ(blockCoordinatesWorld.size(), blockCoordinatesChunk.size());
    for(int i = 0; i < blockCoordinatesWorld.size(); ++i) {
        int bX = 0; int bY = 0; int bZ = 0;
        int cX = 0; int cY = 0; int cZ = 0;
        util::convertBlockWorld2BlockChunk(blockCoordinatesWorld[i][0],
                                           blockCoordinatesWorld[i][1],
                                           blockCoordinatesWorld[i][2],
                                           bX, bY, bZ, cX, cY, cZ);
        EXPECT_EQ(bX, blockCoordinatesChunk[i][0]);
        EXPECT_EQ(bY, blockCoordinatesChunk[i][1]);
        EXPECT_EQ(bZ, blockCoordinatesChunk[i][2]);
        EXPECT_EQ(cX, blockCoordinatesChunk[i][3]);
        EXPECT_EQ(cY, blockCoordinatesChunk[i][4]);
        EXPECT_EQ(cZ, blockCoordinatesChunk[i][5]);
    }
}

TEST(conversion, convertBlockWorld2BlockChunk_2)
{
    ASSERT_EQ(blockCoordinatesWorld.size(), blockCoordinatesChunk.size());
    for(int i = 0; i < blockCoordinatesWorld.size(); ++i) {
        int bX = 0; int bY = 0; int bZ = 0;
        util::convertBlockWorld2BlockChunk(blockCoordinatesWorld[i][0],
                                           blockCoordinatesWorld[i][1],
                                           blockCoordinatesWorld[i][2],
                                           bX, bY, bZ);
        EXPECT_EQ(bX, blockCoordinatesChunk[i][0]);
        EXPECT_EQ(bY, blockCoordinatesChunk[i][1]);
        EXPECT_EQ(bZ, blockCoordinatesChunk[i][2]);
    }
}

TEST(conversion, convertBlockWorld2Chunk)
{
    ASSERT_EQ(blockCoordinatesWorld.size(), blockCoordinatesChunk.size());
    for(int i = 0; i < blockCoordinatesWorld.size(); ++i) {
        int bX = 0; int bY = 0; int bZ = 0;
        int cX = 0; int cY = 0; int cZ = 0;
        util::convertBlockWorld2Chunk(blockCoordinatesWorld[i][0],
                                      blockCoordinatesWorld[i][1],
                                      blockCoordinatesWorld[i][2],
                                      cX, cY, cZ);
        EXPECT_EQ(cX, blockCoordinatesChunk[i][3]);
        EXPECT_EQ(cY, blockCoordinatesChunk[i][4]);
        EXPECT_EQ(cZ, blockCoordinatesChunk[i][5]);
    }
}