#pragma once

#include <component/Database.hpp>
#include <component/Table.hpp>

namespace eng
{
    // todo: tests

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

        // Transform query filter to include a read-only component table.
        template <typename Component>
        auto hasComponent()
        {
            assertComponent<Component>();

            return newQuery(m_database.table<Component>(), std::index_sequence_for<Tables...>());
        }

        // Transform query filter to include a mutable component table.
        template <typename Component>
        auto hasComponent(TableRef<Component> table)
        {
            assertComponent<Component>();

            return newQuery(table, std::index_sequence_for<Tables...>());
        }

        // Execute query against all matching entities.
        template <typename F>
        void execute(F&& process)
        {
            for (auto&& id : ids())
            {
                processImpl(id, process, std::index_sequence_for<Tables...>());
            }
        }

        // Return component data of first entity which matches the query arguments,
        // or nullptr if no matches were found.
        template <typename Component>
        const Component* find()
        {
            assertComponent<Component>();

            auto ids = hasComponent<Component>().ids();
            if (!ids.empty())
            {
                return m_database.table<Component>()[ids[0]];
            }
            return nullptr;
        }

        // Return entity ids which match the query arguments.
        std::vector<EntityId> ids()
        {
            // Use multiset to conveniently check how many matches
            // per id we receive within our query tables
            std::unordered_multiset<EntityId> ids;

            // Insert all ids from query tables into multiset
            forEach(std::index_sequence_for<Tables...>(), m_tables,
                [&](const auto& table)
            {
                for (auto& id : table.ids())
                {
                    ids.insert(id);
                }
            });

            // Remove ids from multiset which we're not added exactly
            // the amount of times than there are query tables; this
            // would indicate that the id was not located in all tables
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
                    it++;
                }
            }

            return std::vector<EntityId>(ids.begin(), ids.end());
        }

    private:
        template <typename Component>
        constexpr void assertComponent()
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Query argument must be a component");
        }

        template <typename T, size_t... Is>
        auto newQuery(T&& table, std::index_sequence<Is...>)
        {
            return Query<Tables..., decltype(table)>(
                m_database,
                std::get<Is>(m_tables)...,
                table);
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
            decltype(auto) getComponent = [](EntityId id, auto& table)
            {
                return table[id];
            };

            f(id, *getComponent(id, std::get<Is>(m_tables))...);
        }

    private:
        const Database& m_database;

        std::tuple<Tables...> m_tables;
    };

    // Read-only query entry point
    Query<> query(const Database& database);
}