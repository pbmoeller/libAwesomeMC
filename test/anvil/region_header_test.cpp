// AwesomeMC
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/anvil/region_header.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <exception>
#include <fstream>

const std::string testFolder = "../../../test/testdata/world/";

class RegionHeaderFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {

    }

    static void SetUpTestSuite()
    {
        const std::string filename = testFolder + "libAwesomeMC_TestWorld_1_18_1/region/r.-1.-1.mca";
        
        std::ifstream ifs(filename, std::ios::binary);
        if(!ifs.is_open()) {
            throw std::runtime_error(std::string("Could not open data file: ") + filename);
        }
        m_data = std::vector<unsigned char>(amc::HeaderSize, 0);
        ifs.read(reinterpret_cast<char*>(m_data.data()), amc::HeaderSize);
    }

    virtual void TearDown() override
    {

    }

    const std::vector<unsigned char>& getTestData() const
    {
        return m_data;
    }

private:
    static std::vector<unsigned char> m_data;
};

std::vector<unsigned char> RegionHeaderFixture::m_data;

TEST_F(RegionHeaderFixture, Constructor)
{
    amc::RegionHeader rHeader;
    EXPECT_EQ(rHeader.getData().size(), amc::HeaderSize);
    ASSERT_THAT(rHeader.getData(), ::testing::Each(::testing::Eq(0)));
}

TEST_F(RegionHeaderFixture, Constructor_2_throw)
{
    const std::vector<unsigned char> data(2, 0);
    EXPECT_THROW(amc::RegionHeader rHeader(data), std::runtime_error);
}

TEST_F(RegionHeaderFixture, Constructor_2)
{
    std::vector<unsigned char> data(amc::HeaderSize, 2);
    amc::RegionHeader rHeader(data);
    EXPECT_EQ(rHeader.getData().size(), amc::HeaderSize);
    EXPECT_EQ(data.size(), amc::HeaderSize);
    ASSERT_THAT(rHeader.getData(), ::testing::Each(::testing::Eq(2)));
}

TEST_F(RegionHeaderFixture, Constructor_3_throw)
{
    std::vector<unsigned char> data(2, 0);
    EXPECT_THROW(amc::RegionHeader rHeader(std::move(data)), std::runtime_error);
}

TEST_F(RegionHeaderFixture, Constructor_3)
{
    std::vector<unsigned char> data(amc::HeaderSize, 3);
    amc::RegionHeader rHeader(std::move(data));
    EXPECT_EQ(rHeader.getData().size(), amc::HeaderSize);
    EXPECT_EQ(data.size(), 0);
    ASSERT_THAT(rHeader.getData(), ::testing::Each(::testing::Eq(3)));
}

TEST_F(RegionHeaderFixture, CopyConstructor)
{
    amc::RegionHeader rHeader1(getTestData());
    amc::RegionHeader rHeader2(rHeader1);
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
    ASSERT_THAT(rHeader2.getData(), ::testing::Not(::testing::Each(::testing::Eq(3))));
    EXPECT_EQ(rHeader1.getData().size(), amc::HeaderSize);
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
}

TEST_F(RegionHeaderFixture, MoveConstructor)
{
    amc::RegionHeader rHeader1(getTestData());
    amc::RegionHeader rHeader2(std::move(rHeader1));
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
    ASSERT_THAT(rHeader2.getData(), ::testing::Not(::testing::Each(::testing::Eq(0))));
    EXPECT_EQ(rHeader1.getData().size(), 0);
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
}

TEST_F(RegionHeaderFixture, CopyAssignment)
{
    amc::RegionHeader rHeader1(getTestData());
    amc::RegionHeader rHeader2 = rHeader1;
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
    ASSERT_THAT(rHeader2.getData(), ::testing::Not(::testing::Each(::testing::Eq(0))));
    EXPECT_EQ(rHeader1.getData().size(), amc::HeaderSize);
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
}

TEST_F(RegionHeaderFixture, MoveAssignment)
{
    amc::RegionHeader rHeader1(getTestData());
    amc::RegionHeader rHeader2 = std::move(rHeader1);
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
    ASSERT_THAT(rHeader2.getData(), ::testing::Not(::testing::Each(::testing::Eq(0))));
    EXPECT_EQ(rHeader1.getData().size(), 0);
    EXPECT_EQ(rHeader2.getData().size(), amc::HeaderSize);
}

TEST_F(RegionHeaderFixture, Equal)
{
    amc::RegionHeader rHeader1;
    amc::RegionHeader rHeader2;
    amc::RegionHeader rHeader3(getTestData());

    EXPECT_TRUE(rHeader1 == rHeader2);
    EXPECT_FALSE(rHeader2 == rHeader3);
    EXPECT_FALSE(rHeader1 == rHeader3);

    rHeader2 = rHeader3;

    EXPECT_FALSE(rHeader1 == rHeader2);
    EXPECT_TRUE(rHeader2 == rHeader3);
    EXPECT_FALSE(rHeader1 == rHeader3);
}

TEST_F(RegionHeaderFixture, NotEqual)
{
    amc::RegionHeader rHeader1;
    amc::RegionHeader rHeader2;
    amc::RegionHeader rHeader3(getTestData());

    EXPECT_FALSE(rHeader1 != rHeader2);
    EXPECT_TRUE(rHeader2 != rHeader3);
    EXPECT_TRUE(rHeader1 != rHeader3);

    rHeader2 = rHeader3;

    EXPECT_TRUE(rHeader1 != rHeader2);
    EXPECT_FALSE(rHeader2 != rHeader3);
    EXPECT_TRUE(rHeader1 != rHeader3);
}

TEST_F(RegionHeaderFixture, getChunkCount)
{
    amc::RegionHeader rHeader1;
    EXPECT_EQ(0, rHeader1.getChunkCount());

    amc::RegionHeader rHeader2(getTestData());
    EXPECT_EQ(993, rHeader2.getChunkCount());
}

TEST_F(RegionHeaderFixture, getData)
{
    amc::RegionHeader rHeader1;
    EXPECT_EQ(amc::HeaderSize, rHeader1.getData().size());
}

TEST_F(RegionHeaderFixture, isEmpty)
{
    amc::RegionHeader rHeader1;
    for(int index = 0; index < amc::ChunkCount; ++index) {
        EXPECT_TRUE(rHeader1.isEmpty(index));
    }

    amc::RegionHeader rHeader2(getTestData());
    EXPECT_FALSE(rHeader2.isEmpty(0));
    EXPECT_TRUE(rHeader2.isEmpty(265));
}

TEST_F(RegionHeaderFixture, getOffset)
{
    amc::RegionHeader rHeader(getTestData());

    // Test known chunk data in test file
    EXPECT_EQ(198,  rHeader.getOffset(0));
    EXPECT_EQ(8,    rHeader.getOffset(32));
    EXPECT_EQ(94,   rHeader.getOffset(92));
    EXPECT_EQ(0,    rHeader.getOffset(265));
    EXPECT_EQ(1514, rHeader.getOffset(970));
    EXPECT_EQ(53,   rHeader.getOffset(1023));
}

TEST_F(RegionHeaderFixture, getByteOffset)
{
    amc::RegionHeader rHeader(getTestData());

    // Test known chunk data in test file
    EXPECT_EQ(811008,   rHeader.getByteOffset(0));
    EXPECT_EQ(32768,    rHeader.getByteOffset(32));
    EXPECT_EQ(385024,   rHeader.getByteOffset(92));
    EXPECT_EQ(0,        rHeader.getByteOffset(265));
    EXPECT_EQ(6201344,  rHeader.getByteOffset(970));
    EXPECT_EQ(217088,   rHeader.getByteOffset(1023));
}

TEST_F(RegionHeaderFixture, getSize)
{
    amc::RegionHeader rHeader(getTestData());

    // Test known chunk data in test file
    EXPECT_EQ(1, rHeader.getSize(0));
    EXPECT_EQ(1, rHeader.getSize(32));
    EXPECT_EQ(1, rHeader.getSize(92));
    EXPECT_EQ(0, rHeader.getSize(265));
    EXPECT_EQ(4, rHeader.getSize(970));
    EXPECT_EQ(2, rHeader.getSize(1023));
}

TEST_F(RegionHeaderFixture, getByteSize)
{
    amc::RegionHeader rHeader(getTestData());

    // Test known chunk data in test file
    EXPECT_EQ(4096,     rHeader.getByteSize(0));
    EXPECT_EQ(4096,     rHeader.getByteSize(32));
    EXPECT_EQ(4096,     rHeader.getByteSize(92));
    EXPECT_EQ(0,        rHeader.getByteSize(265));
    EXPECT_EQ(16384,    rHeader.getByteSize(970));
    EXPECT_EQ(8192,     rHeader.getByteSize(1023));
}

TEST_F(RegionHeaderFixture, getTimestamp)
{
    amc::RegionHeader rHeader(getTestData());

    // Test known chunk data in test file
    EXPECT_EQ(1641405230,   rHeader.getTimestamp(0));
    EXPECT_EQ(1641405230,   rHeader.getTimestamp(32));
    EXPECT_EQ(1641405231,   rHeader.getTimestamp(92));
    EXPECT_EQ(0,            rHeader.getTimestamp(265));
    EXPECT_EQ(1641405237,   rHeader.getTimestamp(970));
    EXPECT_EQ(1642363205,   rHeader.getTimestamp(1023));
}

TEST_F(RegionHeaderFixture, setChunkData)
{
    amc::RegionHeader rHeader;
    EXPECT_EQ(rHeader.getData().size(), amc::HeaderSize);
    ASSERT_THAT(rHeader.getData(),
                ::testing::Each(::testing::Eq(0)));

    rHeader.setChunkData(0, 198, 1, 1641405230);
    ASSERT_THAT(rHeader.getData(),
                ::testing::Not(::testing::Each(::testing::Eq(0))));

    EXPECT_EQ(198,          rHeader.getOffset(0));
    EXPECT_EQ(811008,       rHeader.getByteOffset(0));
    EXPECT_EQ(1,            rHeader.getSize(0));
    EXPECT_EQ(4096,         rHeader.getByteSize(0));
    EXPECT_EQ(1641405230,   rHeader.getTimestamp(0));

    rHeader.setChunkData(0, 0, 0, 0);
    ASSERT_THAT(rHeader.getData(),
                ::testing::Each(::testing::Eq(0)));

    EXPECT_EQ(0, rHeader.getOffset(0));
    EXPECT_EQ(0, rHeader.getByteOffset(0));
    EXPECT_EQ(0, rHeader.getSize(0));
    EXPECT_EQ(0, rHeader.getByteSize(0));
    EXPECT_EQ(0, rHeader.getTimestamp(0));
}
