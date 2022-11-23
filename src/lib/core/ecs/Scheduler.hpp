#pragma once

#include <core/Core.hpp>
#include <core/ecs/Table.hpp>

namespace ecs
{
    class Scheduler
    {
    public:
        class Job
        {
            friend class Scheduler;

        public:
            template <typename Resource>
            Job& read();

            template <typename Resource>
            Job& readWrite(TableRef<Resource> resource);

            template <typename Resource>
            Job& readWrite(Resource)
            {
                return *this;
            }

            Job& require(Job&)
            {
                return *this;
            }

            template <typename Function>
            void onExecute(Function f)
            {
                //f()
            }

        private:
            void execute()
            {
            }

        private:
            // key: std::type_info::hash_code()
            std::unordered_map<size_t, bool> m_readResources;
            std::unordered_map<size_t, bool> m_readWriteResources;
        };

    public:
        Job& job()
        {
            m_jobs.emplace_back(std::make_unique<Job>());

            return *m_jobs.back().get();
        }

        void execute()
        {
            for (auto&& job : m_jobs)
            {
                job->execute();
            }

            m_jobs.clear();
        }

    private:
        std::vector<std::unique_ptr<Job>> m_jobs;
    };

    template <typename Resource>
    inline Scheduler::Job& Scheduler::Job::read()
    {
        assert(!m_readWriteResources.count(typeid(Resource)) &&
            "Resource already declared as 'readWrite'");

        m_readResources[typeid(Resource).hash_code()] = true;

        return *this;
    }

    template <typename Resource>
    inline Scheduler::Job& Scheduler::Job::readWrite(TableRef<Resource> resource)
    {
        assert(!m_readResources.count(typeid(Resource).hash_code()) &&
            "Resource already declared as 'read'");

        m_readWriteResources[typeid(Resource)] = true;

        return *this;
    }
}