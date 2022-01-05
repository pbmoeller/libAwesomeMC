#ifndef NBT_TAGS_LONG_TAG_HPP
#define NBT_TAGS_LONG_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <string>

namespace nbt
{

class LongTag : public AbstractTag
{
public:
    enum { Type = TagType::Long };

    LongTag();
    LongTag(const LongTag &other);
    LongTag(LongTag &&other) noexcept;
    LongTag(const std::string &name);
    LongTag(int64_t value);
    LongTag(const std::string &name, int64_t value);
    virtual ~LongTag();

    LongTag& operator=(const LongTag &other);
    LongTag& operator=(LongTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    int64_t getValue() const;
    void setValue(int64_t value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    int64_t m_value;
};

} // namespace nbt

#endif // NBT_TAGS_LONG_TAG_HPP