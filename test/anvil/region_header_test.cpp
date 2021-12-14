#include "anvil/region_header.hpp"
#include "anvil/chunk_info.hpp"

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
    // Init Testdata
    std::array<anvil::ChunkInfo, anvil::ChunkCount> info;
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        info[i] = anvil::ChunkInfo(i * 2, i, i*3, anvil::ChunkInfo::CompressionType::GZip);
    }

    // Check
    anvil::RegionHeader regionHeader(info);
    for(int i = 0; i < anvil::ChunkCount; ++i) {
        EXPECT_EQ(info[i].getOffset(),      regionHeader.getChunkInfoAt(i).getOffset());
        EXPECT_EQ(info[i].getLength(),      regionHeader.getChunkInfoAt(i).getLength());
        EXPECT_EQ(info[i].getTimestamp(),   regionHeader.getChunkInfoAt(i).getTimestamp());
        EXPECT_EQ(info[i].getCompression(), regionHeader.getChunkInfoAt(i).getCompression());
    }
}

TEST(ReagionHeader, CopyConstructor)
{

}

TEST(ReagionHeader, MoveConstructor)
{

}

TEST(ReagionHeader, CopyAssignment)
{

}

TEST(ReagionHeader, MoveAssignment)
{

}

TEST(ReagionHeader, Equal)
{

}

TEST(ReagionHeader, NotEqual)
{

}

TEST(ReagionHeader, getRegionCount)
{

}

TEST(ReagionHeader, getRegionData)
{

}

TEST(ReagionHeader, getChunkInfo)
{

}

TEST(ReagionHeader, getChunkInfoAt)
{

}

TEST(ReagionHeader, getChunkInfoAt_const)
{

}

TEST(ReagionHeader, setChunkInfo)
{

}

TEST(ReagionHeader, setChunkInfoAt)
{

}