#ifndef AWESOMEMC_ANVIL_REGION_HEADER_HPP
#define AWESOMEMC_ANVIL_REGION_HEADER_HPP

// AwesomeMC
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/anvil/chunk_info.hpp>

// STL
#include <array>
#include <vector>

namespace anvil
{

class RegionHeader
{
public:
    RegionHeader();
    RegionHeader(const RegionHeader &other);
    RegionHeader(RegionHeader &&other) noexcept;
    RegionHeader(const std::array<ChunkInfo, ChunkCount> &info);
    virtual ~RegionHeader();

    RegionHeader& operator=(const RegionHeader &other);
    RegionHeader& operator=(RegionHeader &&other) noexcept;

    bool operator==(const RegionHeader &other);
    bool operator!=(const RegionHeader &other);

    unsigned int getRegionCount() const;
    std::vector<char> getRegionData() const;

    const std::array<ChunkInfo, ChunkCount>& getChunkInfo() const;
    ChunkInfo& getChunkInfoAt(unsigned int index);
    const ChunkInfo& getChunkInfoAt(unsigned int index) const;

    void setChunkInfo(const std::array<ChunkInfo, ChunkCount> &info);
    void setChunkInfoAt(unsigned int index, const ChunkInfo &info);

private:
    std::array<ChunkInfo, ChunkCount> *m_chunkInfo;
};

} // namespace anvil

#endif // AWESOMEMC_ANVIL_REGION_HEADER_HPP