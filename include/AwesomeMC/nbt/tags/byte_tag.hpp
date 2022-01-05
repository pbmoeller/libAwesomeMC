#ifndef NBT_TAGS_BYTE_TAG_HPP
#define NBT_TAGS_BYTE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <string>

namespace nbt
{

class ByteTag : public AbstractTag
{
public:
    enum { Type = TagType::Byte };

    ByteTag();
    ByteTag(const ByteTag &other);
    ByteTag(ByteTag &&other) noexcept;
    ByteTag(const std::string &name);
    ByteTag(char value);
    ByteTag(const std::string &name, char value);
    virtual ~ByteTag();

    ByteTag& operator=(const ByteTag &other);
    ByteTag& operator=(ByteTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    char getValue() const;
    void setValue(char value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    char m_value;
};

} // namespace nbt

#endif // NBT_TAGS_BYTE_TAG_HPP