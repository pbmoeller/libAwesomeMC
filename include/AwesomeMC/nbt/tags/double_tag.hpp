#ifndef AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP
#define AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <string>

namespace nbt
{

class DoubleTag : public AbstractTag
{
public:
    enum { Type = TagType::Double };

    DoubleTag();
    DoubleTag(const DoubleTag &other);
    DoubleTag(DoubleTag &&other) noexcept;
    DoubleTag(const std::string &name);
    DoubleTag(double value);
    DoubleTag(const std::string &name, double value);
    virtual ~DoubleTag();

    DoubleTag& operator=(const DoubleTag &other);
    DoubleTag& operator=(DoubleTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    double getValue() const;
    void setValue(double value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    double m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP