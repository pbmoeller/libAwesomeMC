// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>
#include <AwesomeMC/util/traits.hpp>

// gtest
#include <gtest/gtest.h>

// STL
#include <cstring>
#include <tuple>

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
    ret = byteStream << value1;
    EXPECT_TRUE(ret);
    EXPECT_FALSE(byteStream.good());
    byteStream.reset();
    EXPECT_TRUE(byteStream.good());

    // Read 
    ret = byteStream >> value1_out;
    EXPECT_TRUE(ret);
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

// Test Left Shift Operator
template<typename T>
using LeftShiftParamsT = std::vector<std::tuple<T, size_t, T, size_t>>;

static std::tuple<
    LeftShiftParamsT<char>,
    LeftShiftParamsT<unsigned char>,
    LeftShiftParamsT<int8_t>,
    LeftShiftParamsT<int16_t>,
    LeftShiftParamsT<int32_t>,
    LeftShiftParamsT<int64_t>,
    LeftShiftParamsT<float>,
    LeftShiftParamsT<double>
> leftShiftParamsSimple
{
    {
        std::make_tuple(char(-98), 1, char(52), 2),
    },
    {
        std::make_tuple((unsigned char)(3), 1, (unsigned char)(222), 2),
    },
    {
        std::make_tuple(int8_t(-8), 1, int8_t(56), 2),
    },
    {
        std::make_tuple(int16_t(0x5678), 2, int16_t(0x1234), 4),
    },
    {
        std::make_tuple(0x12345678, 4, 0xAABBCCDD, 8),
    },
    {
        std::make_tuple(0x0123456789ABCDEF, 8, 0xAABBCCDDEEFF1234, 16),
    },
    {
        std::make_tuple(1.0f, 4, 2.0f, 8),
    },
    {
        std::make_tuple(3.14, 8, -4.5, 16),
    }
};

static std::tuple<
    LeftShiftParamsT<std::string>,
    LeftShiftParamsT<std::vector<int8_t>>,
    LeftShiftParamsT<std::vector<uint8_t>>
> leftShiftParamsVector
{
    {
        std::make_tuple("Test", 4, "String", 10),
    },
    {
        std::make_tuple(std::vector<int8_t>({18, 52}), 2,
                        std::vector<int8_t>({-128, 3, -2, 0, -66, 127, 32, 99}), 10),
    },
    {
        std::make_tuple(std::vector<uint8_t>({0, 255, 34, 1, 133}), 5,
                        std::vector<uint8_t>({128, 3, 2, 0, 200, 111}), 11),
    }
};

template<typename T>
struct LeftShiftFixtureSimple : public testing::Test
{
    LeftShiftFixtureSimple()
        : params{std::get<LeftShiftParamsT<T>>(leftShiftParamsSimple)}
    { }
    LeftShiftParamsT<T> params;
};

template<typename T>
struct LeftShiftFixtureVector : public testing::Test
{
    LeftShiftFixtureVector()
        : params{std::get<LeftShiftParamsT<T>>(leftShiftParamsVector)}
    { }
    LeftShiftParamsT<T> params;
};

TYPED_TEST_SUITE_P(LeftShiftFixtureSimple);
TYPED_TEST_SUITE_P(LeftShiftFixtureVector);

TYPED_TEST_P(LeftShiftFixtureSimple, left_shift)
{
    for(auto const& [input1, expectedSizePos1, input2, expectedSizePos2] : this->params) {
        // Test size and position of ByteStream
        util::ByteStream byteStream;
        ASSERT_EQ(0, byteStream.size());
        ASSERT_EQ(0, byteStream.getPosition());
        byteStream << input1;
        EXPECT_EQ(expectedSizePos1, byteStream.size());
        EXPECT_EQ(expectedSizePos1, byteStream.getPosition());
        byteStream << input2;
        EXPECT_EQ(expectedSizePos2, byteStream.size());
        EXPECT_EQ(expectedSizePos2, byteStream.getPosition());

        // Init Test content
        unsigned char testArray1[sizeof(TypeParam)];
        unsigned char testArray2[sizeof(TypeParam)];
        std::memcpy(&testArray1[0], &input1, sizeof(TypeParam));
        std::memcpy(&testArray2[0], &input2, sizeof(TypeParam));

        // Test ByteStream content
        std::vector<unsigned char> data = byteStream.vbuf();
        for(size_t i = 0; i < sizeof(TypeParam); ++i) {
            EXPECT_EQ(data[i], testArray1[i]);
        }
        for(size_t i = 0; i < sizeof(TypeParam); ++i) {
            EXPECT_EQ(data[i + sizeof(TypeParam)], testArray2[i]);
        }
    }
}

TYPED_TEST_P(LeftShiftFixtureSimple, left_shift_swapped)
{
    for(auto const& [input1, expectedSizePos1, input2, expectedSizePos2] : this->params) {
        // Test size and position of ByteStream
        util::ByteStream byteStream(util::ByteStream::Swap::SwapEndian);
        ASSERT_EQ(0, byteStream.size());
        ASSERT_EQ(0, byteStream.getPosition());
        byteStream << input1;
        EXPECT_EQ(expectedSizePos1, byteStream.size());
        EXPECT_EQ(expectedSizePos1, byteStream.getPosition());
        byteStream << input2;
        EXPECT_EQ(expectedSizePos2, byteStream.size());
        EXPECT_EQ(expectedSizePos2, byteStream.getPosition());

        // Init Test content
        unsigned char testArray1[sizeof(TypeParam)];
        unsigned char testArray2[sizeof(TypeParam)];
        std::memcpy(&testArray1[0], &input1, sizeof(TypeParam));
        std::memcpy(&testArray2[0], &input2, sizeof(TypeParam));

        // Test ByteStream content
        std::vector<unsigned char> data = byteStream.vbuf();
        for(size_t i = 0; i < sizeof(TypeParam); ++i) {
            EXPECT_EQ(data[sizeof(TypeParam) - 1 - i], testArray1[i]);
        }
        for(size_t i = 0; i < sizeof(TypeParam); ++i) {
            EXPECT_EQ(data[2 * sizeof(TypeParam) - 1 - i], testArray2[i]);
        }
    }
}

TYPED_TEST_P(LeftShiftFixtureVector, left_shift)
{
    for(auto const& [input1, expectedSizePos1, input2, expectedSizePos2] : this->params) {
        // Test size and position of ByteStream
        util::ByteStream byteStream;
        ASSERT_EQ(0, byteStream.size());
        ASSERT_EQ(0, byteStream.getPosition());
        byteStream << input1;
        EXPECT_EQ(expectedSizePos1, byteStream.size());
        EXPECT_EQ(expectedSizePos1, byteStream.getPosition());
        byteStream << input2;
        EXPECT_EQ(expectedSizePos2, byteStream.size());
        EXPECT_EQ(expectedSizePos2, byteStream.getPosition());

        // Test ByteStream content
        std::vector<unsigned char> data = byteStream.vbuf();
        for(size_t i = 0; i < input1.size(); ++i) {
            EXPECT_EQ(data[i], static_cast<unsigned char>(input1[i]));
        }
        for(size_t i = 0; i < input2.size(); ++i) {
            EXPECT_EQ(data[i + expectedSizePos1], static_cast<unsigned char>(input2[i]));
        }
    }
}

REGISTER_TYPED_TEST_SUITE_P(LeftShiftFixtureSimple, left_shift, left_shift_swapped);
REGISTER_TYPED_TEST_SUITE_P(LeftShiftFixtureVector, left_shift);

using LeftShiftTypesSimple = testing::Types<
    char,
    unsigned char,
    int8_t,
    int16_t,
    int32_t,
    int64_t,
    float,
    double
>;
using LeftShiftTypesVector = testing::Types<
    std::string,
    std::vector<int8_t>,
    std::vector<uint8_t>
>;

INSTANTIATE_TYPED_TEST_SUITE_P(ByteStream, LeftShiftFixtureSimple, LeftShiftTypesSimple);
INSTANTIATE_TYPED_TEST_SUITE_P(ByteStream, LeftShiftFixtureVector, LeftShiftTypesVector);

// Test Right Shift Operator
template<typename T>
using RightShiftParamsT = std::vector<std::tuple<T>>;

static std::tuple<
    RightShiftParamsT<int8_t>,
    RightShiftParamsT<uint8_t>,
    RightShiftParamsT<int16_t>,
    RightShiftParamsT<uint16_t>,
    RightShiftParamsT<int32_t>,
    RightShiftParamsT<uint32_t>,
    RightShiftParamsT<int64_t>,
    RightShiftParamsT<uint64_t>,
    RightShiftParamsT<float>,
    RightShiftParamsT<double>
> rightShiftParams
{
    {
        std::make_tuple(std::numeric_limits<int8_t>::min()),
        std::make_tuple(-34),
        std::make_tuple(0),
        std::make_tuple(115),
        std::make_tuple(std::numeric_limits<int8_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<uint8_t>::min()),
        std::make_tuple(0),
        std::make_tuple(222),
        std::make_tuple(std::numeric_limits<uint8_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<int16_t>::min()),
        std::make_tuple(-1234),
        std::make_tuple(0),
        std::make_tuple(413),
        std::make_tuple(std::numeric_limits<int16_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<uint16_t>::min()),
        std::make_tuple(0),
        std::make_tuple(37899),
        std::make_tuple(std::numeric_limits<uint16_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<int32_t>::min()),
        std::make_tuple(-131231),
        std::make_tuple(0),
        std::make_tuple(0x12345678),
        std::make_tuple(std::numeric_limits<int32_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<uint32_t>::min()),
        std::make_tuple(0),
        std::make_tuple(100000000),
        std::make_tuple(std::numeric_limits<uint32_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<int64_t>::min()),
        std::make_tuple(-(0x1234567890ABCDEF)),
        std::make_tuple(0),
        std::make_tuple(0x1234567890ABCDEF),
        std::make_tuple(std::numeric_limits<int64_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<uint64_t>::min()),
        std::make_tuple(0),
        std::make_tuple(0xFFFFFFFF12345678),
        std::make_tuple(std::numeric_limits<uint64_t>::max())
    },
    {
        std::make_tuple(std::numeric_limits<float>::min()),
        std::make_tuple(100.567f),
        std::make_tuple(300e2f),
        std::make_tuple(-3.14f),
        std::make_tuple(std::numeric_limits<float>::max())
    },
    {
        std::make_tuple(std::numeric_limits<double>::min()),
        std::make_tuple(12345.67890),
        std::make_tuple(-5.4e-9),
        std::make_tuple(std::numeric_limits<double>::max())
    }
};

template<typename T>
struct RightShiftFixture : public testing::Test
{
    RightShiftFixture()
        : params{std::get<RightShiftParamsT<T>>(rightShiftParams)}
    { }
    RightShiftParamsT<T> params;
};

TYPED_TEST_SUITE_P(RightShiftFixture);

TYPED_TEST_P(RightShiftFixture, right_shift)
{
    for(const auto &[input1] : this->params)
    {
        // Init 
        size_t ret = 0;
        TypeParam value1 = 0;
        TypeParam value2 = 0;
        util::ByteStream byteStream;

        // Write input 1
        byteStream << input1;
        ASSERT_EQ(sizeof(TypeParam), byteStream.size());
        ASSERT_EQ(sizeof(TypeParam), byteStream.getPosition());

        // Set position back
        byteStream.reset();
        ASSERT_EQ(0, byteStream.getPosition());
        EXPECT_EQ(sizeof(TypeParam), byteStream.availableBytes());

        // Read input 1
        ret = byteStream >> value1;
        EXPECT_EQ(util::ByteStream::Success, ret);
        EXPECT_EQ(input1, value1);

        // Read invalid
        EXPECT_EQ(0, byteStream.availableBytes());
        ret = byteStream >> value2;
        EXPECT_EQ(util::ByteStream::EndOfStream, ret);
        EXPECT_EQ(0, value2);
    }
}

REGISTER_TYPED_TEST_SUITE_P(RightShiftFixture, right_shift);

using RightShiftTypes = testing::Types<
    int8_t,
    uint8_t,
    int16_t,
    uint16_t,
    int32_t,
    uint32_t,
    int64_t,
    uint64_t,
    float,
    double
>;

INSTANTIATE_TYPED_TEST_SUITE_P(ByteStream, RightShiftFixture, RightShiftTypes);