// AwesomeMC
#include <AwesomeMC/anvil/region_header.hpp>
#include <AwesomeMC/anvil/chunk_info.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ReagionHeader, Constructor)
{
    const anvil::ChunkInfo defaultInfo;
    anvil::RegionHeader regionHeader;

    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_TRUE(regionHeader.getChunkInfoAt(i) == defaultInfo);
    }
}

TEST(ReagionHeader, Constructor_2)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Check
    anvil::RegionHeader regionHeader(*info);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
    EXPECT_EQ(anvil::ChunkCount, regionHeader.getRegionCount());

    delete info;
}

TEST(ReagionHeader, CopyConstructor)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Init A
    anvil::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(anvil::ChunkCount, regionHeaderA.getRegionCount());

    // Test Copy
    anvil::RegionHeader regionHeaderB(regionHeaderA);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(anvil::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty copy
    anvil::RegionHeader regionHeaderC;
    anvil::RegionHeader regionHeaderD(regionHeaderC);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, MoveConstructor)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Init A
    anvil::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(anvil::ChunkCount, regionHeaderA.getRegionCount());

    // Test Move
    anvil::RegionHeader regionHeaderB(std::move(regionHeaderA));
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(anvil::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty move
    anvil::RegionHeader regionHeaderC;
    anvil::RegionHeader regionHeaderD(std::move(regionHeaderC));
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, CopyAssignment)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Init A
    anvil::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(anvil::ChunkCount, regionHeaderA.getRegionCount());

    // Test Copy assignment
    anvil::RegionHeader regionHeaderB = regionHeaderA;
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(anvil::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty copy assignment
    anvil::RegionHeader regionHeaderC;
    anvil::RegionHeader regionHeaderD = regionHeaderC;
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, MoveAssignment)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Init A
    anvil::RegionHeader regionHeaderA(*info);
    ASSERT_EQ(anvil::ChunkCount, regionHeaderA.getRegionCount());

    // Test Move assignment
    anvil::RegionHeader regionHeaderB = std::move(regionHeaderA);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      regionHeaderB.getChunkInfoAt(i).getOffset());
        EXPECT_EQ((*info)[i].getLength(),      regionHeaderB.getChunkInfoAt(i).getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   regionHeaderB.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), regionHeaderB.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(anvil::ChunkCount, regionHeaderB.getRegionCount());

    // Test empty move assignment
    anvil::RegionHeader regionHeaderC;
    anvil::RegionHeader regionHeaderD = std::move(regionHeaderC);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getLength());
        EXPECT_EQ(0, regionHeaderD.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, regionHeaderD.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(0, regionHeaderD.getRegionCount());

    delete info;
}

TEST(ReagionHeader, Equal)
{
    anvil::RegionHeader regionHeaderA;
    anvil::RegionHeader regionHeaderB;

    EXPECT_TRUE(regionHeaderA == regionHeaderA);
    EXPECT_TRUE(regionHeaderA == regionHeaderB);

    regionHeaderB.setChunkInfoAt(0, anvil::ChunkInfo(1, 0, 0, anvil::ChunkInfo::CompressionType::GZip));
    EXPECT_FALSE(regionHeaderA == regionHeaderB);
}

TEST(ReagionHeader, NotEqual)
{
    anvil::RegionHeader regionHeaderA;
    anvil::RegionHeader regionHeaderB;

    EXPECT_FALSE(regionHeaderA != regionHeaderA);
    EXPECT_FALSE(regionHeaderA != regionHeaderB);

    regionHeaderB.setChunkInfoAt(0, anvil::ChunkInfo(1, 0, 0, anvil::ChunkInfo::CompressionType::GZip));
    EXPECT_TRUE(regionHeaderA != regionHeaderB);
}

TEST(ReagionHeader, getRegionCount)
{
    anvil::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(1, anvil::ChunkInfo(2, 2, 2, anvil::ChunkInfo::CompressionType::GZip));
    EXPECT_EQ(1, regionHeader.getRegionCount());
}

TEST(ReagionHeader, getRegionData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ReagionHeader, getChunkInfo)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Check #1
    anvil::RegionHeader regionHeader(*info);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        ASSERT_EQ((*info)[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        ASSERT_EQ((*info)[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        ASSERT_EQ((*info)[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        ASSERT_EQ((*info)[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(anvil::ChunkCount, regionHeader.getRegionCount());

    // Check #2
    const std::array<anvil::ChunkInfo, anvil::ChunkCount> *info2 = &(regionHeader.getChunkInfo());
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      (*info2)[i].getOffset());
        EXPECT_EQ((*info)[i].getLength(),      (*info2)[i].getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   (*info2)[i].getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), (*info2)[i].getCompression());
    }

    delete info;
}

TEST(ReagionHeader, getChunkInfoAt)
{
    anvil::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    anvil::ChunkInfo info = regionHeader.getChunkInfoAt(10);
    EXPECT_EQ(0, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(0, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(0, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, regionHeader.getChunkInfoAt(10).getCompression());

    regionHeader.setChunkInfoAt(10, anvil::ChunkInfo(2, 4, 6, anvil::ChunkInfo::CompressionType::Zlib));
    EXPECT_EQ(1, regionHeader.getRegionCount());

    info = regionHeader.getChunkInfoAt(10);
    EXPECT_EQ(2, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::Zlib, regionHeader.getChunkInfoAt(10).getCompression());
}

TEST(ReagionHeader, getChunkInfoAt_const)
{
    anvil::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    const anvil::RegionHeader regionHeaderB = regionHeader;
    anvil::ChunkInfo info = regionHeaderB.getChunkInfoAt(10);
    EXPECT_EQ(0, regionHeaderB.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(0, regionHeaderB.getChunkInfoAt(10).getLength());
    EXPECT_EQ(0, regionHeaderB.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, regionHeaderB.getChunkInfoAt(10).getCompression());

    regionHeader.setChunkInfoAt(10, anvil::ChunkInfo(2, 4, 6, anvil::ChunkInfo::CompressionType::Zlib));
    EXPECT_EQ(1, regionHeader.getRegionCount());

    const anvil::RegionHeader regionHeaderC = regionHeader;
    info = regionHeaderC.getChunkInfoAt(10);
    EXPECT_EQ(2, regionHeaderC.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4, regionHeaderC.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6, regionHeaderC.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::Zlib, regionHeaderC.getChunkInfoAt(10).getCompression());
}

TEST(ReagionHeader, setChunkInfo)
{
    // Init test data
    std::array<anvil::ChunkInfo, anvil::ChunkCount> *info = new std::array<anvil::ChunkInfo, anvil::ChunkCount>();
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        (*info)[i] = anvil::ChunkInfo((i + 1) * 2, (i + 1), (i + 1) * 3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Check #1
    anvil::RegionHeader regionHeader;
    regionHeader.setChunkInfo(*info);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        ASSERT_EQ((*info)[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        ASSERT_EQ((*info)[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        ASSERT_EQ((*info)[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        ASSERT_EQ((*info)[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
    ASSERT_EQ(anvil::ChunkCount, regionHeader.getRegionCount());

    // Check #2
    const std::array<anvil::ChunkInfo, anvil::ChunkCount> *info2 = &(regionHeader.getChunkInfo());
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ((*info)[i].getOffset(),      (*info2)[i].getOffset());
        EXPECT_EQ((*info)[i].getLength(),      (*info2)[i].getLength());
        EXPECT_EQ((*info)[i].getTimestamp(),   (*info2)[i].getTimestamp());
        EXPECT_EQ((*info)[i].getCompression(), (*info2)[i].getCompression());
    }

    delete info;
}

TEST(ReagionHeader, setChunkInfoAt)
{
    anvil::RegionHeader regionHeader;
    ASSERT_EQ(0, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(10, anvil::ChunkInfo(2, 4, 6, anvil::ChunkInfo::CompressionType::Zlib));
    EXPECT_EQ(2, regionHeader.getChunkInfoAt(10).getOffset());
    EXPECT_EQ(4, regionHeader.getChunkInfoAt(10).getLength());
    EXPECT_EQ(6, regionHeader.getChunkInfoAt(10).getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::Zlib, regionHeader.getChunkInfoAt(10).getCompression());
    EXPECT_EQ(1, regionHeader.getRegionCount());

    regionHeader.setChunkInfoAt(20, anvil::ChunkInfo(4, 8, 12, anvil::ChunkInfo::CompressionType::Uncompressed));
    EXPECT_EQ(4, regionHeader.getChunkInfoAt(20).getOffset());
    EXPECT_EQ(8, regionHeader.getChunkInfoAt(20).getLength());
    EXPECT_EQ(12, regionHeader.getChunkInfoAt(20).getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::Uncompressed, regionHeader.getChunkInfoAt(20).getCompression());
    EXPECT_EQ(2, regionHeader.getRegionCount());
}