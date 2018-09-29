#pragma once

#include <component/Database.hpp>
#include <component/Table.hpp>

namespace eng
{
    // Read-only query builder
    template <typename... Tables>
    class Query : public trait::non_copyable
    {
    public:
        Query(
            const Database& database, 
            Tables... tables) : 
            m_database(database),
            m_tables(tables...) {}
        Query(Query&&) = default;
        Query& operator=(Query&&) = default;

        template <typename Component>
        auto hasComponent()
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Query argument must be a component");

            return hasComponentImpl<Component>(std::index_sequence_for<Tables...>());
        }

        template <typename F>
        void execute(F&& process)
        {
            std::unordered_multiset<EntityId> ids;

            // todo: optimize

            // Collect ids
            forEach(std::index_sequence_for<Tables...>(), m_tables,
                [&](const auto& table) 
                {
                    for (auto& id : table.ids())
                    {
                        ids.insert(id);
                    }
                });

            // Filter ids
            auto it = ids.begin();
            while (it != ids.end())
            {
                auto id = *it;
                if (ids.count(id) != sizeof...(Tables))
                {
                    it = ids.erase(it);
                }
                else
                {
                    // Entity exists in all tables

                    processImpl(id, process, std::index_sequence_for<Tables...>());
                    it++;
                }
            }

            //static_assert(sizeof...(Tables) == sizeof...(Components), 
            //	"Mismatching number of Table and Component parameters.");
        }

    private:
        template <typename Component, size_t... Is>
        auto hasComponentImpl(std::index_sequence<Is...>)
        {
            return Query<Tables..., const TableRef<Component>>(
                m_database,
                std::get<Is>(m_tables)...,
                m_database.table<Component>());
        }

        template <size_t... Is, typename Tuple, typename F>
        void forEach(std::index_sequence<Is...>, Tuple&& tuple, F&& f) 
        {
            // Unpack 'tuple' and execute 'f' for each value
            doInOrder([&] { f(std::get<Is>(std::forward<Tuple>(tuple))); }...);
        }

        template <typename... F>
        void doInOrder(F&&... f)
        {
            // Use comma operator to call each function in parameter pack
            int unused[] = { 0, ((void) std::forward<F>(f)(), 0)... };
            (void) unused; // Prevent warning
        }

        template <typename F, size_t... Is>
        void processImpl(EntityId id, F&& f, std::index_sequence<Is...>)
        {
            const auto& getComponent = [](EntityId id, const auto& table)
            {
                return *table[id];
            };

            f(id, getComponent(id, std::get<Is>(m_tables))...);
        }

    private:
        const Database& m_database;
        std::tuple<Tables...> m_tables;
    };

    // Read-only query entry point
    Query<> query(const Database& database);

    template <typename Component>
    void query(
        Table<Component>& table, 
        std::function<void(EntityId)>&& process)
    {
        table.forEach(std::move(process));
    }

    template <typename Component>
    void query(
        Table<Component>& table, 
        std::function<void(EntityId, Component&)>&& process)
    {
        table.forEach(std::move(process));
    }

    template <typename Component>
    void query(
        const Table<Component>& table, 
        std::function<void(EntityId, const Component&)>&& process)
    {
        table.forEach(std::move(process));
    }

    template <typename Component>
    void query(
        const Table<Component>& table, 
        std::function<void(EntityId)>&& process)
    {
        table.forEach(std::move(process));
    }
    
    //template <typename Component>
    //void query(Table<Component>& table, std::function<void(EntityId)>&& process)
    //{
    //	table.forEach(std::move(process));
    //}

    //template <typename Component>
    //void query(Table<Component>& table, std::function<void(EntityId, Component&)>&& process)
    //{
    //	table.forEach(std::move(process));
    //}

    //template <typename Component>
    //void query(const Table<Component>& table, std::function<void(EntityId)>&& process)
    //{
    //	table.forEach(std::move(process));
    //}

    //template <typename Component>
    //void query(const Table<Component>& table, std::function<void(EntityId, const Component&)>&& process)
    //{
    //	table.forEach(std::move(process));
    //}
}