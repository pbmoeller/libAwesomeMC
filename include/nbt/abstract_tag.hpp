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
    AbstractTag(TagType type);
    AbstractTag(const std::string &name, TagType type);
    virtual ~AbstractTag();

    AbstractTag& operator=(const AbstractTag &other);
    AbstractTag& operator=(AbstractTag &&other) noexcept;

    virtual bool operator==(const AbstractTag &other);
    virtual bool operator!=(const AbstractTag &other);

    std::string getName() const;
    void setName(const std::string &name);

    TagType getType() const;
    void setType(TagType type);

    virtual std::vector<unsigned char> getData(bool isListEntry) = 0;

public:
    TagType m_type;
    std::string m_name;
};

} // namespace nbt

#endif // NBT_ABSTRACT_TAG_HPP