// AwesomeMC
#include <AwesomeMC/anvil/chunk_info.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ChunkInfo, Constructor)
{
    amc::ChunkInfo chunkInfo;

    EXPECT_EQ(0u, chunkInfo.getOffset());
    EXPECT_EQ(0u, chunkInfo.getLength());
    EXPECT_EQ(0u, chunkInfo.getTimestamp());
    EXPECT_EQ(amc::CompressionType::GZip, chunkInfo.getCompression());
}

TEST(ChunkInfo, Constructor_2)
{
    amc::ChunkInfo chunkInfo(345, 20, 0x12345678, amc::CompressionType::Zlib);

    EXPECT_EQ(345u, chunkInfo.getOffset());
    EXPECT_EQ(20u, chunkInfo.getLength());
    EXPECT_EQ(0x12345678u, chunkInfo.getTimestamp());
    EXPECT_EQ(amc::CompressionType::Zlib, chunkInfo.getCompression());
}

TEST(ChunkInfo, CopyConstructor)
{
    // Init A
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(amc::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Copy
    amc::ChunkInfo chunkInfoB(chunkInfoA);
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, MoveConstructor)
{
    // Init A
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(amc::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Move
    amc::ChunkInfo chunkInfoB(std::move(chunkInfoA));
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, CopyAssignment)
{
    // Init A
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(amc::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Copy
    amc::ChunkInfo chunkInfoB = chunkInfoA;
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, MoveAssignment)
{
    // Init A
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(amc::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Move
    amc::ChunkInfo chunkInfoB = std::move(chunkInfoA);
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, Equal)
{
    // Init
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoC(346, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoD(345, 21, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoE(345, 20, 0x12345679, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoF(345, 20, 0x12345678, amc::CompressionType::GZip);
    amc::ChunkInfo chunkInfoG;

    // Check
    EXPECT_TRUE(chunkInfoA == chunkInfoB);
    EXPECT_FALSE(chunkInfoA == chunkInfoC);
    EXPECT_FALSE(chunkInfoA == chunkInfoD);
    EXPECT_FALSE(chunkInfoA == chunkInfoE);
    EXPECT_FALSE(chunkInfoA == chunkInfoF);
    EXPECT_FALSE(chunkInfoA == chunkInfoG);
}

TEST(ChunkInfo, NotEqual)
{
    // Init
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoC(346, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoD(345, 21, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoE(345, 20, 0x12345679, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoF(345, 20, 0x12345678, amc::CompressionType::GZip);
    amc::ChunkInfo chunkInfoG;

    // Check
    EXPECT_FALSE(chunkInfoA != chunkInfoB);
    EXPECT_TRUE(chunkInfoA != chunkInfoC);
    EXPECT_TRUE(chunkInfoA != chunkInfoD);
    EXPECT_TRUE(chunkInfoA != chunkInfoE);
    EXPECT_TRUE(chunkInfoA != chunkInfoF);
    EXPECT_TRUE(chunkInfoA != chunkInfoG);
}

TEST(ChunkInfo, isEmpty)
{
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(0, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoC;

    EXPECT_FALSE(chunkInfoA.isEmpty());
    EXPECT_TRUE(chunkInfoB.isEmpty());
    EXPECT_TRUE(chunkInfoC.isEmpty());
}

TEST(ChunkInfo, getOffset)
{
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(0, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getOffset(), 345u);
    EXPECT_EQ(chunkInfoB.getOffset(), 0u);
    EXPECT_EQ(chunkInfoC.getOffset(), 0u);
}

TEST(ChunkInfo, setOffset)
{
    amc::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getOffset(), 0u);
    chunkInfo.setOffset(8u);
    EXPECT_EQ(chunkInfo.getOffset(), 8u);
}

TEST(ChunkInfo, getLength)
{
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(0, 0, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getLength(), 20u);
    EXPECT_EQ(chunkInfoB.getLength(), 0u);
    EXPECT_EQ(chunkInfoC.getLength(), 0u);
}

TEST(ChunkInfo, setLength)
{
    amc::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getLength(), 0u);
    chunkInfo.setLength(8u);
    EXPECT_EQ(chunkInfo.getLength(), 8u);
}

TEST(ChunkInfo, getTimestamp)
{
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(0, 0, 0, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getTimestamp(), 0x12345678u);
    EXPECT_EQ(chunkInfoB.getTimestamp(), 0u);
    EXPECT_EQ(chunkInfoC.getTimestamp(), 0u);
}

TEST(ChunkInfo, setTimestamp)
{
    amc::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getTimestamp(), 0u);
    chunkInfo.setTimestamp(8u);
    EXPECT_EQ(chunkInfo.getTimestamp(), 8u);
}

TEST(ChunkInfo, getCompression)
{
    amc::ChunkInfo chunkInfoA(345, 20, 0x12345678, amc::CompressionType::Zlib);
    amc::ChunkInfo chunkInfoB(0, 0, 0, amc::CompressionType::GZip);
    amc::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getCompression(), amc::CompressionType::Zlib);
    EXPECT_EQ(chunkInfoB.getCompression(), amc::CompressionType::GZip);
    EXPECT_EQ(chunkInfoC.getCompression(), amc::CompressionType::GZip);
}

TEST(ChunkInfo, setCompression)
{
    amc::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getCompression(), amc::CompressionType::GZip);
    chunkInfo.setCompression(amc::CompressionType::Zlib);
    EXPECT_EQ(chunkInfo.getCompression(), amc::CompressionType::Zlib);
}
