#ifndef NBT_DOUBLE_TAG_HPP
#define NBT_DOUBLE_TAG_HPP

// nbt
#include "nbt/abstract_tag.hpp"

// STL
#include <string>

namespace nbt
{

class DoubleTag : public AbstractTag
{
public:
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

#endif // NBT_DOUBLE_TAG_HPP