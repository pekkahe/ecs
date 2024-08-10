#pragma once

#include <cassert>
#include <typeindex>
#include <unordered_map>
#include <functional>
#include <tuple>

// query()
//     .hasComponent<Updated>()
//     .hasComponent<Transform>()
//     .hasComponent<Camera>(m_cameraTable)
//     .execute([&](
//         EntityId,
//         const Updated&,
//         const Transform& transform,
//         Camera& camera)

namespace ecs
{
    class Task
    {
    public:
        class Context
        {
        public:
            // template <typename Resource>
            // Resource& read(EntityId ent);

            // template <typename Resource>
            // Resource& write(EntityId ent);
        };

        Task(const char* name, std::function<void(const Task::Context&)> work);

        const char* name() const;

        template <typename Resource>
        Task& read()
        {
            std::type_index resourceId(typeid(Resource));
            assert(!m_readWriteResources.count(resourceId) && "Resource already declared as 'readWrite'");
            m_readResources[resourceId] = true;
            return *this;
        }

        // template <typename Resource>
        // Task& readWrite(TableRef<Resource> resource);

        template <typename Resource>
        Task& readWrite(Resource)
        {
            std::type_index resourceId(typeid(Resource));
            assert(!m_readResources.count(resourceId) && "Resource already declared as 'read'");
            m_readWriteResources[resourceId] = true;
            return *this;
        }

        Task& require(Task&);

    private:
        void execute();

    private:
        const char* m_name;
        std::function<void()> m_work;
        
        std::unordered_map<std::type_index, bool> m_readResources;
        std::unordered_map<std::type_index, bool> m_readWriteResources;
    };
}