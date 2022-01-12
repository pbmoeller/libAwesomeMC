#ifndef AWESOMEMC_NBT_TAGS_INT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_INT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <string>

namespace nbt
{

class IntTag : public AbstractTag
{
public:
    enum { Type = static_cast<int>(TagType::Int) };

    IntTag();
    IntTag(const IntTag &other);
    IntTag(IntTag &&other) noexcept;
    IntTag(const std::string &name);
    IntTag(int32_t value);
    IntTag(const std::string &name, int32_t value);
    virtual ~IntTag();

    IntTag& operator=(const IntTag &other);
    IntTag& operator=(IntTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override {
        return TagType::Int;
    }

    std::vector<unsigned char> getData(bool isListEntry) override;

    int32_t getValue() const;
    void setValue(int32_t value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    int32_t m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_INT_TAG_HPP