// AwesomeMC
#include <AwesomeMC/anvil/region_header.hpp>
#include <AwesomeMC/anvil/chunk_info.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ReagionHeader, Constructor)
{
    const amc::ChunkInfo defaultInfo;
    amc::RegionHeader regionHeader;

    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_TRUE(regionHeader.getChunkInfoAt(i) == defaultInfo);
    }
}

TEST(ReagionHeader, Constructor_2)
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

TEST(ReagionHeader, CopyConstructor)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, regionHeaderA.getRegionCount());

    // Test Copy
    amc::RegionHeader regionHeaderB(regionHeaderA);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty copy
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD(regionHeaderC);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, MoveConstructor)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, regionHeaderA.getRegionCount());

    // Test Move
    amc::RegionHeader regionHeaderB(std::move(regionHeaderA));
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty move
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD(std::move(regionHeaderC));
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, CopyAssignment)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, regionHeaderA.getRegionCount());

    // Test Copy assignment
    amc::RegionHeader regionHeaderB = regionHeaderA;
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty copy assignment
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD = regionHeaderC;
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, MoveAssignment)
{
    // Init test data
    std::array<amc::ChunkInfo, amc::ChunkCount> *info = new std::array<amc::ChunkInfo, amc::ChunkCount>();
    for(int i = 0; i < amc::ChunkCount; ++i) {
        (*info)[i] = amc::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, amc::CompressionType::GZip);
    }

    // Init A
    amc::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(amc::ChunkCount, regionHeaderA.getRegionCount());

    // Test Move assignment
    amc::RegionHeader regionHeaderB = std::move(regionHeaderA);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(amc::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty move assignment
    amc::RegionHeader regionHeaderC;
    amc::RegionHeader regionHeaderD = std::move(regionHeaderC);
    for(int i = 0; i < amc::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(amc::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, Equal)
{
    amc::RegionHeader regionHeaderA;
    amc::RegionHeader regionHeaderB;

    EXPECT_TRUE(regionHeaderA == regionHeaderA);
    EXPECT_TRUE(regionHeaderA == regionHeaderB);

    regionHeaderB.setChunkInfoAt(0, amc::ChunkInfo(1, 0, 0, amc::CompressionType::GZip));
    EXPECT_FALSE(regionHeaderA == regionHeaderB);
}

TEST(ReagionHeader, NotEqual)
{
    amc::RegionHeader regionHeaderA;
    amc::RegionHeader regionHeaderB;

    EXPECT_FALSE(regionHeaderA != regionHeaderA);
    EXPECT_FALSE(regionHeaderA != regionHeaderB);

    regionHeaderB.setChunkInfoAt(0, amc::ChunkInfo(1, 0, 0, amc::CompressionType::GZip));
    EXPECT_TRUE(regionHeaderA != regionHeaderB);
}

TEST(ReagionHeader, getRegionCount)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(1, amc::ChunkInfo(2, 2, 2, amc::CompressionType::GZip));
    EXPECT_EQ(1, regionHeader.getRegionCount());
}

TEST(ReagionHeader, getRegionData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ReagionHeader, getChunkInfo)
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
    ASSERT_EQ(amc::ChunkCount, regionHeader.getRegionCount());

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

TEST(ReagionHeader, getChunkInfoAt)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    amc::ChunkInfo info = regionHeader.getChunkInfoAt(10);
    EXPECT_EQ(0, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(0, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(0, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::GZip, regionHeader.getChunkInfoAt(10).getCompression());

    regionHeader.setChunkInfoAt(10, amc::ChunkInfo(2, 4, 6, amc::CompressionType::Zlib));
    EXPECT_EQ(1, regionHeader.getRegionCount());

    info = regionHeader.getChunkInfoAt(10);
    EXPECT_EQ(2, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, regionHeader.getChunkInfoAt(10).getCompression());
}

TEST(ReagionHeader, getChunkInfoAt_const)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    const amc::RegionHeader regionHeaderB = regionHeader;
    amc::ChunkInfo info = regionHeaderB.getChunkInfoAt(10);
    EXPECT_EQ(0, regionHeaderB.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(0, regionHeaderB.getChunkInfoAt(10).getLength());
    EXPECT_EQ(0, regionHeaderB.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::GZip, regionHeaderB.getChunkInfoAt(10).getCompression());

    regionHeader.setChunkInfoAt(10, amc::ChunkInfo(2, 4, 6, amc::CompressionType::Zlib));
    EXPECT_EQ(1, regionHeader.getRegionCount());

    const amc::RegionHeader regionHeaderC = regionHeader;
    info = regionHeaderC.getChunkInfoAt(10);
    EXPECT_EQ(2, regionHeaderC.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4, regionHeaderC.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6, regionHeaderC.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, regionHeaderC.getChunkInfoAt(10).getCompression());
}

TEST(ReagionHeader, setChunkInfo)
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
    ASSERT_EQ(amc::ChunkCount, regionHeader.getRegionCount());

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

TEST(ReagionHeader, setChunkInfoAt)
{
    amc::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(10, amc::ChunkInfo(2, 4, 6, amc::CompressionType::Zlib));
    EXPECT_EQ(2, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, regionHeader.getChunkInfoAt(10).getCompression());
    EXPECT_EQ(1, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(20, amc::ChunkInfo(4, 8, 12, amc::CompressionType::Uncompressed));
    EXPECT_EQ(4, regionHeader.getChunkInfoAt(20).getOffset());
    EXPECT_EQ(8, regionHeader.getChunkInfoAt(20).getLength());
    EXPECT_EQ(12, regionHeader.getChunkInfoAt(20).getTimestamp());
    EXPECT_EQ(amc::CompressionType::Uncompressed, regionHeader.getChunkInfoAt(20).getCompression());
    EXPECT_EQ(2, regionHeader.getRegionCount());
}