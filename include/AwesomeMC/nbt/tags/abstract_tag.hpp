#ifndef AWESOMEMC_NBT_TAGS_ABSTRACT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_ABSTRACT_TAG_HPP

// STL
#include <string>
#include <vector>
#include <cstdint>

namespace nbt
{

// Tag types to distinguish between types
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
    Unknown     = 255,
};

class AbstractTag
{
public:
    enum { Type = static_cast<int>(TagType::Unknown) };

public:
    // Constructors, Destructor & Assignments
    AbstractTag();
    AbstractTag(const AbstractTag &other);
    AbstractTag(AbstractTag &&other) noexcept;
    AbstractTag(const std::string &name);
    AbstractTag(std::string &&name);
    virtual ~AbstractTag();

    AbstractTag& operator=(const AbstractTag &other);
    AbstractTag& operator=(AbstractTag &&other) noexcept;

    // Tag functions
    virtual AbstractTag* clone() const = 0;

    constexpr virtual TagType getType() const {
        return TagType::End;
    }

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

template<typename T> inline T tag_cast(AbstractTag *item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    return int(Item::Type) == int(AbstractTag::Type)
        || (item && int(Item::Type) == int(item->getType())) ? static_cast<T>(item) : nullptr;
}

template<typename T> inline T tag_cast(const AbstractTag *item)
{
    typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
    return int(Item::Type) == int(AbstractTag::Type)
        || (item && int(Item::Type) == int(item->getType())) ? static_cast<T>(item) : nullptr;
}

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_ABSTRACT_TAG_HPP