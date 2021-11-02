#ifndef NBT_TAGS_LONG_ARRAY_TAG_HPP
#define NBT_TAGS_LONG_ARRAY_TAG_HPP

// nbt
#include "abstract_tag.hpp"

// STL
#include <cstdint>
#include <string>
#include <vector>

namespace nbt
{

class LongArrayTag : public AbstractTag
{
public:
    LongArrayTag();
    LongArrayTag(const LongArrayTag &other);
    LongArrayTag(LongArrayTag &&other) noexcept;
    LongArrayTag(const std::string &name);
    LongArrayTag(const std::vector<int64_t> &value);
    LongArrayTag(const std::string &name, const std::vector<int64_t> &value);
    virtual ~LongArrayTag();

    LongArrayTag& operator=(const LongArrayTag &other);
    LongArrayTag& operator=(LongArrayTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    bool isEmpty() const;
    void clear();
    bool erase(size_t index);
    bool insert(size_t index, int64_t value);
    void pushBack(int64_t value);
    size_t size() const;
    int64_t& at(size_t index);
    const int64_t& at(size_t index) const;

    std::vector<int64_t>& getValue();
    void setValue(const std::vector<int64_t> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    std::vector<int64_t> m_value;
};

} // namespace nbt

#endif // NBT_TAGS_LONG_ARRAY_TAG_HPP