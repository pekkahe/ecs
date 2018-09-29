#pragma once

#include <component/IComponent.hpp>
#include <component/Table.hpp>
#include <core/Defines.hpp>

namespace eng
{
    // todo: consider removing this and moving table ownership to systems
    // todo: then, createEntity() should be somewhere else
    // - there can be multiple 'databases' or 'stages' in world
    // - can entity ids conflict between 'stages'?
    //   - if not, we must separate entity creation from 'database'
    //   - if yes, it should be ok to keep entity creation in 'database'
    class Database : public trait::non_copyable
    {
    public:
        Database() = default;
        Database(Database&&) = default;
        Database& operator=(Database&&) = default;

        template <typename Component>
        TableRef<Component> createTable();

        template <typename Component>
        TableRef<Component> table();

        template <typename Component>
        const TableRef<Component> table() const;

        EntityId createEntity();

        template <typename Component>
        void addComponent(EntityId id, Component&& component);

    private:
        using TableId = size_t;
        template <typename Component>
        TableId tableId() const;

    private:
        std::unordered_map<TableId, std::unique_ptr<ITable>> m_tables;
        EntityId m_nextEntityId = 0u;
    };

    template <typename Component>
    inline TableRef<Component> Database::createTable()
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Cannot create Table for other type than a component");

        static TableId id = tableId<Component>();

        assert(!m_tables.count(id) && "Table already created");

        m_tables[id] = std::make_unique<Table<Component>>();

        return table<Component>();
    }

    template <typename Component>
    inline TableRef<Component> Database::table()
    {
        static TableId id = tableId<Component>();

        assert(m_tables.count(id) && "No such table");

        return static_cast<TableRef<Component>>(*m_tables.at(id));
    }

    template <typename Component>
    inline const TableRef<Component> Database::table() const
    {
        // todo: duplication

        static TableId id = tableId<Component>();

        assert(m_tables.count(id) && "No such table");

        return static_cast<const TableRef<Component>>(*m_tables.at(id));
    }

    template <typename Component>
    inline void Database::addComponent(EntityId id, Component&& component)
    {
        table<Component>().assign(id, std::forward<Component>(component));
    }

    template <typename Component>
    inline Database::TableId Database::tableId() const
    {
        return typeid(Component).hash_code();
    }
}
