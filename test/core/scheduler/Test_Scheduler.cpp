#include <Common.hpp>

#include <core/scheduler/Scheduler.hpp>

#include <chrono>
#include <condition_variable>
#include <mutex>

using namespace wip;

std::condition_variable cv;
std::mutex mutex;

class TestJob : public Job 
{
public:
    void process() override;
    void finish() override;

    bool processed = false;
    bool finished = false;
};

void TestJob::process()
{
    processed = true;
}

void TestJob::finish()
{
    finished = true;

    cv.notify_all();
}

TEST(Scheduler, Test)
{
    std::unique_lock<std::mutex> lock(mutex);

    Scheduler::init(1);

    auto job = std::make_shared<TestJob>();

    Scheduler::addJob(job);
    
    cv.wait_for(lock, std::chrono::seconds(1));

    Scheduler::stop();

    ASSERT_EQ(true, job->processed);
    ASSERT_EQ(true, job->finished);
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
