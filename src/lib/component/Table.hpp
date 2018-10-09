#pragma once

#include <core/Defines.hpp>

namespace eng
{
    class ITable 
    {
    public:
        virtual ~ITable() {}

        virtual void remove(EntityId id) = 0;
        virtual void clear() = 0;
        virtual bool empty() const = 0;
    };

    template <typename Component>
    class Table : public ITable, public trait::non_copyable
    {
    public:
        Table() = default;
        ~Table() override = default;
        Table(Table&&) = default;
        Table& operator=(Table&&) = default;

        void resize(size_t size);
        void assign(EntityId id, Component&& component);
        void remove(EntityId id) override;
        void clear() override;
        bool empty() const override { return m_entities.empty(); }

        Component* operator[](EntityId id);
        const Component* operator[](EntityId id) const;

        const std::vector<EntityId>& ids() const { return m_entities; }

        void forEach(std::function<void(EntityId)> func);
        void forEach(std::function<void(EntityId)> func) const;
        void forEach(std::function<void(EntityId, Component&)> func);
        void forEach(std::function<void(EntityId, Component&)> func) const;

    private:
        // todo: assert no concurrent read & writes
        // todo: implement sparse index data structure
        std::unordered_map<EntityId, size_t> m_entityToIndex;
        std::vector<EntityId>  m_entities;
        std::vector<Component> m_components;
    };

    template <typename Component>
    inline void Table<Component>::resize(size_t size)
    {
        assert(true && "Not implemented");
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
            // todo: data is now left hanging in table,
            // fixed once we move to a better data structure

            m_entityToIndex.erase(id);
        }
    }

    template <typename Component>
    inline void Table<Component>::clear()
    {
        m_entities.clear();
        m_components.clear();
        m_entityToIndex.clear();
    }

    template<typename Component>
    inline Component* Table<Component>::operator[](EntityId id)
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

    // todo: enforce that only one reference to a table can be held at any given time?
    //       or invert Table ownership Database <-> System
    //       use RAII reference counting?

    template <typename Component>
    using TableRef = Table<Component>&;

    template <typename Component>
    using ConstTableRef = const Table<Component>&;
}
