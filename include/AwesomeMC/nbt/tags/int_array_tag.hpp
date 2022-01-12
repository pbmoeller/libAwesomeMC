#ifndef AWESOMEMC_NBT_TAGS_INT_ARRAY_TAG_HPP
#define AWESOMEMC_NBT_TAGS_INT_ARRAY_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <cstdint>
#include <string>
#include <vector>

namespace nbt
{

class IntArrayTag : public AbstractTag
{
public:
    enum { Type = static_cast<int>(TagType::IntArray) };

    IntArrayTag();
    IntArrayTag(const IntArrayTag &other);
    IntArrayTag(IntArrayTag &&other) noexcept;
    IntArrayTag(const std::string &name);
    IntArrayTag(const std::vector<int32_t> &value);
    IntArrayTag(const std::string &name, const std::vector<int32_t> &value);
    virtual ~IntArrayTag();

    IntArrayTag& operator=(const IntArrayTag &other);
    IntArrayTag& operator=(IntArrayTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override {
        return TagType::IntArray;
    }

    std::vector<unsigned char> getData(bool isListEntry) override;

    bool isEmpty() const;
    void clear();
    bool erase(size_t index);
    bool insert(size_t index, int32_t value);
    void pushBack(int32_t value);
    size_t size() const;
    int32_t& at(size_t index);
    const int32_t& at(size_t index) const;

    std::vector<int32_t>& getValue();
    void setValue(const std::vector<int32_t> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    std::vector<int32_t> m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_INT_ARRAY_TAG_HPP