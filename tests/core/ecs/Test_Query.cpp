#include <Precompiled.hpp>

#include <core/ecs/Database.hpp>
#include <core/ecs/Query.hpp>
#include <core/ecs/TestComponents.hpp>

using namespace eng;

TEST(Query, IsExecutedOnceWhenComponentMatches)
{
    Database database;
    
    auto& table = database.createTable<BoolComponent>();
    auto id = database.createEntity();

    table.assign(id, BoolComponent(true));

    using ResultType = std::pair<EntityId, bool>;
    std::vector<ResultType> results;

    query(database)
        .hasComponent<BoolComponent>()
        .execute([&](EntityId id, const BoolComponent& c)
    {
        results.emplace_back(std::make_pair(id, c.value));
    });

    ASSERT_EQ(1u,   results.size());
    EXPECT_EQ(id,   results[0].first);
    EXPECT_EQ(true, results[0].second);
}

TEST(Query, IsExecutedOnceWhenAllComponentsMatch)
{
    Database database;

    auto& table1 = database.createTable<BoolComponent>();
    auto& table2 = database.createTable<NumberComponent>();
    auto& table3 = database.createTable<TextComponent>();

    auto id = database.createEntity();

    table1.assign(id, BoolComponent(true));
    table2.assign(id, NumberComponent(10));
    table3.assign(id, TextComponent("id"));

    using ResultType = std::tuple<EntityId, bool, int, std::string>;
    std::vector<ResultType> results;

    query(database)
        .hasComponent<BoolComponent>()
        .hasComponent<NumberComponent>()
        .hasComponent<TextComponent>()
        .execute([&](
            EntityId id, 
            const BoolComponent& c1,
            const NumberComponent& c2,
            const TextComponent& c3)
    {
        results.emplace_back(std::make_tuple(
            id, 
            c1.value,
            c2.value,
            c3.value));
    });

    ASSERT_EQ(1u,   results.size());
    EXPECT_EQ(id,   std::get<0>(results[0]));
    EXPECT_EQ(true, std::get<1>(results[0]));
    EXPECT_EQ(10,   std::get<2>(results[0]));
    EXPECT_EQ("id", std::get<3>(results[0]));
}

TEST(Query, IsExecutedOnceForEachEntity)
{
    Database database;

    auto& table1 = database.createTable<BoolComponent>();
    auto& table2 = database.createTable<NumberComponent>();
    auto& table3 = database.createTable<TextComponent>();

    std::vector<EntityId> ids;
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());

    table1.assign(ids[0], BoolComponent(true));
    table2.assign(ids[0], NumberComponent(10));
    table3.assign(ids[0], TextComponent("id0"));
    table2.assign(ids[1], NumberComponent(20));
    table1.assign(ids[1], BoolComponent(false));
    table1.assign(ids[2], BoolComponent(true));
    table3.assign(ids[2], TextComponent("id2"));

    {
        using ResultType = std::tuple<EntityId, bool>;
        std::vector<ResultType> results;

        query(database)
            .hasComponent<BoolComponent>()
            .execute([&](
                EntityId id,
                const BoolComponent& c)
        {
            results.emplace_back(std::make_tuple(
                id,
                c.value));
        });

        ASSERT_EQ(3u,       results.size());
        EXPECT_EQ(ids[0],   std::get<0>(results[0]));
        EXPECT_EQ(true,     std::get<1>(results[0]));
        EXPECT_EQ(ids[1],   std::get<0>(results[1]));
        EXPECT_EQ(false,    std::get<1>(results[1]));
        EXPECT_EQ(ids[2],   std::get<0>(results[2]));
        EXPECT_EQ(true,     std::get<1>(results[2]));
    }

    {
        using ResultType = std::tuple<EntityId, bool, int>;
        std::vector<ResultType> results;

        query(database)
            .hasComponent<BoolComponent>()
            .hasComponent<NumberComponent>()
            .execute([&](
                EntityId id,
                const BoolComponent& c1,
                const NumberComponent& c2)
        {
            results.emplace_back(std::make_tuple(
                id,
                c1.value,
                c2.value));
        });

        ASSERT_EQ(2u,       results.size());
        EXPECT_EQ(ids[0],   std::get<0>(results[0]));
        EXPECT_EQ(true,     std::get<1>(results[0]));
        EXPECT_EQ(10,       std::get<2>(results[0]));
        EXPECT_EQ(ids[1],   std::get<0>(results[1]));
        EXPECT_EQ(false,    std::get<1>(results[1]));
        EXPECT_EQ(20,       std::get<2>(results[1]));
    }

    {
        using ResultType = std::tuple<EntityId, bool, int, std::string>;
        std::vector<ResultType> results;

        query(database)
            .hasComponent<BoolComponent>()
            .hasComponent<NumberComponent>()
            .hasComponent<TextComponent>()
            .execute([&](
                EntityId id,
                const BoolComponent& c1,
                const NumberComponent& c2,
                const TextComponent& c3)
        {
            results.emplace_back(std::make_tuple(
                id,
                c1.value,
                c2.value,
                c3.value));
        });

        ASSERT_EQ(1u,       results.size());
        EXPECT_EQ(ids[0],   std::get<0>(results[0]));
        EXPECT_EQ(true,     std::get<1>(results[0]));
        EXPECT_EQ(10,       std::get<2>(results[0]));
        EXPECT_EQ("id0",    std::get<3>(results[0]));
    }
}

TEST(Query, IdsForMatchingEntities)
{
    Database database;

    auto& table1 = database.createTable<BoolComponent>();
    auto& table2 = database.createTable<NumberComponent>();
    auto& table3 = database.createTable<TextComponent>();

    std::vector<EntityId> ids;
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());

    table1.assign(ids[0], BoolComponent(true));
    table2.assign(ids[0], NumberComponent(0));
    table3.assign(ids[0], TextComponent(""));
    table2.assign(ids[1], NumberComponent(0));
    table1.assign(ids[1], BoolComponent(true));
    table1.assign(ids[2], BoolComponent(true));
    table3.assign(ids[2], TextComponent(""));

    {
        auto results = query(database)
            .hasComponent<BoolComponent>()
            .ids();

        ASSERT_EQ(3u, results.size());
        EXPECT_EQ(ids[0], results[0]);
        EXPECT_EQ(ids[1], results[1]);
        EXPECT_EQ(ids[2], results[2]);
    }

    {
        auto results = query(database)
            .hasComponent<BoolComponent>()
            .hasComponent<NumberComponent>()
            .ids();

        ASSERT_EQ(2u, results.size());
        EXPECT_EQ(ids[0], results[0]);
        EXPECT_EQ(ids[1], results[1]);
    }

    {
        auto results = query(database)
            .hasComponent<BoolComponent>()
            .hasComponent<NumberComponent>()
            .hasComponent<TextComponent>()
            .ids();

        ASSERT_EQ(1u,       results.size());
        EXPECT_EQ(ids[0],   results[0]);
    }
}

TEST(Query, FindComponentOfFirstMatchingEntity)
{
    Database database;

    auto& table1 = database.createTable<BoolComponent>();
    auto& table2 = database.createTable<NumberComponent>();
    auto& table3 = database.createTable<TextComponent>();

    std::vector<EntityId> ids;
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());

    table1.assign(ids[0], BoolComponent(true));
    table2.assign(ids[1], NumberComponent(10));
    table1.assign(ids[1], BoolComponent(false));
    table1.assign(ids[2], BoolComponent(false));
    table2.assign(ids[2], NumberComponent(0));

    auto result1 = query(database).find<BoolComponent>();
    auto result2 = query(database).find<NumberComponent>();
    auto result3 = query(database).find<TextComponent>();

    ASSERT_TRUE(result1 != nullptr);
    EXPECT_EQ(true, result1->value);
    ASSERT_TRUE(result2 != nullptr);
    EXPECT_EQ(10, result2->value);
    ASSERT_TRUE(result3 == nullptr);
}

TEST(Query, PerformanceTest)
{
    Database database;

    auto& table1 = database.createTable<BoolComponent>();
    auto& table2 = database.createTable<NumberComponent>();
    auto& table3 = database.createTable<TextComponent>();

    size_t count = 2000u;

    std::vector<EntityId> ids;
    for (size_t i = 0; i < count; ++i)
    { 
        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), BoolComponent(true));
        
        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), BoolComponent(false));
        table2.assign(ids.back(), NumberComponent(10));

        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), BoolComponent(true));
        table3.assign(ids.back(), TextComponent("text"));

        ids.emplace_back(database.createEntity());
        table2.assign(ids.back(), NumberComponent(100));
        table3.assign(ids.back(), TextComponent("text"));

        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), BoolComponent(false));
        table2.assign(ids.back(), NumberComponent(1000));
        table3.assign(ids.back(), TextComponent("text"));
    }
    
    size_t found = 0u;
    Timer timer = Timer::start();

    query(database)
        .hasComponent<BoolComponent>()
        .hasComponent<NumberComponent>()
        .hasComponent<TextComponent>()
        .execute([&](
            EntityId id,
            const BoolComponent& c1,
            const NumberComponent& c2,
            const TextComponent& c3) 
    {
        found++;
    });

    double elapsed = timer.reset();
    EXPECT_EQ(found, count);

    std::cout <<
        "Entities: " << ids.size() << std::endl <<
        "Matches:  " << found << std::endl <<
        "Elapsed:  " << elapsed << " ms" << std::endl;
}