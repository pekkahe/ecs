#include <Precompiled.hpp>

#include <core/ecs/Table.hpp>
#include <core/ecs/TestComponents.hpp>

using namespace eng;

TEST(Table, Assign)
{
    Table<BoolComponent> table;
    EntityId id = 100u;

    table.assign(id, BoolComponent(true));

    EXPECT_EQ(1u, table.size());
    EXPECT_TRUE(table[id] != nullptr);
    EXPECT_EQ(true, table[id]->value);
}

TEST(Table, Remove)
{
    Table<BoolComponent> table;
    EntityId id = 100u;

    table.assign(id, BoolComponent(true));

    EXPECT_EQ(1u, table.size());
    EXPECT_TRUE(table[id] != nullptr);
    EXPECT_EQ(true, table[id]->value);

    table.remove(id);

    EXPECT_EQ(0u, table.size());
    EXPECT_FALSE(table[id] != nullptr);
}
