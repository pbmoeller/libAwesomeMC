#ifndef ANVIL_ANVIL_READ_HPP
#define ANVIL_ANVIL_READ_HPP

// AwesomeMC
#include <AwesomeMC/anvil/region.hpp>

// STL
#include <string>
#include <fstream>

namespace anvil
{

Region loadRegion(const std::string &filename);

bool readRegionHeader(std::ifstream &filestream, Region &region);

bool readRegionChunks(std::ifstream &filestream, Region &region);

} // namespace anvil

#endif // ANVIL_ANVIL_READ_HPP