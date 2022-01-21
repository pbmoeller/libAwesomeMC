// AwesomeMC
#include <AwesomeMC/anvil/chunk_info.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ChunkInfo, CompressionType)
{
    EXPECT_EQ(1, static_cast<int>(anvil::ChunkInfo::CompressionType::GZip));
    EXPECT_EQ(2, static_cast<int>(anvil::ChunkInfo::CompressionType::Zlib));
    EXPECT_EQ(3, static_cast<int>(anvil::ChunkInfo::CompressionType::Uncompressed));
}

TEST(ChunkInfo, Constructor)
{
    anvil::ChunkInfo chunkInfo;

    EXPECT_EQ(0u, chunkInfo.getOffset());
    EXPECT_EQ(0u, chunkInfo.getLength());
    EXPECT_EQ(0u, chunkInfo.getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, chunkInfo.getCompression());
}

TEST(ChunkInfo, Constructor_2)
{
    anvil::ChunkInfo chunkInfo(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    EXPECT_EQ(345u, chunkInfo.getOffset());
    EXPECT_EQ(20u, chunkInfo.getLength());
    EXPECT_EQ(0x12345678u, chunkInfo.getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::Zlib, chunkInfo.getCompression());
}

TEST(ChunkInfo, CopyConstructor)
{
    // Init A
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(anvil::ChunkInfo::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Copy
    anvil::ChunkInfo chunkInfoB(chunkInfoA);
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, MoveConstructor)
{
    // Init A
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(anvil::ChunkInfo::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Move
    anvil::ChunkInfo chunkInfoB(std::move(chunkInfoA));
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, CopyAssignment)
{
    // Init A
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(anvil::ChunkInfo::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Copy
    anvil::ChunkInfo chunkInfoB = chunkInfoA;
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, MoveAssignment)
{
    // Init A
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    ASSERT_EQ(345u, chunkInfoA.getOffset());
    ASSERT_EQ(20u, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678u, chunkInfoA.getTimestamp());
    ASSERT_EQ(anvil::ChunkInfo::CompressionType::Zlib, chunkInfoA.getCompression());

    // Test Move
    anvil::ChunkInfo chunkInfoB = std::move(chunkInfoA);
    EXPECT_EQ(chunkInfoA.getOffset(), chunkInfoB.getOffset());
    EXPECT_EQ(chunkInfoA.getLength(), chunkInfoB.getLength());
    EXPECT_EQ(chunkInfoA.getTimestamp(), chunkInfoB.getTimestamp());
    EXPECT_EQ(chunkInfoA.getCompression(), chunkInfoB.getCompression());
}

TEST(ChunkInfo, Equal)
{
    // Init
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoC(346, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoD(345, 21, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoE(345, 20, 0x12345679, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoF(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::GZip);
    anvil::ChunkInfo chunkInfoG;

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
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoC(346, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoD(345, 21, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoE(345, 20, 0x12345679, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoF(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::GZip);
    anvil::ChunkInfo chunkInfoG;

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
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(0, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoC;

    EXPECT_FALSE(chunkInfoA.isEmpty());
    EXPECT_TRUE(chunkInfoB.isEmpty());
    EXPECT_TRUE(chunkInfoC.isEmpty());
}

TEST(ChunkInfo, getOffset)
{
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(0, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getOffset(), 345u);
    EXPECT_EQ(chunkInfoB.getOffset(), 0u);
    EXPECT_EQ(chunkInfoC.getOffset(), 0u);
}

TEST(ChunkInfo, setOffset)
{
    anvil::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getOffset(), 0u);
    chunkInfo.setOffset(8u);
    EXPECT_EQ(chunkInfo.getOffset(), 8u);
}

TEST(ChunkInfo, getLength)
{
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(0, 0, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getLength(), 20u);
    EXPECT_EQ(chunkInfoB.getLength(), 0u);
    EXPECT_EQ(chunkInfoC.getLength(), 0u);
}

TEST(ChunkInfo, setLength)
{
    anvil::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getLength(), 0u);
    chunkInfo.setLength(8u);
    EXPECT_EQ(chunkInfo.getLength(), 8u);
}

TEST(ChunkInfo, getTimestamp)
{
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(0, 0, 0, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getTimestamp(), 0x12345678u);
    EXPECT_EQ(chunkInfoB.getTimestamp(), 0u);
    EXPECT_EQ(chunkInfoC.getTimestamp(), 0u);
}

TEST(ChunkInfo, setTimestamp)
{
    anvil::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getTimestamp(), 0u);
    chunkInfo.setTimestamp(8u);
    EXPECT_EQ(chunkInfo.getTimestamp(), 8u);
}

TEST(ChunkInfo, getCompression)
{
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);
    anvil::ChunkInfo chunkInfoB(0, 0, 0, anvil::ChunkInfo::CompressionType::GZip);
    anvil::ChunkInfo chunkInfoC;

    EXPECT_EQ(chunkInfoA.getCompression(), anvil::ChunkInfo::CompressionType::Zlib);
    EXPECT_EQ(chunkInfoB.getCompression(), anvil::ChunkInfo::CompressionType::GZip);
    EXPECT_EQ(chunkInfoC.getCompression(), anvil::ChunkInfo::CompressionType::GZip);
}

TEST(ChunkInfo, setCompression)
{
    anvil::ChunkInfo chunkInfo;
    ASSERT_EQ(chunkInfo.getCompression(), anvil::ChunkInfo::CompressionType::GZip);
    chunkInfo.setCompression(anvil::ChunkInfo::CompressionType::Zlib);
    EXPECT_EQ(chunkInfo.getCompression(), anvil::ChunkInfo::CompressionType::Zlib);
}
