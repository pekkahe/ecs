// #include <Common.hpp>

#include <test/core/ecs/Components.hpp>

#include <core/ecs/Database.hpp>
#include <core/ecs/Query.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ecs;

TEST(Query, IsExecutedOnceWhenComponentMatches)
{
    Database database;
    
    auto& table = database.createTable<test::BoolComponent>();
    auto id = database.createEntity();

    table.assign(id, test::BoolComponent{true});

    using ResultType = std::pair<EntityId, bool>;
    std::vector<ResultType> results;

    query(database)
        .hasComponent<test::BoolComponent>()
        .execute([&](EntityId id, const test::BoolComponent& c)
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

    auto& table1 = database.createTable<test::BoolComponent>();
    auto& table2 = database.createTable<test::NumberComponent>();
    auto& table3 = database.createTable<test::TextComponent>();

    auto id = database.createEntity();

    table1.assign(id, test::BoolComponent{true});
    table2.assign(id, test::NumberComponent{10});
    table3.assign(id, test::TextComponent{"id"});

    using ResultType = std::tuple<EntityId, bool, int, std::string>;
    std::vector<ResultType> results;

    query(database)
        .hasComponent<test::BoolComponent>()
        .hasComponent<test::NumberComponent>()
        .hasComponent<test::TextComponent>()
        .execute([&](
            EntityId id, 
            const test::BoolComponent& c1,
            const test::NumberComponent& c2,
            const test::TextComponent& c3)
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

    auto& table1 = database.createTable<test::BoolComponent>();
    auto& table2 = database.createTable<test::NumberComponent>();
    auto& table3 = database.createTable<test::TextComponent>();

    std::vector<EntityId> ids;
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());

    table1.assign(ids[0], test::BoolComponent{true});
    table2.assign(ids[0], test::NumberComponent{10});
    table3.assign(ids[0], test::TextComponent{"id0"});
    table2.assign(ids[1], test::NumberComponent{20});
    table1.assign(ids[1], test::BoolComponent{false});
    table1.assign(ids[2], test::BoolComponent{true});
    table3.assign(ids[2], test::TextComponent{"id2"});

    {
        using ResultType = std::tuple<EntityId, bool>;
        std::vector<ResultType> results;

        query(database)
            .hasComponent<test::BoolComponent>()
            .execute([&](
                EntityId id,
                const test::BoolComponent& c)
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
            .hasComponent<test::BoolComponent>()
            .hasComponent<test::NumberComponent>()
            .execute([&](
                EntityId id,
                const test::BoolComponent& c1,
                const test::NumberComponent& c2)
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
            .hasComponent<test::BoolComponent>()
            .hasComponent<test::NumberComponent>()
            .hasComponent<test::TextComponent>()
            .execute([&](
                EntityId id,
                const test::BoolComponent& c1,
                const test::NumberComponent& c2,
                const test::TextComponent& c3)
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

    auto& table1 = database.createTable<test::BoolComponent>();
    auto& table2 = database.createTable<test::NumberComponent>();
    auto& table3 = database.createTable<test::TextComponent>();

    std::vector<EntityId> ids;
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());

    table1.assign(ids[0], test::BoolComponent{true});
    table2.assign(ids[0], test::NumberComponent{0});
    table3.assign(ids[0], test::TextComponent{""});
    table2.assign(ids[1], test::NumberComponent{0});
    table1.assign(ids[1], test::BoolComponent{true});
    table1.assign(ids[2], test::BoolComponent{true});
    table3.assign(ids[2], test::TextComponent{""});

    {
        auto results = query(database)
            .hasComponent<test::BoolComponent>()
            .ids();

        ASSERT_EQ(3u, results.size());
        EXPECT_EQ(ids[0], results[0]);
        EXPECT_EQ(ids[1], results[1]);
        EXPECT_EQ(ids[2], results[2]);
    }

    {
        auto results = query(database)
            .hasComponent<test::BoolComponent>()
            .hasComponent<test::NumberComponent>()
            .ids();

        ASSERT_EQ(2u, results.size());
        EXPECT_EQ(ids[0], results[0]);
        EXPECT_EQ(ids[1], results[1]);
    }

    {
        auto results = query(database)
            .hasComponent<test::BoolComponent>()
            .hasComponent<test::NumberComponent>()
            .hasComponent<test::TextComponent>()
            .ids();

        ASSERT_EQ(1u,       results.size());
        EXPECT_EQ(ids[0],   results[0]);
    }
}

TEST(Query, FindComponentOfFirstMatchingEntity)
{
    Database database;

    auto& table1 = database.createTable<test::BoolComponent>();
    auto& table2 = database.createTable<test::NumberComponent>();
    database.createTable<test::TextComponent>();

    std::vector<EntityId> ids;
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());
    ids.emplace_back(database.createEntity());

    table1.assign(ids[0], test::BoolComponent{true});
    table2.assign(ids[1], test::NumberComponent{10});
    table1.assign(ids[1], test::BoolComponent{false});
    table1.assign(ids[2], test::BoolComponent{false});
    table2.assign(ids[2], test::NumberComponent{0});

    auto result1 = query(database).find<test::BoolComponent>();
    auto result2 = query(database).find<test::NumberComponent>();
    auto result3 = query(database).find<test::TextComponent>();

    ASSERT_TRUE(result1 != nullptr);
    EXPECT_EQ(true, result1->value);
    ASSERT_TRUE(result2 != nullptr);
    EXPECT_EQ(10, result2->value);
    ASSERT_TRUE(result3 == nullptr);
}

TEST(Query, PerformanceTest)
{
    Database database;

    auto& table1 = database.createTable<test::BoolComponent>();
    auto& table2 = database.createTable<test::NumberComponent>();
    auto& table3 = database.createTable<test::TextComponent>();

    size_t count = 2000u;

    std::vector<EntityId> ids;
    for (size_t i = 0; i < count; ++i)
    { 
        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), test::BoolComponent{true});
        
        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), test::BoolComponent{false});
        table2.assign(ids.back(), test::NumberComponent{10});

        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), test::BoolComponent{true});
        table3.assign(ids.back(), test::TextComponent{"text"});

        ids.emplace_back(database.createEntity());
        table2.assign(ids.back(), test::NumberComponent{100});
        table3.assign(ids.back(), test::TextComponent{"text"});

        ids.emplace_back(database.createEntity());
        table1.assign(ids.back(), test::BoolComponent{false});
        table2.assign(ids.back(), test::NumberComponent{1000});
        table3.assign(ids.back(), test::TextComponent{"text"});
    }
    
    size_t found = 0u;
    Timer timer = Timer::start();

    query(database)
        .hasComponent<test::BoolComponent>()
        .hasComponent<test::NumberComponent>()
        .hasComponent<test::TextComponent>()
        .execute([&](
            EntityId,
            const test::BoolComponent&,
            const test::NumberComponent&,
            const test::TextComponent&) 
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