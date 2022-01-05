// AwesomeMC
#include <AwesomeMC/util/conversion.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <vector>

TEST(conversion, convertCoordinates_Block2Region)
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
        util::convertCoordinates_Block2Region(blockCoordinates[i][0],
                                              blockCoordinates[i][1],
                                              blockCoordinates[i][2],
                                              regionX,
                                              regionZ);
        EXPECT_EQ(regionX, regionCoordinates[i][0]);
        EXPECT_EQ(regionZ, regionCoordinates[i][1]);
    }
}

TEST(conversion, convertCoordinates_Block2Chunk)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}