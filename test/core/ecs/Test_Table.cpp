// #include <Common.hpp>
#include <test/core/ecs/Components.hpp>

#include <core/ecs/Table.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ecs;

TEST(Table, Assign)
{
    Table<test::BoolComponent> table;
    EntityId id = 100u;

    table.assign(id, test::BoolComponent{true});

    EXPECT_EQ(1u, table.size());
    EXPECT_TRUE(table[id] != nullptr);
    EXPECT_EQ(true, table[id]->value);
}

TEST(Table, Remove)
{
    Table<test::BoolComponent> table;
    EntityId id = 100u;

    table.assign(id, test::BoolComponent{true});

    EXPECT_EQ(1u, table.size());
    EXPECT_TRUE(table[id] != nullptr);
    EXPECT_EQ(true, table[id]->value);

    table.remove(id);

    EXPECT_EQ(0u, table.size());
    EXPECT_FALSE(table[id] != nullptr);
}
