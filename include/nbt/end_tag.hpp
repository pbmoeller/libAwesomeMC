#ifndef NBT_END_TAG_HPP
#define NBT_END_TAG_HPP

#include "abstract_tag.hpp"

namespace nbt
{

class EndTag : public AbstractTag
{
public:
    EndTag();
    EndTag(const EndTag &other);
    EndTag(EndTag &&other) noexcept;
    virtual ~EndTag();

    EndTag& operator=(const EndTag &other);
    EndTag& operator=(EndTag &&other) noexcept;

    bool operator==(const AbstractTag &other);
    bool operator!=(const AbstractTag &other);

    std::vector<unsigned char> getData(bool value) override;
};

} // namespace nbt

#endif // NBT_END_TAG_HPP