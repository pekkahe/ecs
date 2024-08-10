#include <core/graph/Scheduler.hpp>

#include <core/Core.hpp>

#include <thread>

using namespace ecs;

Schedule Scheduler::sort()
{
    return {};
}

#if 0
void Scheduler::execute(const Schedule& schedule)
{
    // written first
    // read last
    // topological sort
    // error if any vertex unreachable
    // how to parallelize?
    // - iterate over vertices
    // - 

    auto todo = graph.roots();

    for (auto& job : todo)
    {
        worker = workers.pop();
        worker.start(job);

        if (job.completed())
        {
            next = graph.outgoing(job);
        }
    }

    for (auto& job : pending)
    {

    }

    ///

    for (auto ptr = schedule.begin(); ptr < schedule.end(); )
    {
        auto& group = *ptr;
        Schedule::JobGroup pending;

        for (auto& job : group)
        {
            if (job.pending())
            {
                pending.emplace_back(job);
            }

            if (!workers.empty())
            {
                worker = workers.pop();
                worker.assign(job);
                continue;
            }

            if (workSelf)
            {
                job->execute();
            }

            if (job.completed())
            {
                worker = job->worker().free();
                workers.emplace_back(worker);
            }
        }

        if (!pending.empty())
        {
            ptr++;
        }
    }
}
#endif