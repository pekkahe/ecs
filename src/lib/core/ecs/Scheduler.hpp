#pragma once

#include <core/ecs/Table.hpp>

#include <typeindex>
#include <mutex>
#include <utility>
#include <array>

// namespace ecs
// {
//     struct Schedule;

//     class Scheduler
//     {
//     public:
//         class Job
//         {
//             friend class Scheduler;

//         public:
//             template <typename Resource>
//             Job& read();

//             template <typename Resource>
//             Job& readWrite(TableRef<Resource> resource);

//             template <typename Resource>
//             Job& readWrite(Resource);

//             Job& require(Job&);

//             template <typename Function>
//             void onExecute(Function);

//             const char* name() const;

//         private:
//             void execute();

//         private:
//             std::unordered_map<std::type_index, bool> m_readResources;
//             std::unordered_map<std::type_index, bool> m_readWriteResources;
//         };

//     public:
//         Job& addJob()
//         {
//             m_jobs.emplace_back(std::make_unique<Job>());
//             return *m_jobs.back().get();
//         }

//         Schedule sort();

//         // written first
//         // read last
//         // topological sort
//         // error if any vertex unreachable
//         // how to parallelize?
//         // - iterate over vertices
//         // - 

//         void execute(const Schedule& schedule)
//         {
//             auto todo = graph.roots();
            
//             for (auto& job : todo)
//             {
//                 worker = workers.pop();
//                 worker.start(job);

//                 if (job.completed())
//                 {
//                     next = graph.outgoing(job);
//                 }
//             }

//             for (auto& job : pending)
//             {

//             }

//             ///

//             for (auto ptr = schedule.begin(); ptr < schedule.end(); )
//             {
//                 auto& group = *ptr;
//                 Schedule::JobGroup pending;

//                 for (auto& job : group)
//                 {
//                     if (job.pending())
//                     {
//                         pending.emplace_back(job);
//                     }

//                     if (!workers.empty())
//                     {
//                         worker = workers.pop();
//                         worker.assign(job);
//                         continue;
//                     }

//                     if (workSelf)
//                     {
//                         job->execute();
//                     }

//                     if (job.completed())
//                     {
//                         worker = job->worker().free();
//                         workers.emplace_back(worker);
//                     }
//                 }

//                 if (!pending.empty())
//                 {
//                     ptr++;
//                 }
//             }
//         }

//     private:
//         std::vector<std::unique_ptr<Job>> m_jobs;
//     };

//     template <typename Resource>
//     inline Scheduler::Job& Scheduler::Job::read()
//     {
//         std::type_index typeId(typeid(Resource));
//         assert(!m_readWriteResources.count(typeId) && "Resource already declared as 'readWrite'");
//         m_readResources[typeId] = true;
//         return *this;
//     }

//     template <typename Resource>
//     inline Scheduler::Job& Scheduler::Job::readWrite(TableRef<Resource> resource)
//     {
//         std::type_index typeId(typeid(Resource));
//         assert(!m_readResources.count(typeId) && "Resource already declared as 'read'");
//         m_readWriteResources[typeId] = true;
//         return *this;
//     }

//     class JobGraph
//     {
//     public:
//         using Job = Scheduler::Job;
//         using JobPtr = Job*;
//         using Vertex = JobPtr;

//         JobGraph(const std::vector<JobPtr>& jobs)
//         {
//         }

//         void addEdge(Vertex a, Vertex b);

//         std::vector<Vertex> incoming(Vertex v);
//         std::vector<Vertex> outgoing(Vertex v);
//         std::vector<Vertex> roots(); // Those with incoming.empty()

//     private:
//         size_t indexOf(Vertex v);
//         bool hasEdge(Vertex a, Vertex b); // ?

//         std::unordered_map<const char*, size_t> indexMap;
//         std::vector<std::vector<Vertex>> adjacencyList;
//     };
// }