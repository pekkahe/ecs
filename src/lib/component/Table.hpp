#pragma once

#include <component/SparseIndex.hpp>
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

        void assign(EntityId id, Component&& component);
        void remove(EntityId id) override;
        void clear() override;
        bool empty() const override;
        size_t size() const;

        const std::vector<EntityId>& ids() const;
        SparseIndex index() const;

        Component* operator[](EntityId id);
        const Component* operator[](EntityId id) const;

        void forEach(std::function<void(EntityId)> func);
        void forEach(std::function<void(EntityId)> func) const;
        void forEach(std::function<void(EntityId, Component&)> func);
        void forEach(std::function<void(EntityId, Component&)> func) const;

    private:
        // todo: assert no concurrent read & writes
        SparseIndex m_index;
        
        std::vector<EntityId> m_ids;
        std::vector<Component> m_components;

        std::unordered_map<EntityId, size_t> m_indexMap;
        std::deque<size_t> m_freeIndices;

        // Entity offset to its index to component vector.
        //std::vector<size_t> m_offsets;
    };

    template <typename Component>
    inline void Table<Component>::assign(EntityId id, Component&& component)
    {
        size_t index = 0;

        if (!m_freeIndices.empty())
        {
            index = m_freeIndices.front();
            m_freeIndices.pop_front();

            m_ids[index] = id;
            m_components[index] = std::forward<Component>(component);
        }
        else
        {
            m_ids.emplace_back(id);
            m_components.emplace_back(std::forward<Component>(component));

            index = m_ids.size() - 1;
        }
        
        m_indexMap[id] = index;
        m_index.insert(id);
    }

    template <typename Component>
    inline void Table<Component>::remove(EntityId id)
    {
        m_index.erase(id);

        auto it = m_indexMap.find(id);
        if (it != m_indexMap.end())
        {
            size_t index = it->second;
            m_indexMap.erase(id);

            m_ids[index] = {};
            m_components[index] = {};
            m_freeIndices.emplace_back(index);
        }
    }

    template <typename Component>
    inline void Table<Component>::clear()
    {
        m_indexMap.clear();
        m_ids.clear();
        m_components.clear();
    }

    template <typename Component>
    inline bool Table<Component>::empty() const
    {
        return size() == 0u;
    }

    template <typename Component>
    inline size_t Table<Component>::size() const
    {
        return m_indexMap.size();
    }
    
    template<typename Component>
    inline const std::vector<EntityId>& Table<Component>::ids() const
    {
        return m_ids;
    }

    template<typename Component>
    inline SparseIndex Table<Component>::index() const
    {
        return m_index;
    }

    template<typename Component>
    inline Component* Table<Component>::operator[](EntityId id)
    {
        auto it = m_indexMap.find(id);
        if (it != m_indexMap.end())
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
        auto it = m_indexMap.find(id);
        if (it != m_indexMap.end())
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
        for (size_t i = 0; i < m_ids.size(); ++i)
        {
            func(m_ids[i]);
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
        for (size_t i = 0; i < m_ids.size(); ++i)
        {
            func(m_ids[i], m_components[i]);
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
