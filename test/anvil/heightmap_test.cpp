// AwesomeMC
#include <AwesomeMC/anvil/heightmap.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class HeightMapFixture : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // Init Map 1
        std::array<int, amc::BlockCount> data;
        for(int i = 0; i < amc::BlockCount; ++i) {
            data[i] = i;
        }
        map1 = new amc::HeightMap(3, 4, amc::HeightMap::MapType::WorldSurface, data);

        // Init Map 2
        map2 = new amc::HeightMap(-512, 6667, amc::HeightMap::MapType::MotionBlockingNoLeaves);

        // Init Map 3
        map3 = new amc::HeightMap(-512, 6667, amc::HeightMap::MapType::MotionBlockingNoLeaves);

        // Init Map 4
        map4 = new amc::HeightMap();

        // Init Map 5
        std::array<int, amc::BlockCount> data5;
        for(int x = 0; x < amc::BlockWidth; ++x) {
            for(int z = 0; z < amc::BlockWidth; ++z) {
                data5[amc::BlockWidth * z + x] = amc::BlockWidth * z + x;
            }
        }
        map5 = new amc::HeightMap(1, 2, amc::HeightMap::MapType::WorldSurface, data5);
    }

    virtual void TearDown()
    {
        delete map1;
        delete map2;
        delete map3;
        delete map4;
        delete map5;
    }

    amc::HeightMap *map1 = nullptr;
    amc::HeightMap *map2 = nullptr;
    amc::HeightMap *map3 = nullptr;
    amc::HeightMap *map4 = nullptr;
    amc::HeightMap *map5 = nullptr;
};

TEST_F(HeightMapFixture, MapType)
{
    EXPECT_EQ(static_cast<int>(amc::HeightMap::MapType::Unknown),                 -1);
    EXPECT_EQ(static_cast<int>(amc::HeightMap::MapType::MotionBlocking),          0);
    EXPECT_EQ(static_cast<int>(amc::HeightMap::MapType::MotionBlockingNoLeaves),  1);
    EXPECT_EQ(static_cast<int>(amc::HeightMap::MapType::OceanFloor),              2);
    EXPECT_EQ(static_cast<int>(amc::HeightMap::MapType::WorldSurface),            3);
}

TEST_F(HeightMapFixture, Constructor)
{
    amc::HeightMap map;
    EXPECT_EQ(map.getChunkX(), std::numeric_limits<int>::max());
    EXPECT_EQ(map.getChunkZ(), std::numeric_limits<int>::max());
    EXPECT_EQ(map.getMapType(), amc::HeightMap::MapType::Unknown);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), 0);
    }
}

TEST(HeiHeightMapFixtureghtMap, Constructor_2)
{
    amc::HeightMap map(45, -23);
    EXPECT_EQ(map.getChunkX(), 45);
    EXPECT_EQ(map.getChunkZ(), -23);
    EXPECT_EQ(map.getMapType(), amc::HeightMap::MapType::Unknown);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), 0);
    }
}

TEST_F(HeightMapFixture, Constructor_3)
{
    amc::HeightMap map(12, 10, amc::HeightMap::MapType::MotionBlocking);
    EXPECT_EQ(map.getChunkX(), 12);
    EXPECT_EQ(map.getChunkZ(), 10);
    EXPECT_EQ(map.getMapType(), amc::HeightMap::MapType::MotionBlocking);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), 0);
    }
}

TEST_F(HeightMapFixture, Constructor_4)
{
    std::array<int, amc::BlockCount> data;
    for(int i = 0; i < amc::BlockCount; ++i) {
        data[i] = i;
    }
    amc::HeightMap map(3, 4, amc::HeightMap::MapType::WorldSurface, data);
    EXPECT_EQ(map.getChunkX(), 3);
    EXPECT_EQ(map.getChunkZ(), 4);
    EXPECT_EQ(map.getMapType(), amc::HeightMap::MapType::WorldSurface);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), i);
    }
}

TEST_F(HeightMapFixture, CopyConstructor)
{
    std::array<int, amc::BlockCount> data;
    for(int i = 0; i < amc::BlockCount; ++i) {
        data[i] = i;
    }
    amc::HeightMap map(3, 4, amc::HeightMap::MapType::WorldSurface, data);
    amc::HeightMap mapCopy(map);
    EXPECT_EQ(mapCopy.getChunkX(), 3);
    EXPECT_EQ(mapCopy.getChunkZ(), 4);
    EXPECT_EQ(mapCopy.getMapType(), amc::HeightMap::MapType::WorldSurface);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), mapCopy.getAt(i));
    }
}

TEST_F(HeightMapFixture, MoveConstructor)
{
    std::array<int, amc::BlockCount> data;
    for(int i = 0; i < amc::BlockCount; ++i) {
        data[i] = i;
    }
    amc::HeightMap map(3, 4, amc::HeightMap::MapType::WorldSurface, data);
    amc::HeightMap mapMove(std::move(map));
    EXPECT_EQ(mapMove.getChunkX(), 3);
    EXPECT_EQ(mapMove.getChunkZ(), 4);
    EXPECT_EQ(mapMove.getMapType(), amc::HeightMap::MapType::WorldSurface);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), mapMove.getAt(i));
    }
}

TEST_F(HeightMapFixture, CopyAssignment)
{
    std::array<int, amc::BlockCount> data;
    for(int i = 0; i < amc::BlockCount; ++i) {
        data[i] = i;
    }
    amc::HeightMap map(3, 4, amc::HeightMap::MapType::WorldSurface, data);
    amc::HeightMap mapCopy = map;
    EXPECT_EQ(mapCopy.getChunkX(), 3);
    EXPECT_EQ(mapCopy.getChunkZ(), 4);
    EXPECT_EQ(mapCopy.getMapType(), amc::HeightMap::MapType::WorldSurface);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), mapCopy.getAt(i));
    }
}

TEST_F(HeightMapFixture, MoveAssignment)
{
    std::array<int, amc::BlockCount> data;
    for(int i = 0; i < amc::BlockCount; ++i) {
        data[i] = i;
    }
    amc::HeightMap map(3, 4, amc::HeightMap::MapType::WorldSurface, data);
    amc::HeightMap mapMove = std::move(map);
    EXPECT_EQ(mapMove.getChunkX(), 3);
    EXPECT_EQ(mapMove.getChunkZ(), 4);
    EXPECT_EQ(mapMove.getMapType(), amc::HeightMap::MapType::WorldSurface);
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map.getAt(i), mapMove.getAt(i));
    }
}

TEST_F(HeightMapFixture, Equal)
{
    amc::HeightMap map;
    EXPECT_FALSE(*map1 == *map2);
    EXPECT_FALSE(*map1 == *map3);
    EXPECT_TRUE(*map2 == *map3);
    EXPECT_TRUE(*map4 == map);
}

TEST_F(HeightMapFixture, NotEqual)
{
    amc::HeightMap map;
    EXPECT_TRUE(*map1 != *map2);
    EXPECT_TRUE(*map1 != *map3);
    EXPECT_FALSE(*map2 != *map3);
    EXPECT_FALSE(*map4 != map);
}

TEST_F(HeightMapFixture, setMapType)
{
    amc::HeightMap map;
    EXPECT_EQ(map.getMapType(), amc::HeightMap::MapType::Unknown);
    map.setMapType(amc::HeightMap::MapType::WorldSurface);
    EXPECT_EQ(map.getMapType(), amc::HeightMap::MapType::WorldSurface);
}

TEST_F(HeightMapFixture, getMapType)
{
    EXPECT_EQ(amc::HeightMap::MapType::WorldSurface,            map1->getMapType());
    EXPECT_EQ(amc::HeightMap::MapType::MotionBlockingNoLeaves,  map2->getMapType());
    EXPECT_EQ(amc::HeightMap::MapType::MotionBlockingNoLeaves,  map3->getMapType());
}

TEST_F(HeightMapFixture, setChunkX)
{
    amc::HeightMap map;
    EXPECT_EQ(map.getChunkX(), std::numeric_limits<int>::max());
    map.setChunkX(888);
    EXPECT_EQ(map.getChunkX(), 888);
}

TEST_F(HeightMapFixture, getChunkX)
{
    EXPECT_EQ(map1->getChunkX(), 3);
    EXPECT_EQ(map2->getChunkX(), -512);
    EXPECT_EQ(map5->getChunkX(), 1);
}

TEST_F(HeightMapFixture, setChunkZ)
{
    amc::HeightMap map;
    EXPECT_EQ(map.getChunkZ(), std::numeric_limits<int>::max());
    map.setChunkZ(828);
    EXPECT_EQ(map.getChunkZ(), 828);
}

TEST_F(HeightMapFixture, getChunkZ)
{
    EXPECT_EQ(map1->getChunkZ(), 4);
    EXPECT_EQ(map2->getChunkZ(), 6667);
    EXPECT_EQ(map5->getChunkZ(), 2);
}

TEST_F(HeightMapFixture, setAt)
{
    amc::HeightMap map(3, 4, amc::HeightMap::MapType::WorldSurface);
    for(int i = 0; i < amc::BlockCount; ++i) {
        map.setAt(i, i);
    }
    EXPECT_TRUE(map == *map1);
}

TEST_F(HeightMapFixture, setAt_2)
{
    amc::HeightMap map(1, 2, amc::HeightMap::MapType::WorldSurface);
    for(int x = 0; x < amc::BlockWidth; ++x) {
        for(int z = 0; z < amc::BlockWidth; ++z) {
            map.setAt(x, z, amc::BlockWidth * z + x);
        }
    }
    EXPECT_TRUE(map == *map5);
}

TEST_F(HeightMapFixture, getAt)
{
    for(int i = 0; i < amc::BlockCount; ++i) {
        EXPECT_EQ(map1->getAt(i), i);
    }
}

TEST_F(HeightMapFixture, getAt_2)
{
    for(int x = 0; x < amc::BlockWidth; ++x) {
        for(int z = 0; z < amc::BlockWidth; ++z) {
            EXPECT_EQ(map5->getAt(x, z), amc::BlockWidth * z + x);
        }
    }
}

TEST_F(HeightMapFixture, getData)
{
    std::array<int, amc::BlockCount> &data = map1->getData();
    for(int x = 0; x < amc::BlockWidth; ++x) {
        for(int z = 0; z < amc::BlockWidth; ++z) {
            EXPECT_EQ(data[amc::BlockWidth * z + x], amc::BlockWidth * z + x);
        }
    }

    data[0] = 2;
    EXPECT_EQ(map1->getAt(0), 2);
}

TEST_F(HeightMapFixture, getData_const)
{
    const amc::HeightMap map(*map1);
    std::array<int, amc::BlockCount> data = map.getData();
    for(int x = 0; x < amc::BlockWidth; ++x) {
        for(int z = 0; z < amc::BlockWidth; ++z) {
            EXPECT_EQ(data[amc::BlockWidth * z + x], amc::BlockWidth * z + x);
        }
    }
}