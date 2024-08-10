#pragma once

//#include <core/ecs/Table.hpp>

#include <core/graph/Task.hpp>
#include <core/graph/Graph.hpp>

#include <vector>

#include <typeindex>
#include <mutex>
#include <utility>
#include <array>

namespace ecs
{
    struct Schedule
    {};

    class Scheduler
    {
    public:
        Task& registerTask(/* lambda? */);

        template <typename ...Args>
        Task& registerTask(Task&& func)
        {
            return *m_functions.emplace_back(std::make_unique<Task>()).get();
        }

        Schedule sort();

        void execute(const Schedule& schedule);

    private:
        std::vector<std::unique_ptr<Task>> m_functions;
    };
}