#ifndef LIBAWESOMEANVIL_REGION_HEADER_HPP
#define LIBAWESOMEANVIL_REGION_HEADER_HPP

#include "constants.hpp"
#include "chunk_info.hpp"

// STL
#include <vector>

namespace anvil
{

class RegionHeader
{
public:
    RegionHeader();
    RegionHeader(const RegionHeader &other);
    RegionHeader(RegionHeader &&other) noexcept;
    RegionHeader(const ChunkInfo (&info)[ChunkCount]);
    virtual ~RegionHeader();

    RegionHeader& operator=(const RegionHeader &other);
    RegionHeader& operator=(RegionHeader &&other) noexcept;

    bool operator==(const RegionHeader &other);
    bool operator!=(const RegionHeader &other);

    unsigned int getRegionCount() const;
    std::vector<char> getRegionData() const;

    const ChunkInfo (& getChunkInfo() const)[ChunkCount];
    ChunkInfo& getChunkInfoAt(unsigned int index);
    const ChunkInfo& getChunkInfoAt(unsigned int index) const;

    void setChunkInfo(const ChunkInfo (&info)[ChunkCount]);
    void setChunkInfoAt(unsigned int index, const ChunkInfo &info);

private:
    ChunkInfo m_info[ChunkCount];
};

} // namespace anvil

#endif // LIBAWESOMEANVIL_REGION_HEADER_HPP