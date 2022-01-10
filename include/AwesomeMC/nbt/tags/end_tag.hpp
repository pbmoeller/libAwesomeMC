#ifndef AWESOMEMC_NBT_TAGS_END_TAG_HPP
#define AWESOMEMC_NBT_TAGS_END_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

namespace nbt
{

class EndTag : public AbstractTag
{
public:
    enum { Type = TagType::End };

    EndTag();
    EndTag(const EndTag &other);
    EndTag(EndTag &&other) noexcept;
    virtual ~EndTag();

    EndTag& operator=(const EndTag &other);
    EndTag& operator=(EndTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

protected:
    virtual bool isEqual(const AbstractTag &other) const override;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_END_TAG_HPP