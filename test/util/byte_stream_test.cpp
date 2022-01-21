// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// gtest
#include <gtest/gtest.h>

TEST(ByteStream, Types)
{
    EXPECT_EQ(0, static_cast<int>(util::ByteStream::Swap::NoSwapEndian));
    EXPECT_EQ(1, static_cast<int>(util::ByteStream::Swap::SwapEndian));

    EXPECT_EQ(0, util::ByteStream::EndOfStream);
    EXPECT_EQ(1, util::ByteStream::Success);
}

TEST(ByteStream, Constructor)
{
    util::ByteStream stream;

    EXPECT_EQ(0, stream.getPosition());
    EXPECT_EQ(false, stream.isSwapSet());
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, stream.getSwap());
    EXPECT_EQ(0, stream.size());
    EXPECT_EQ(0, stream.availableBytes());
}

TEST(ByteStream, Constructor_2)
{
    util::ByteStream stream(util::ByteStream::Swap::NoSwapEndian);

    EXPECT_EQ(0, stream.getPosition());
    EXPECT_EQ(false, stream.isSwapSet());
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, stream.getSwap());
    EXPECT_EQ(0, stream.size());
    EXPECT_EQ(0, stream.availableBytes());

    util::ByteStream stream2(util::ByteStream::Swap::SwapEndian);

    EXPECT_EQ(0, stream2.getPosition());
    EXPECT_EQ(true, stream2.isSwapSet());
    EXPECT_EQ(util::ByteStream::Swap::SwapEndian, stream2.getSwap());
    EXPECT_EQ(0, stream2.size());
    EXPECT_EQ(0, stream2.availableBytes());
}

TEST(ByteStream, Constructor_3)
{
    std::string data("ABCD");

    util::ByteStream stream(data);

    EXPECT_EQ(0, stream.getPosition());
    EXPECT_EQ(false, stream.isSwapSet());
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, stream.getSwap());
    EXPECT_EQ(data.size(), stream.size());
    EXPECT_EQ(data.size(), stream.availableBytes());
}

TEST(ByteStream, Constructor_4)
{
    std::vector<unsigned char> data({0, 1, 2, 3});

    util::ByteStream stream(data);

    EXPECT_EQ(0, stream.getPosition());
    EXPECT_EQ(false, stream.isSwapSet());
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, stream.getSwap());
    EXPECT_EQ(data.size(), stream.size());
    EXPECT_EQ(data.size(), stream.availableBytes());
}

TEST(ByteStream, CopyConstructor)
{
    std::string str = "Byte";

    // Init Stream A
    util::ByteStream streamA;
    streamA.setSwap(util::ByteStream::Swap::SwapEndian);
    streamA << str;
    ASSERT_EQ(4, streamA.getPosition());
    ASSERT_EQ(4, streamA.size());
    ASSERT_EQ(util::ByteStream::Swap::SwapEndian, streamA.getSwap());

    // Test Copy Constructor
    util::ByteStream streamB(streamA);
    EXPECT_EQ(4, streamB.getPosition());
    EXPECT_EQ(4, streamB.size());
    EXPECT_EQ(util::ByteStream::Swap::SwapEndian, streamB.getSwap());
}

TEST(ByteStream, MoveConstructor)
{
    std::string str = "Byte";

    // Init Stream A
    util::ByteStream streamA;
    streamA.setSwap(util::ByteStream::Swap::SwapEndian);
    streamA << str;
    ASSERT_EQ(4, streamA.getPosition());
    ASSERT_EQ(4, streamA.size());
    ASSERT_EQ(util::ByteStream::Swap::SwapEndian, streamA.getSwap());

    // Test Move Constructor
    util::ByteStream streamB(std::move(streamA));
    EXPECT_EQ(4, streamB.getPosition());
    EXPECT_EQ(4, streamB.size());
    EXPECT_EQ(util::ByteStream::Swap::SwapEndian, streamB.getSwap());
}

TEST(ByteStream, CopyAssignment)
{
    std::string str = "Byte";

    // Init Stream A
    util::ByteStream streamA;
    streamA.setSwap(util::ByteStream::Swap::SwapEndian);
    streamA << str;
    ASSERT_EQ(4, streamA.getPosition());
    ASSERT_EQ(4, streamA.size());
    ASSERT_EQ(util::ByteStream::Swap::SwapEndian, streamA.getSwap());

    // Init Stream B
    util::ByteStream streamB;
    ASSERT_EQ(0, streamB.getPosition());
    ASSERT_EQ(0, streamB.size());
    ASSERT_EQ(util::ByteStream::Swap::NoSwapEndian, streamB.getSwap());

    // Test Copy Assignment
    streamB = streamA;
    EXPECT_EQ(4, streamB.getPosition());
    EXPECT_EQ(4, streamB.size());
    EXPECT_EQ(util::ByteStream::Swap::SwapEndian, streamB.getSwap());
}

TEST(ByteStream, MoveAssignment)
{
    // Init Stream A
    util::ByteStream streamA;
    streamA.setSwap(util::ByteStream::Swap::SwapEndian);
    ASSERT_EQ(0, streamA.getPosition());
    ASSERT_EQ(0, streamA.size());
    ASSERT_EQ(util::ByteStream::Swap::SwapEndian, streamA.getSwap());

    // Test Move Assignment
    streamA = util::ByteStream("Byte");
    EXPECT_EQ(0, streamA.getPosition());
    EXPECT_EQ(4, streamA.size());
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, streamA.getSwap());
}

TEST(ByteStream, Equal)
{
    util::ByteStream a("BYTES");
    util::ByteStream b("BYTES");
    util::ByteStream c("BYTED");
    util::ByteStream d("BYTE");

    EXPECT_TRUE(a == a);
    EXPECT_TRUE(a == b);
    b.setPosition(1);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);

    util::ByteStream g;
    util::ByteStream h;
    g << 3.4;
    h << 3.4;
    EXPECT_TRUE(g == g);
    EXPECT_TRUE(g == h);
    h.reset();
    EXPECT_FALSE(g == h);
}

TEST(ByteStream, NotEqual)
{
    util::ByteStream a("BYTES");
    util::ByteStream b("BYTES");
    util::ByteStream c("BYTED");
    util::ByteStream d("BYTE");

    EXPECT_FALSE(a != a);
    EXPECT_FALSE(a != b);
    b.setPosition(1);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a != d);

    util::ByteStream g;
    util::ByteStream h;
    g << 3.4;
    h << 3.4;
    EXPECT_FALSE(g != g);
    EXPECT_FALSE(g != h);
    h.reset();
    EXPECT_TRUE(g != h);
}

TEST(ByteStream, availableBytes)
{
    std::string data("ABCD");

    util::ByteStream stream;
    stream << data;
    ASSERT_EQ(data.size(), stream.getPosition());
    ASSERT_EQ(data.size(), stream.size());
    ASSERT_EQ(0, stream.availableBytes());

    stream.reset();
    ASSERT_EQ(4, stream.availableBytes());
    int8_t value;
    stream >> value;
    ASSERT_EQ(3, stream.availableBytes());
    stream >> value;
    ASSERT_EQ(2, stream.availableBytes());
    stream >> value;
    ASSERT_EQ(1, stream.availableBytes());
    stream >> value;
    ASSERT_EQ(0, stream.availableBytes());
}

TEST(ByteStream, size)
{
    util::ByteStream byteStream;
    EXPECT_EQ(0, byteStream.size());
    byteStream << static_cast<int8_t>(0x45);
    EXPECT_EQ(1, byteStream.size());
    byteStream << static_cast<int16_t>(0x6789);
    EXPECT_EQ(3, byteStream.size());

    byteStream.clear();
    EXPECT_EQ(0, byteStream.size());
}

TEST(ByteStream, good)
{
    // Definitions
    size_t ret = 0;
    int16_t value1 = 0x1234;
    int16_t value1_out = 0;

    // Init
    util::ByteStream byteStream;
    EXPECT_FALSE(byteStream.good());
    byteStream << value1;
    EXPECT_FALSE(byteStream.good());
    byteStream.reset();
    EXPECT_TRUE(byteStream.good());

    // Read 
    ret = byteStream >> value1_out;
    EXPECT_FALSE(byteStream.good());
}

TEST(ByteStream, clear)
{
    std::string data("ABCD");
    util::ByteStream stream(data);

    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(data.size(), stream.size());
    ASSERT_EQ(data.size(), stream.availableBytes());
    stream.clear();
    EXPECT_EQ(0, stream.getPosition());
    EXPECT_EQ(0, stream.size());
    EXPECT_EQ(0, stream.availableBytes());

    util::ByteStream stream2;
    stream2 << data;
    ASSERT_EQ(data.size(), stream2.getPosition());
    ASSERT_EQ(data.size(), stream2.size());
    ASSERT_EQ(0, stream2.availableBytes());
    stream2.clear();
    EXPECT_EQ(0, stream2.getPosition());
    EXPECT_EQ(0, stream2.size());
    EXPECT_EQ(0, stream2.availableBytes());
}

TEST(ByteStream, reset)
{
    std::string data("ABCD");

    util::ByteStream stream;
    stream << data;
    ASSERT_EQ(data.size(), stream.getPosition());
    ASSERT_EQ(data.size(), stream.size());
    ASSERT_EQ(0, stream.availableBytes());
    stream.reset();
    EXPECT_EQ(0, stream.getPosition());
}

TEST(ByteStream, getPosition)
{
    util::ByteStream byteStream;

    EXPECT_EQ(0, byteStream.getPosition());
    byteStream.setPosition(2);
    EXPECT_EQ(2, byteStream.getPosition());

    util::ByteStream byteStream2("Test");
    EXPECT_EQ(0, byteStream2.getPosition());
}

TEST(ByteStream, setPosition)
{
    util::ByteStream byteStream;

    EXPECT_EQ(0, byteStream.getPosition());
    byteStream.setPosition(2);
    EXPECT_EQ(2, byteStream.getPosition());
}

TEST(ByteStream, isSwapSet)
{
    util::ByteStream byteStream;

    EXPECT_FALSE(byteStream.isSwapSet());

    byteStream.setSwap(util::ByteStream::Swap::NoSwapEndian);
    EXPECT_FALSE(byteStream.isSwapSet());
    byteStream.setSwap(util::ByteStream::Swap::SwapEndian);
    EXPECT_TRUE(byteStream.isSwapSet());
}

TEST(ByteStream, getSwap)
{
    util::ByteStream byteStream;

    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, byteStream.getSwap());

    byteStream.setSwap(util::ByteStream::Swap::NoSwapEndian);
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, byteStream.getSwap());
    byteStream.setSwap(util::ByteStream::Swap::SwapEndian);
    EXPECT_EQ(util::ByteStream::Swap::SwapEndian, byteStream.getSwap());
}

TEST(ByteStream, setSwap)
{
    util::ByteStream byteStream;

    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, byteStream.getSwap());

    byteStream.setSwap(util::ByteStream::Swap::NoSwapEndian);
    EXPECT_EQ(util::ByteStream::Swap::NoSwapEndian, byteStream.getSwap());
    byteStream.setSwap(util::ByteStream::Swap::SwapEndian);
    EXPECT_EQ(util::ByteStream::Swap::SwapEndian, byteStream.getSwap());
}

TEST(ByteStream, rdbuf)
{
    std::vector<unsigned char> data({0, 1, 2, 3});

    util::ByteStream stream(data);

    const unsigned char* data2 = stream.rdbuf();
    ASSERT_EQ(4, stream.size());
    EXPECT_EQ(data[0], data2[0]);
    EXPECT_EQ(data[1], data2[1]);
    EXPECT_EQ(data[2], data2[2]);
    EXPECT_EQ(data[3], data2[3]);
}

TEST(ByteStream, vbuf)
{
    std::vector<unsigned char> data({0, 1, 2, 3});

    util::ByteStream stream(data);

    std::vector<unsigned char> data2 = stream.vbuf();
    EXPECT_EQ(data[0], data2[0]);
    EXPECT_EQ(data[1], data2[1]);
    EXPECT_EQ(data[2], data2[2]);
    EXPECT_EQ(data[3], data2[3]);
}

TEST(ByteStream, streamOperator_in_char)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << static_cast<char>(0xAB);
    EXPECT_EQ(1, byteStream.size());
    EXPECT_EQ(1, byteStream.getPosition());
    byteStream << static_cast<char>(0x34);
    EXPECT_EQ(2, byteStream.size());
    EXPECT_EQ(2, byteStream.getPosition());

    std::vector<unsigned char> data = byteStream.vbuf();
    EXPECT_EQ(0xAB, data[0]);
    EXPECT_EQ(0x34, data[1]);
}

TEST(ByteStream, streamOperator_in_int8)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << static_cast<int8_t>(0x56);
    EXPECT_EQ(1, byteStream.size());
    EXPECT_EQ(1, byteStream.getPosition());
    byteStream << static_cast<int8_t>(0x78);
    EXPECT_EQ(2, byteStream.size());
    EXPECT_EQ(2, byteStream.getPosition());

    std::vector<unsigned char> data = byteStream.vbuf();
    EXPECT_EQ(0x56, data[0]);
    EXPECT_EQ(0x78, data[1]);
}

TEST(ByteStream, streamOperator_in_int16)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << static_cast<int16_t>(0x5678);
    EXPECT_EQ(2, byteStream.size());
    EXPECT_EQ(2, byteStream.getPosition());
    byteStream << static_cast<int16_t>(0x1234);
    EXPECT_EQ(4, byteStream.size());
    EXPECT_EQ(4, byteStream.getPosition());

    std::vector<unsigned char> data = byteStream.vbuf();
    EXPECT_EQ(0x78, data[0]);
    EXPECT_EQ(0x56, data[1]);
    EXPECT_EQ(0x34, data[2]);
    EXPECT_EQ(0x12, data[3]);

    util::ByteStream byteStream2(util::ByteStream::Swap::SwapEndian);
    ASSERT_EQ(0, byteStream2.size());
    ASSERT_EQ(0, byteStream2.getPosition());
    byteStream2 << static_cast<int16_t>(0x5678);
    EXPECT_EQ(2, byteStream2.size());
    EXPECT_EQ(2, byteStream2.getPosition());
    std::vector<unsigned char> data2 = byteStream2.vbuf();
    EXPECT_EQ(0x56, data2[0]);
    EXPECT_EQ(0x78, data2[1]);
}

TEST(ByteStream, streamOperator_in_int32)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << static_cast<int32_t>(0x12345678);
    EXPECT_EQ(4, byteStream.size());
    EXPECT_EQ(4, byteStream.getPosition());
    byteStream << static_cast<int32_t>(0xAABBCCDD);
    EXPECT_EQ(8, byteStream.size());
    EXPECT_EQ(8, byteStream.getPosition());
}

TEST(ByteStream, streamOperator_in_int64)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << static_cast<int64_t>(0x0123456789ABCDEF);
    EXPECT_EQ(8, byteStream.size());
    EXPECT_EQ(8, byteStream.getPosition());
    byteStream << static_cast<int64_t>(0xAABBCCDDEEFF1234);
    EXPECT_EQ(16, byteStream.size());
    EXPECT_EQ(16, byteStream.getPosition());
}

TEST(ByteStream, streamOperator_in_float)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << 1.0f;
    EXPECT_EQ(4, byteStream.size());
    EXPECT_EQ(4, byteStream.getPosition());
    byteStream << 2.0f;
    EXPECT_EQ(8, byteStream.size());
    EXPECT_EQ(8, byteStream.getPosition());
}

TEST(ByteStream, streamOperator_in_double)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << 3.14;
    EXPECT_EQ(8, byteStream.size());
    EXPECT_EQ(8, byteStream.getPosition());
    byteStream << -4.5;
    EXPECT_EQ(16, byteStream.size());
    EXPECT_EQ(16, byteStream.getPosition());
}

TEST(ByteStream, streamOperator_in_string)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << "Test";
    EXPECT_EQ(4, byteStream.size());
    EXPECT_EQ(4, byteStream.getPosition());
    byteStream << "String";
    EXPECT_EQ(10, byteStream.size());
    EXPECT_EQ(10, byteStream.getPosition());
}

TEST(ByteStream, streamOperator_in_vector)
{
    util::ByteStream byteStream;
    ASSERT_EQ(0, byteStream.size());
    ASSERT_EQ(0, byteStream.getPosition());
    byteStream << std::vector<char>({0x12, 0x34});
    EXPECT_EQ(2, byteStream.size());
    EXPECT_EQ(2, byteStream.getPosition());
    byteStream << std::vector<char>({0x12, 0x34, 0x56, 0x78, (char)0x90u, (char)0xABu, (char)0xCDu, (char)0xEFu});
    EXPECT_EQ(10, byteStream.size());
    EXPECT_EQ(10, byteStream.getPosition());
}

TEST(ByteStream, streamOperator_out_char)
{
    // Definitions
    size_t ret      = 0;
    char value1     = -67;
    char value2     = 117;
    char value1_out = 0;
    char value2_out = 0;
    char value3_out = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    byteStream << value2;
    ASSERT_EQ(2, byteStream.size());
    ASSERT_EQ(2, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(2, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);

    // Read 2
    EXPECT_EQ(1, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value2, value2_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value3_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value3_out);
}

TEST(ByteStream, streamOperator_out_int8)
{
    // Definitions
    size_t ret          = 0;
    int8_t value1       = -34;
    int8_t value2       = 115;
    int8_t value1_out   = 0;
    int8_t value2_out   = 0;
    int8_t value3_out   = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    byteStream << value2;
    ASSERT_EQ(2, byteStream.size());
    ASSERT_EQ(2, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(2, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);
    
    // Read 2
    EXPECT_EQ(1, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value2, value2_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value3_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value3_out);
}

TEST(ByteStream, streamOperator_out_int16)
{
    // Definitions
    size_t ret = 0;
    int16_t value1 = 0x1234;
    int16_t value1_out = 0;
    int16_t value2_out = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    ASSERT_EQ(2, byteStream.size());
    ASSERT_EQ(2, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(2, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value2_out);
}

TEST(ByteStream, streamOperator_out_int32)
{
    // Definitions
    size_t ret = 0;
    int32_t value1 = 0x12345678;
    int32_t value1_out = 0;
    int32_t value2_out = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    ASSERT_EQ(4, byteStream.size());
    ASSERT_EQ(4, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(4, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value2_out);
}

TEST(ByteStream, streamOperator_out_int64)
{
    // Definitions
    size_t ret = 0;
    int64_t value1 = 0x1234567890ABCDEF;
    int64_t value1_out = 0;
    int64_t value2_out = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    ASSERT_EQ(8, byteStream.size());
    ASSERT_EQ(8, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(8, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value2_out);
}

TEST(ByteStream, streamOperator_out_float)
{
    // Definitions
    size_t ret = 0;
    float value1 = 100.567f;
    float value1_out = 0;
    float value2_out = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    ASSERT_EQ(4, byteStream.size());
    ASSERT_EQ(4, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(4, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value2_out);
}

TEST(ByteStream, streamOperator_out_double)
{
    // Definitions
    size_t ret = 0;
    double value1 = 12345.67890;
    double value1_out = 0;
    double value2_out = 0;

    // Init
    util::ByteStream byteStream;
    byteStream << value1;
    ASSERT_EQ(8, byteStream.size());
    ASSERT_EQ(8, byteStream.getPosition());
    byteStream.reset();

    // Read 1
    EXPECT_EQ(8, byteStream.availableBytes());
    ret = byteStream >> value1_out;
    EXPECT_EQ(util::ByteStream::Success, ret);
    EXPECT_EQ(value1, value1_out);

    // Read Invalid
    EXPECT_EQ(0, byteStream.availableBytes());
    ret = byteStream >> value2_out;
    EXPECT_EQ(util::ByteStream::EndOfStream, ret);
    EXPECT_EQ(0, value2_out);
}