// #include <Common.hpp>

#include <core/scheduler/Scheduler.hpp>

#include <chrono>
#include <condition_variable>
#include <mutex>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace wip;

// TODO: Move to scope
std::condition_variable test_cv;

class TestJob : public Job 
{
public:
    void run() override;

    bool completed = false;
};

void TestJob::run()
{
    completed = true;
    test_cv.notify_all();
}

TEST(Scheduler, Legacy)
{
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);

    Scheduler::init(1);

    auto job = std::make_shared<TestJob>();

    Scheduler::addJob(job);
    
    test_cv.wait_for(lock, std::chrono::seconds(1));

    Scheduler::stop();

    ASSERT_TRUE(job->completed);
}

//TEST(Scheduler, Test)
//{
//    std::unique_lock<std::mutex> ulock(mutex);
//
//    Scheduler::init(3);
//
//    auto job = std::make_shared<TestJob>();
//
//    Scheduler::addJob(job);
//
//    cv.wait_for(ulock, std::chrono::seconds(1));
//
//    Scheduler::stop();
//
//    ASSERT_EQ(true, job->processed);
//    ASSERT_EQ(true, job->finished);
//}
