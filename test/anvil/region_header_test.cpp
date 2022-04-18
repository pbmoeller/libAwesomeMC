// AwesomeMC
#include <AwesomeMC/anvil/region_header.hpp>
#include <AwesomeMC/anvil/chunk_info.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(RegionHeader, Constructor)
{
    const amc::ChunkInfo defaultInfo;
    amc::RegionHeader regionHeader;

    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_TRUE(regionHeader.getChunkInfoAt(i) == defaultInfo);
    }
}

TEST(RegionHeader, Constructor_2)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Check
    amc::RegionHeader regionHeader(*info);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
    EXPECT_EQ(amc::ChunkCount, static_cast<int>(regionHeader.getRegionCount()));

    delete info;
}

TEST(RegionHeader, CopyConstructor)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderA.getRegionCount()));

    // Test Copy
    amc::RegionHeader regionHeaderB(regionHeaderA);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderB.getRegionCount()));

    // Test empty copy
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD(regionHeaderC);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0, static_cast<int>(regionHeaderD.getChunkInfoAt(i).getOffset()));
        EXPECT_EQ(0, static_cast<int>(regionHeaderD.getChunkInfoAt(i).getLength()));
        EXPECT_EQ(0, static_cast<int>(regionHeaderD.getChunkInfoAt(i).getTimestamp()));
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, static_cast<int>(regionHeaderD.getRegionCount()));

    delete info;
}

TEST(RegionHeader, MoveConstructor)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderA.getRegionCount()));

    // Test Move
    amc::RegionHeader regionHeaderB(std::move(regionHeaderA));
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderB.getRegionCount()));

    // Test empty move
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD(std::move(regionHeaderC));
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, static_cast<int>(regionHeaderD.getRegionCount()));

    delete info;
}

TEST(RegionHeader, CopyAssignment)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderA.getRegionCount()));

    // Test Copy assignment
    amc::RegionHeader regionHeaderB = regionHeaderA;
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderB.getRegionCount()));

    // Test empty copy assignment
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD = regionHeaderC;
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, static_cast<int>(regionHeaderD.getRegionCount()));

    delete info;
}

TEST(RegionHeader, MoveAssignment)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderA.getRegionCount()));

    // Test Move assignment
    amc::RegionHeader regionHeaderB = std::move(regionHeaderA);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeaderB.getRegionCount()));

    // Test empty move assignment
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD = std::move(regionHeaderC);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0u, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, static_cast<int>(regionHeaderD.getRegionCount()));

    delete info;
}

TEST(RegionHeader, Equal)
{
    amc::RegionHeader regionHeaderA;
    amc::RegionHeader regionHeaderB;

    EXPECT_TRUE(regionHeaderA == regionHeaderA);
    EXPECT_TRUE(regionHeaderA == regionHeaderB);

    regionHeaderB.setChunkInfoAt(0, amc::ChunkInfo(1, 0, 0, amc::CompressionType::GZip));
    EXPECT_FALSE(regionHeaderA == regionHeaderB);
}

TEST(RegionHeader, NotEqual)
{
    amc::RegionHeader regionHeaderA;
    amc::RegionHeader regionHeaderB;

    EXPECT_FALSE(regionHeaderA != regionHeaderA);
    EXPECT_FALSE(regionHeaderA != regionHeaderB);

    regionHeaderB.setChunkInfoAt(0, amc::ChunkInfo(1, 0, 0, amc::CompressionType::GZip));
    EXPECT_TRUE(regionHeaderA != regionHeaderB);
}

TEST(RegionHeader, getRegionCount)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, static_cast<int>(regionHeader.getRegionCount()));

    regionHeader.setChunkInfoAt(1, amc::ChunkInfo(2, 2, 2, amc::CompressionType::GZip));
    EXPECT_EQ(1, static_cast<int>(regionHeader.getRegionCount()));
}

TEST(RegionHeader, getRegionData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(RegionHeader, getChunkInfo)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Check #1
    amc::RegionHeader regionHeader(*info);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        ASSERT_EQ((*info)[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        ASSERT_EQ((*info)[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        ASSERT_EQ((*info)[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        ASSERT_EQ((*info)[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeader.getRegionCount()));

    // Check #2
    const std::array<amc::ChunkInfo, amc::ChunkCount> *info2 = &(regionHeader.getChunkInfo());
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      (*info2)[i].getOffset());
        EXPECT_EQ((*info)[i].getLength(),      (*info2)[i].getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   (*info2)[i].getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), (*info2)[i].getCompression());
    }

    delete info;
}

TEST(RegionHeader, getChunkInfoAt)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, static_cast<int>(regionHeader.getRegionCount()));

    amc::ChunkInfo info = regionHeader.getChunkInfoAt(10);
    EXPECT_EQ(0u, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(0u, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(0u, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::GZip, regionHeader.getChunkInfoAt(10).getCompression());

    regionHeader.setChunkInfoAt(10, amc::ChunkInfo(2, 4, 6, amc::CompressionType::Zlib));
    EXPECT_EQ(1, static_cast<int>(regionHeader.getRegionCount()));

    info = regionHeader.getChunkInfoAt(10);
    EXPECT_EQ(2u, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4u, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6u, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, regionHeader.getChunkInfoAt(10).getCompression());
}

TEST(RegionHeader, getChunkInfoAt_const)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, static_cast<int>(regionHeader.getRegionCount()));

    const amc::RegionHeader regionHeaderB = regionHeader;
    amc::ChunkInfo info = regionHeaderB.getChunkInfoAt(10);
    EXPECT_EQ(0u, regionHeaderB.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(0u, regionHeaderB.getChunkInfoAt(10).getLength());
    EXPECT_EQ(0u, regionHeaderB.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::GZip, regionHeaderB.getChunkInfoAt(10).getCompression());

    regionHeader.setChunkInfoAt(10, amc::ChunkInfo(2, 4, 6, amc::CompressionType::Zlib));
    EXPECT_EQ(1, static_cast<int>(regionHeader.getRegionCount()));

    const amc::RegionHeader regionHeaderC = regionHeader;
    info = regionHeaderC.getChunkInfoAt(10);
    EXPECT_EQ(2u, regionHeaderC.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4u, regionHeaderC.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6u, regionHeaderC.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, regionHeaderC.getChunkInfoAt(10).getCompression());
}

TEST(RegionHeader, setChunkInfo)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Check #1
    amc::RegionHeader regionHeader;
    regionHeader.setChunkInfo(*info);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        ASSERT_EQ((*info)[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        ASSERT_EQ((*info)[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        ASSERT_EQ((*info)[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        ASSERT_EQ((*info)[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, static_cast<int>(regionHeader.getRegionCount()));

    // Check #2
    const std::array<amc::ChunkInfo, amc::ChunkCount> *info2 = &(regionHeader.getChunkInfo());
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      (*info2)[i].getOffset());
        EXPECT_EQ((*info)[i].getLength(),      (*info2)[i].getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   (*info2)[i].getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), (*info2)[i].getCompression());
    }

    delete info;
}

TEST(RegionHeader, setChunkInfoAt)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0u, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(10, amc::ChunkInfo(2, 4, 6, amc::CompressionType::Zlib));
    EXPECT_EQ(2u, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4u, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6u, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, regionHeader.getChunkInfoAt(10).getCompression());
    EXPECT_EQ(1, static_cast<int>(regionHeader.getRegionCount()));

    regionHeader.setChunkInfoAt(20, amc::ChunkInfo(4, 8, 12, amc::CompressionType::Uncompressed));
    EXPECT_EQ(4u, regionHeader.getChunkInfoAt(20).getOffset());
    EXPECT_EQ(8u, regionHeader.getChunkInfoAt(20).getLength());
    EXPECT_EQ(12u, regionHeader.getChunkInfoAt(20).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Uncompressed, regionHeader.getChunkInfoAt(20).getCompression());
    EXPECT_EQ(2, static_cast<int>(regionHeader.getRegionCount()));
}