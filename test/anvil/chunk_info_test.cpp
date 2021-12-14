#include "anvil/chunk_info.hpp"

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

    EXPECT_EQ(0, chunkInfo.getOffset());
    EXPECT_EQ(0, chunkInfo.getLength());
    EXPECT_EQ(0, chunkInfo.getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::GZip, chunkInfo.getCompression());
}

TEST(ChunkInfo, Constructor_2)
{
    anvil::ChunkInfo chunkInfo(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    EXPECT_EQ(345, chunkInfo.getOffset());
    EXPECT_EQ(20, chunkInfo.getLength());
    EXPECT_EQ(0x12345678, chunkInfo.getTimestamp());
    EXPECT_EQ(anvil::ChunkInfo::CompressionType::Zlib, chunkInfo.getCompression());
}

TEST(ChunkInfo, CopyConstructor)
{
    // Init A
    anvil::ChunkInfo chunkInfoA(345, 20, 0x12345678, anvil::ChunkInfo::CompressionType::Zlib);

    ASSERT_EQ(345, chunkInfoA.getOffset());
    ASSERT_EQ(20, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678, chunkInfoA.getTimestamp());
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

    ASSERT_EQ(345, chunkInfoA.getOffset());
    ASSERT_EQ(20, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678, chunkInfoA.getTimestamp());
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

    ASSERT_EQ(345, chunkInfoA.getOffset());
    ASSERT_EQ(20, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678, chunkInfoA.getTimestamp());
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

    ASSERT_EQ(345, chunkInfoA.getOffset());
    ASSERT_EQ(20, chunkInfoA.getLength());
    ASSERT_EQ(0x12345678, chunkInfoA.getTimestamp());
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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, NotEqual)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, isEmpty)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, getOffset)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, setOffset)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, getLength)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, setLength)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, getTimestamp)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, setTimestamp)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, getCompression)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ChunkInfo, setCompression)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

