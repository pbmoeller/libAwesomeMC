#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace util
{

ByteStream::ByteStream()
    : m_position(0)
    , m_swap(Swap::NoSwapEndian)
{

}

ByteStream::ByteStream(const ByteStream &other)
{
    *this = other;
}

ByteStream::ByteStream(ByteStream &&other) noexcept
{
    *this = std::move(other);
}

ByteStream::ByteStream(Swap swap)
    : m_position(0)
    , m_swap(swap)
{

}

ByteStream::ByteStream(const std::string &buffer)
    : m_buffer{std::vector<unsigned char>(buffer.begin(), buffer.end())}
    , m_position{0}
    , m_swap{Swap::NoSwapEndian}
{
    
}

ByteStream::ByteStream(const std::vector<unsigned char> &buffer)
    : m_buffer{buffer}
    , m_position{0}
    , m_swap{Swap::NoSwapEndian}
{

}

ByteStream::~ByteStream()
{

}

ByteStream& ByteStream::operator=(const ByteStream &other)
{
    if(this != &other) {
        m_buffer    = other.m_buffer;
        m_position  = other.m_position;
        m_swap      = other.m_swap;
    }
    return *this;
}

ByteStream& ByteStream::operator=(ByteStream &&other) noexcept
{
    if(this != &other) {
        m_buffer    = other.m_buffer;
        m_position  = other.m_position;
        m_swap      = other.m_swap;
    }
    return *this;
}

bool ByteStream::operator==(const ByteStream &other)
{
    if(this == &other) {
        return true;
    } 
    
    if(m_position != other.m_position
       || size() != other.size()) {
        return false;
    }
    for(size_t i = 0; i < m_buffer.size(); ++i) {
        if(m_buffer[i] != other.m_buffer[i]) {
            return false;
        }
    }

    return true;
}

bool ByteStream::operator!=(const ByteStream &other)
{
    return !(*this == other);
}

size_t ByteStream::availableBytes() const
{
    if(m_position > m_buffer.size()) {
        return EndOfStream;
    } else {
        return m_buffer.size() - m_position;
    }
}

size_t ByteStream::size() const
{
    return m_buffer.size();
}

bool ByteStream::good() const
{
    return availableBytes() != EndOfStream;
}

void ByteStream::clear()
{
    m_buffer.clear();
    m_position = 0;
}

void ByteStream::reset()
{
    m_position = 0;
}

size_t ByteStream::getPosition() const
{
    return m_position;
}

void ByteStream::setPosition(size_t pos)
{
    m_position = pos;
}

bool ByteStream::isSwapSet() const
{
    return m_swap == Swap::SwapEndian;
}

ByteStream::Swap ByteStream::getSwap() const
{
    return m_swap;
}

void ByteStream::setSwap(Swap swap)
{
    m_swap = swap;
}

const unsigned char* ByteStream::rdbuf()
{
    return m_buffer.data();
}

std::vector<unsigned char> ByteStream::vbuf()
{
    return m_buffer;
}

bool ByteStream::readString(std::string &str, const int16_t length)
{
    if(availableBytes() < static_cast<size_t>(length)) {
        return EndOfStream;
    }

    size_t idx = str.length();
    str.resize(str.size() + length);
    std::memcpy(str.data() + idx, &m_buffer[m_position], length);
    m_position += length;

    return Success;
}

} // namespace util