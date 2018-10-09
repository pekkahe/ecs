#include <Precompiled.hpp>

#include <component/Database.hpp>
#include <component/Query.hpp>
#include <component/TestComponents.hpp>

using namespace eng;

TEST(Query, Simple)
{
    Database database;
    auto id = database.createEntity();

    auto& boolTable = database.createTable<BoolComponent>();
    boolTable.assign(id, BoolComponent(true));

    int executeCount = 0;
    EntityId executedId = InvalidId;

    //query(database)
    //    .hasComponent<BoolComponent>()
    //    .execute([&](EntityId id, const BoolComponent& component)
    //{
    //    executedId = id;
    //    executeCount++;
    //});

    ASSERT_EQ(1, executeCount);
    ASSERT_EQ(executedId, id);

    // todo: difference to assert?
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

//TEST(Query, Simple_2) 
//{
//    Database database;
//
//    std::vector<EntityId> ids;
//    ids.emplace_back(database.createEntity());
//    ids.emplace_back(database.createEntity());
//    ids.emplace_back(database.createEntity());
//
//    auto& boolTable = database.createTable<BoolComponent>();
//    auto& numberTable = database.createTable<NumberComponent>();
//    auto& textTable = database.createTable<TextComponent>();
//
//    boolTable.assign(ids[0], BoolComponent(true));
//    boolTable.assign(ids[1], BoolComponent(false));
//    boolTable.assign(ids[2], BoolComponent(true));
//
//    numberTable.assign(ids[0], NumberComponent(10));
//    numberTable.assign(ids[1], NumberComponent(0));
//
//    textTable.assign(ids[1], TextComponent("id2"));
//    textTable.assign(ids[2], TextComponent("id3"));
//
//    // todo: more complex query...
//    query(database)
//        .hasComponent<BoolComponent>()
//        .execute([&](EntityId id, const BoolComponent& boolComponent)
//    {
//        // is executed once!
//    });
//
//    EXPECT_EQ(1, 1);
//    EXPECT_TRUE(true);
//}