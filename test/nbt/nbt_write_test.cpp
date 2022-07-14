// AwesomeMC
#include <AwesomeMC/nbt/nbt_write.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/nbt/tags/tags.hpp>

// gtest
#include <gtest/gtest.h>

TEST(nbt_write, writeNbtFile)
{
    // Setup CompoundTag Level 1
    amc::ByteTag *byteTag_1             = new amc::ByteTag("Level 1 - ByteTag", 123);
    amc::ShortTag *shortTag_1           = new amc::ShortTag("Level 0 - ShortTag", 0x1234);
    amc::IntTag *intTag_1               = new amc::IntTag("Level 0 - IntTag", 0x12345678);
    amc::FloatTag *floatTag_1           = new amc::FloatTag("Level 0 - FloatTag", -555.666f);
    amc::StringTag *stringTag_1         = new amc::StringTag("Level 0 - StringTag", "String");


    // Setup NBT structure Level 0
    amc::ByteTag *byteTag_0             = new amc::ByteTag("Level 0 - ByteTag", 56);
    amc::ShortTag *shortTag_0           = new amc::ShortTag("Level 0 - ShortTag", 0x1234);
    amc::IntTag *intTag_0               = new amc::IntTag("Level 0 - IntTag", 0x12345678);
    amc::LongTag *longTag_0             = new amc::LongTag("Level 0 - LongTag", 0x1234567890ABCDEF);
    amc::FloatTag *floatTag_0           = new amc::FloatTag("Level 0 - FloatTag", 3.5678f);
    amc::DoubleTag *doubleTag_0         = new amc::DoubleTag("Level 0 - DoubleTag", 123456.123456789);
    amc::StringTag *stringTag_0         = new amc::StringTag("Level 0 - StringTag", "Test");
    amc::ByteArrayTag *byteArrayTag_0   = new amc::ByteArrayTag("Level 0 - ByteArrayTag", {-1, 0, 1});
    amc::IntArrayTag *intArrayTag_0     = new amc::IntArrayTag("Level 0 - IntArrayTag", {-10, 0, 10});
    amc::LongArrayTag *longArrayTag_0   = new amc::LongArrayTag("Level 0 - LongArrayTag", {-100, 0, 100});
    amc::CompoundTag *compoundTag_0     = new amc::CompoundTag("Level 0 - CompoundTag", {
        byteTag_1, shortTag_1, intTag_1, floatTag_1, stringTag_1
    });
    // !!! Attention list items are stored (by defintion) without names or types, thats why the name must be empty.
    amc::ListTag * listTag_0            = new amc::ListTag("Level 0 - ListTag", amc::TagType::String, {
        new amc::StringTag("", "#1"),
        new amc::StringTag("", "#2"),
        new amc::StringTag("", "#3")
    });
    amc::CompoundTag *cTag = new amc::CompoundTag("Level 0", {
        byteTag_0, shortTag_0, intTag_0, longTag_0, floatTag_0, doubleTag_0, stringTag_0,
        byteArrayTag_0, intArrayTag_0, longArrayTag_0, compoundTag_0, listTag_0
    });

    // Save the file
    const std::string filename = "writeNbtFile_test.nbt";
    bool ret = amc::writeNbtFile(filename, cTag, amc::CompressionType::GZip);
    EXPECT_TRUE(ret);

    // Read the file again
    std::unique_ptr<amc::CompoundTag> compoundPtr = amc::readNbtFile(filename);

    // Compare Read and Constructed CompoundTag
    EXPECT_TRUE(*compoundPtr.get() == *cTag);

    delete cTag;
}