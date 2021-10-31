#ifndef NBT_ABSTRACT_TAG_HPP
#define NBT_ABSTRACT_TAG_HPP

#include <string>
#include <vector>

namespace nbt
{

enum class TagType : unsigned char
{
    End         = 0,
    Byte        = 1,
    Short       = 2,
    Int         = 3,
    Long        = 4,
    Float       = 5,
    Double      = 6,
    ByteArray   = 7,
    String      = 8,
    List        = 9,
    Compound    = 10,
    IntArray    = 11,
    LongArray   = 12,
};

class AbstractTag
{
public:
    AbstractTag();
    AbstractTag(const AbstractTag &other);
    AbstractTag(AbstractTag &&other) noexcept;
    AbstractTag(const std::string &name);
    virtual ~AbstractTag();

    AbstractTag& operator=(const AbstractTag &other);
    AbstractTag& operator=(AbstractTag &&other) noexcept;

    constexpr virtual TagType getType() const;

    virtual std::vector<unsigned char> getData(bool isListEntry) = 0;

    std::string getName() const;
    void setName(const std::string &name);

protected:
    virtual bool isEqual(const AbstractTag &other) const;

    friend bool operator==(const AbstractTag &lhs,
                           const AbstractTag &rhs);
    friend bool operator!=(const AbstractTag &lhs,
                           const AbstractTag &rhs);

protected:
    std::string m_name;
};

} // namespace nbt

#endif // NBT_ABSTRACT_TAG_HPP