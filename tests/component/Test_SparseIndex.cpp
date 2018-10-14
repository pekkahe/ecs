#include <Precompiled.hpp>

#include <component/SparseIndex.hpp>
#include <core/Time.hpp>
#include <array>

using namespace eng;

TEST(SparseIndex, Insertion)
{
}

TEST(SparseIndex, Checking)
{
    SparseIndex index;
    static constexpr size_t firstId = 1u;
    static constexpr size_t lastId = 10001u;
    std::array<bool, (lastId - firstId) + 10u> checks;

    Timer timer = Timer::start();

    for (size_t i = firstId; i <= lastId; ++i)
    {
        index.insert(i);
    }

    double elapsedInsert = timer.reset();

    for (size_t i = 0u; i < checks.size(); ++i)
    {
        checks[i] = index.check(i);
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
        "Elapsed:  " << (lastId - firstId) << " ids" << std::endl <<
        "Size:     " << sizeof(SparseIndex) << std::endl <<
        "(insert): " << elapsedInsert << " seconds" <<  std::endl <<
        "(check):  " << elapsedCheck << " seconds" << std::endl;
}

TEST(SparseIndex, Iteration)
{
}

TEST(SparseIndex, Removal)
{
}

TEST(SparseIndex, BitwiseBool)
{
}

TEST(SparseIndex, BitwiseAnd)
{
}

TEST(SparseIndex, BitwiseXor)
{
}

TEST(SparseIndex, StressTest)
{
}
