#pragma once

#include <core/Defines.hpp>

namespace eng
{
    class ITable 
    {
    public:
        virtual ~ITable() {}
    };

    template <typename Component>
    class Table : public ITable, public trait::non_copyable
    {
    public:
        Table() = default;
        virtual ~Table() override {}
        Table(Table&&) = default;
        Table& operator=(Table&&) = default;

        void resize(size_t size);
        void assign(EntityId id, Component&& component);
        void remove(EntityId id);

        const Component* operator[](EntityId id) const;
        const std::vector<EntityId>& ids() const { return m_entities; }

        void forEach(std::function<void(EntityId)> func);
        void forEach(std::function<void(EntityId)> func) const;
        void forEach(std::function<void(EntityId, Component&)> func);
        void forEach(std::function<void(EntityId, Component&)> func) const;

    private:
        // todo: assert read/write
        // todo: use sparse index for entity ids
        std::unordered_map<EntityId, size_t> m_entityToIndex;
        std::vector<EntityId>  m_entities;
        std::vector<Component> m_components;
    };

    template <typename Component>
    inline void Table<Component>::resize(size_t size)
    {
        m_entities.resize(size);
        m_components.resize(size);
    }

    template <typename Component>
    inline void Table<Component>::assign(EntityId id, Component&& component)
    {
        auto it = m_entityToIndex.find(id);
        if (it != m_entityToIndex.end())
        {
            m_components[it->second] = std::forward<Component>(component);
        }
        else
        {
            auto index = m_entities.size();

            m_entities.emplace_back(id);
            m_components.emplace_back(std::forward<Component>(component));
            
            m_entityToIndex[id] = index;
        }
    }

    template <typename Component>
    inline void Table<Component>::remove(EntityId id)
    {
        auto it = m_entityToIndex.find(id);
        if (it != m_entityToIndex.end())
        {
            // todo: use memory slot for next entity?
            // m_components[it->second] = Component(); 

            m_entityToIndex.erase(id);
        }
    }

    template <typename Component>
    inline const Component* Table<Component>::operator[](EntityId id) const
    {
        auto it = m_entityToIndex.find(id);
        if (it != m_entityToIndex.end())
        {
            return &m_components[it->second];
        }
        else
        {
            return nullptr;
        }
    }

    template <typename Component>
    inline void Table<Component>::forEach(std::function<void(EntityId)> func)
    {
        for (auto& id : m_entities)
        {
            func(id);
        }
    }

    template <typename Component>
    inline void Table<Component>::forEach(std::function<void(EntityId)> func) const
    {
        forEach(func);
    }

    template <typename Component>
    inline void Table<Component>::forEach(std::function<void(EntityId, Component&)> func)
    {
        for (size_t i = 0; i < m_entities.size(); ++i)
        {
            func(m_entities[i], m_components[i]);
        }
    }

    template <typename Component>
    inline void Table<Component>::forEach(std::function<void(EntityId, Component&)> func) const
    {
        forEach(func);
    }

    // todo: enforce that only one reference to a single table can exist at any given time,
    //       use RAII reference counting
    // todo: rename to TableOwner, ...
    template <typename Component>
    using TableRef = Table<Component>&;

    template <typename Component>
    using ConstTableRef = const Table<Component>&;
}
