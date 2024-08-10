// #include <Common.hpp>

#include <core/Time.hpp>
#include <core/ecs/SparseIndex.hpp>

#include <array>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ecs;
using namespace testing;

TEST(SparseIndex, Insertion)
{
    SparseIndex index;
    EXPECT_TRUE(index.empty());
    EXPECT_EQ(0u, index.size());

    index.insert(100);
    index.insert(100);
    index.insert(100);
    index.insert(200);

    EXPECT_FALSE(index.empty());
    EXPECT_EQ(2u, index.size());
    EXPECT_TRUE(index.check(100));
    EXPECT_TRUE(index.check(200));
}

TEST(SparseIndex, Iteration)
{
    SparseIndex index;
    index.insert(1);
    index.insert(3000);
    index.insert(12000);
    index.insert(5);

    std::vector<EntityId> ids;

    auto it = index.begin();
    while (it != index.end())
    { 
        ids.emplace_back(*it);
        ++it;
    }

    EXPECT_EQ(4u, ids.size());
    EXPECT_THAT(ids, UnorderedElementsAre(1, 3000, 12000, 5));
}

TEST(SparseIndex, IterationOverEmptyIndex)
{
    SparseIndex index;
    std::vector<EntityId> ids;

    auto it = index.begin();
    while (it != index.end())
    {
        ids.emplace_back(*it);
        ++it;
    }

    EXPECT_TRUE(ids.empty());
}

TEST(SparseIndex, Removal)
{
    SparseIndex index;
    index.insert(1);
    index.insert(100);
    index.insert(1000);
    EXPECT_EQ(3u, index.size());

    index.erase(100);
    index.erase(100);
    index.erase(100);
    EXPECT_EQ(2u, index.size());

    index.erase(1);
    EXPECT_EQ(1u, index.size());

    index.erase(1000);
    EXPECT_EQ(0u, index.size());
}

TEST(SparseIndex, BitwiseBool)
{
    SparseIndex in1;
    in1.insert(1);
    in1.insert(20);
    in1.insert(200);

    SparseIndex in2;
    in2.insert(1);
    in2.insert(20);
    in2.insert(30);
    in2.insert(300);

    SparseIndex out1;
    out1.insert(100);
    out1 |= in1;

    SparseIndex out2 = in1 | in2;

    EXPECT_EQ(4u, out1.size());
    EXPECT_TRUE(out1.check(1));
    EXPECT_TRUE(out1.check(20));
    EXPECT_TRUE(out1.check(200));
    EXPECT_TRUE(out1.check(100));
    
    EXPECT_EQ(5u, out2.size());
    EXPECT_TRUE(out2.check(1));
    EXPECT_TRUE(out2.check(20));
    EXPECT_TRUE(out2.check(200));
    EXPECT_TRUE(out2.check(30));
    EXPECT_TRUE(out2.check(300));
}

TEST(SparseIndex, BitwiseAnd)
{
    SparseIndex in1;
    in1.insert(1);
    in1.insert(20);
    in1.insert(200);

    SparseIndex in2;
    in2.insert(1);
    in2.insert(20);
    in2.insert(30);
    in2.insert(300);

    SparseIndex out1;
    out1.insert(1);
    out1.insert(100);
    out1 &= in1;

    SparseIndex out2 = in1 & in2;

    EXPECT_EQ(1u, out1.size());
    EXPECT_TRUE(out1.check(1));

    EXPECT_EQ(2u, out2.size());
    EXPECT_TRUE(out2.check(1));
    EXPECT_TRUE(out2.check(20));
}

TEST(SparseIndex, BitwiseXor)
{
    SparseIndex in1;
    in1.insert(1);
    in1.insert(20);
    in1.insert(200);

    SparseIndex in2;
    in2.insert(1);
    in2.insert(20);
    in2.insert(30);
    in2.insert(300);

    SparseIndex out1;
    out1.insert(1);
    out1.insert(100);
    out1 ^= in1;

    SparseIndex out2 = in1 ^ in2;

    EXPECT_EQ(3u, out1.size());
    EXPECT_TRUE(out1.check(100));
    EXPECT_TRUE(out1.check(20));
    EXPECT_TRUE(out1.check(200));

    EXPECT_EQ(3u, out2.size());
    EXPECT_TRUE(out2.check(30));
    EXPECT_TRUE(out2.check(200));
    EXPECT_TRUE(out2.check(300));
}

TEST(SparseIndex, PerformanceTest)
{
    SparseIndex index;
    static constexpr size_t firstId = 1u;
    static constexpr size_t lastId = 10001u;
    std::array<bool, (lastId - firstId) + 10u> checks;

    Timer timer = Timer::start();

    for (size_t i = firstId; i <= lastId; ++i)
    {
        index.insert(static_cast<EntityId>(i));
    }

    double elapsedInsert = timer.reset();

    for (size_t i = 0u; i < checks.size(); ++i)
    {
        checks[i] = index.check(static_cast<EntityId>(i));
    }

    double elapsedCheck = timer.reset();

    for (size_t i = 0u; i < checks.size(); ++i)
    {
        if (i < firstId || i > lastId)
        {
            EXPECT_FALSE(checks[i]);
        }
        else
        {
            EXPECT_TRUE(checks[i]);
        }
    }

    std::cout <<
        "Entities:         " << (lastId - firstId) << std::endl <<
        "Index byte size:  " << sizeof(SparseIndex) << std::endl <<
        "Elapsed (insert): " << elapsedInsert << " ms" << std::endl <<
        "Elapsed (check):  " << elapsedCheck << " ms" << std::endl;
}
