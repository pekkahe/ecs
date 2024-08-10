// #include <Common.hpp>
#include <core/graph/FunctionSignature.hpp>
#include <core/graph/Scheduler.hpp>

#include <chrono>
#include <condition_variable>
#include <mutex>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ecs;

TEST(Graph, FunctionSignature)
{
    struct SomeType {};

    FunctionSignature<int, float, const SomeType> signature;

    ASSERT_FALSE(signature.parameter(0)->isConst); 
    ASSERT_FALSE(signature.parameter(1)->isConst); 
    ASSERT_TRUE(signature.parameter(2)->isConst); 

    ASSERT_EQ(typeid(int), signature.parameter(0)->typeIndex);
    ASSERT_EQ(typeid(float), signature.parameter(1)->typeIndex);
    ASSERT_EQ(typeid(SomeType), signature.parameter(2)->typeIndex);
}

TEST(Graph, Scheduler)
{
    Scheduler scheduler;
    // auto& function = scheduler.registerTask("test", [&](const View& view) {});
    
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    
    std::condition_variable cv;
    cv.wait_for(lock, std::chrono::seconds(1));

    auto schedule = scheduler.sort();
    // ASSERT_TRUE(job->completed);
}
