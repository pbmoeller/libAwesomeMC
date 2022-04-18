#ifndef AWESOMEMC_NBT_NBT_PRINT_HPP
#define AWESOMEMC_NBT_NBT_PRINT_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/tag_type.hpp>
#include <AwesomeMC/nbt/tags/tags.hpp>
#include <AwesomeMC/util/indent.hpp>

// STL
#include <sstream>
#include <iomanip>

namespace amc
{

std::string printNbtData(const AbstractTag *root,
                         bool printArrayContent = false);

void printNbtChildTag(const AbstractTag *tag,
                      std::stringstream &sstr,
                      Indent indent,
                      bool printArrayContent = false);

template<typename T, TagType TAG>
std::string printTagName(const ValueTag<T, TAG> &tag) {
    std::stringstream sstr;
    sstr << "TAG_" << getTagTypeName(TAG) << "(\"" << tag.getName() << "\"): ";
    return sstr.str();
}

template<typename T, TagType TAG>
std::string printTagName(const ArrayTag<T, TAG> &tag) {
    std::stringstream sstr;
    sstr << "TAG_" << getTagTypeName(TAG) << "(\"" << tag.getName() << "\"): "
         << tag.size() << " entries";
    return sstr.str();
}

std::string printTagName(const CompoundTag &tag) {
    std::stringstream sstr;
    sstr << "TAG_" << getTagTypeName(tag.getType()) << "(\"" << tag.getName() << "\"): "
        << tag.size() << " entries";
    return sstr.str();
}

std::string printTagName(const ListTag &tag) {
    std::stringstream sstr;
    sstr << "TAG_" << getTagTypeName(tag.getType()) << "(\"" << tag.getName() << "\"): "
         << tag.size() << " entries of type " << getTagTypeName(tag.getListType());
    return sstr.str();
}

template<typename T, TagType TAG>
std::string printTagValue(const ValueTag<T, TAG> &tag)
{
    std::stringstream sstr;
    if constexpr(TAG == TagType::Byte || TAG == TagType::Short) {
        sstr << static_cast<int>(tag.getValue()) << "\n";
    } else {
        if constexpr(TAG == TagType::Float) {
            sstr << std::setprecision(8);
        } else if constexpr(TAG == TagType::Double) {
            sstr << std::setprecision(16);
        }
        sstr << tag.getValue() << "\n";
    }
    return sstr.str();
}

template<typename T, TagType TAG>
std::string printTagValue(const ArrayTag<T, TAG> &tag,
                          Indent indent, 
                          bool printArrayContent)
{
    std::stringstream sstr;
    if(printArrayContent) {
        sstr << "\n" << indent << "{\n";
        int64_t i = 0;
        for(i = 0; i < tag.size() - 1; ++i) {
            sstr << " " << static_cast<int64_t>(tag[i]) << ",";
        }
        sstr << " " << static_cast<int64_t>(tag[i]) << "\n";
        sstr << indent << "}\n";
    } else {
        sstr << " [" << tag.size() << " bytes]\n";
    }
    return sstr.str();
}

} // namespace amc

#endif // AWESOMEMC_NBT_NBT_PRINT_HPP