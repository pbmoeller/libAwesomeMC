#ifndef AWESOMEMC_UTIL_BYTE_STREAM_HPP
#define AWESOMEMC_UTIL_BYTE_STREAM_HPP

// AwesomeMC
#include <AwesomeMC/util/traits.hpp>
#include <AwesomeMC/util/byte_swap.hpp>

// STL
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace util
{

class ByteStream
{
public:
    enum class Swap
    {
        NoSwapEndian    = 0,
        SwapEndian      = 1,
    };

    static constexpr size_t EndOfStream  = 0;
    static constexpr size_t Success      = 1;

public:
    ByteStream();
    ByteStream(const ByteStream &byteStream);
    ByteStream(ByteStream &&byteStream) noexcept;
    ByteStream(Swap swap);
    ByteStream(const std::string &buffer);
    ByteStream(const std::vector<unsigned char> &buffer);
    virtual ~ByteStream();

    ByteStream& operator=(const ByteStream &other);
    ByteStream& operator=(ByteStream &&other) noexcept;

    bool operator==(const ByteStream &other);
    bool operator!=(const ByteStream &other);

    size_t availableBytes() const;
    size_t size() const;

    bool good() const;
    void clear();
    void reset();

    size_t getPosition() const;
    void setPosition(size_t pos);

    bool isSwapSet() const;
    Swap getSwap() const;
    void setSwap(Swap swap);

    const unsigned char* rdbuf();
    std::vector<unsigned char> vbuf();

    bool readString(std::string &str, const int16_t length);

    // Operators
    // Left Shift
    template<typename T>
    requires Number<T>
    bool operator<<(const T &input) {
        return writeStream(input);
    }

    template<typename T>
    requires StdStringOrStdVector<T>
    bool operator<<(const T &input) {
        m_buffer.insert(m_buffer.begin() + m_position,
                        input.begin(),
                        input.end());
        m_position += input.size();
        return true;
    }

    // Right Shift
    template<typename T>
    requires Number<T>
    bool operator>>(T &input) {
        return readStream(input);
    }

private:
    template<typename T>
    requires Number<T>
    size_t readStream(T &value)
    {
        size_t width = sizeof(T);
        if(availableBytes() < width) {
            return EndOfStream;
        }
        std::memcpy(&value, &m_buffer[m_position], width);
        m_position += width;

        if(m_swap == Swap::SwapEndian) {
            value = util::bswap(value);
        }
        return Success;
    }

    template<typename T>
    size_t writeStream(T value)
    {
        if(m_swap == Swap::SwapEndian) {
            value = util::bswap(value);
        }

        m_buffer.insert(m_buffer.end(),
                        reinterpret_cast<unsigned char*>(&value),
                        reinterpret_cast<unsigned char*>(&value) + sizeof(T));

        m_position += sizeof(T);
        return Success;
    }

private:
    std::vector<unsigned char> m_buffer;
    size_t m_position;
    Swap m_swap;
};

} // namespace util

#endif // AWESOMEMC_UTIL_BYTE_STREAM_HPP
