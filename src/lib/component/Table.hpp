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
        // TODO: Assert no concurrent read & writes

        SparseIndex m_index;
        std::vector<EntityId> m_ids; // TODO: Replace with m_index and operator[]?
        std::vector<Component> m_components;
        std::unordered_map<EntityId, size_t> m_idToComponentIndex;
        std::deque<size_t> m_freeIndices;

        // TODO: Offset based entity component indexing?
        //std::vector<size_t> m_offsets;
    };

    template <typename Component>
    inline void Table<Component>::assign(EntityId id, Component&& component)
    {
        size_t insertAt = 0u;
        if (m_freeIndices.empty())
        {
            insertAt = m_components.size();
        }
        else
        {
            insertAt = m_freeIndices.front();
            m_freeIndices.pop_front();
        }

        if (insertAt < m_components.size())
        {
            m_ids[insertAt] = id;
            m_components[insertAt] = std::forward<Component>(component);
            m_idToComponentIndex[id] = insertAt;
        }
        else
        {
            m_ids.emplace_back(id);
            m_components.emplace_back(std::forward<Component>(component));
            m_idToComponentIndex[id] = m_components.size() - 1;
        }
        
        m_index.insert(id);
    }

    template <typename Component>
    inline void Table<Component>::remove(EntityId id)
    {
        auto it = m_idToComponentIndex.find(id);
        if (it != m_idToComponentIndex.end())
        {
            size_t index = it->second;

            m_index.erase(id);
            m_ids[index] = {};
            m_components[index] = {};
            m_idToComponentIndex.erase(id);

            m_freeIndices.emplace_back(index);
        }
    }

    template <typename Component>
    inline void Table<Component>::clear()
    {
        m_index.clear();
        m_ids.clear();
        m_components.clear();
        m_idToComponentIndex.clear();
    }

    template <typename Component>
    inline bool Table<Component>::empty() const
    {
        return size() == 0u;
    }

    template <typename Component>
    inline size_t Table<Component>::size() const
    {
        return m_index.size();
    }
    
    template<typename Component>
    inline const std::vector<EntityId>& Table<Component>::ids() const
    {
        std::vector<EntityId> ids;

        auto it = m_index.begin();
        while (it != m_index.end())
        {
            ids.emplace_back(*it);
            ++it;
        }

        return ids;
    }

    template<typename Component>
    inline SparseIndex Table<Component>::index() const
    {
        return m_index;
    }

    template<typename Component>
    inline Component* Table<Component>::operator[](EntityId id)
    {
        auto it = m_idToComponentIndex.find(id);
        if (it != m_idToComponentIndex.end())
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
        auto it = m_idToComponentIndex.find(id);
        if (it != m_idToComponentIndex.end())
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
        // TODO: This should be a faster iteration than using the indexing operator's 
        // hash map search, yet the query API uses that. This is also the only reason
        // why we still duplicate ids to 'm_ids'. Should we pick one and go with it,
        // or study new other (e.g. index offset calculation based) solutions?

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

    // TODO: Enforce that only one reference to a table can be held at any given time?
    // Invert Table ownership between Database and Systems? Use RAII reference counting?

    template <typename Component>
    using TableRef = Table<Component>&;

    template <typename Component>
    using ConstTableRef = const Table<Component>&;
}
