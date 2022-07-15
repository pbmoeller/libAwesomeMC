#ifndef AWESOMEMC_ANVIL_REGION_HEADER_HPP
#define AWESOMEMC_ANVIL_REGION_HEADER_HPP

// AwesomeMC
#include <AwesomeMC/constants.hpp>

// STL
#include <array>
#include <vector>

namespace amc
{

class RegionHeader
{
public:
    RegionHeader();
    RegionHeader(const RegionHeader &other);
    RegionHeader(RegionHeader &&other) noexcept;
    RegionHeader(const std::vector<unsigned char> &data);
    RegionHeader(std::vector<unsigned char> &&data);
    virtual ~RegionHeader();

    RegionHeader &operator=(const RegionHeader &other);
    RegionHeader &operator=(RegionHeader &&other) noexcept;

    bool operator==(const RegionHeader &other);
    bool operator!=(const RegionHeader &other);

    int getChunkCount() const;
    std::vector<unsigned char> getData() const;

    bool isEmpty(const int index) const;

    int getOffset(const int index) const;
    int getByteOffset(const int index) const;
    int getSize(const int index) const;
    int getByteSize(const int index) const;
    int getTimestamp(const int index) const;

    void setChunkData(const int index,
                      const int offset,
                      const int size,
                      const int timestamp);

private:
    std::vector<unsigned char> m_data;
};

} // namespace amc

#endif // AWESOMEMC_ANVIL_REGION_HEADER_HPP