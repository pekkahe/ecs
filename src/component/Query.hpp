#pragma once

#include <component/Database.hpp>
#include <component/Table.hpp>

namespace eng
{
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
				"Query argument is not a Component");

			return hasComponentImpl<Component>(std::index_sequence_for<Tables...>());
		}

		template <typename F>
		void execute(F&& process)
		{
			std::unordered_multiset<EntityId> ids;

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

		//template <size_t... Is>
		//void insertTableIds(std::unordered_multiset<EntityId>& ids, std::index_sequence<Is...>)
		//{
		//	std::vector<ITable&> tables = { std::get<Is>(m_tables)... };

		//	auto indexes = get_indexes(tup);

		//	for_each(indexes, std::forward<Tuple>(tup), std::forward<F>(f));

		//	// auto t = { (std::get<Is>(m_tables).ids(), 0)... };

		//	for (auto table : std::get<Is>(m_tables)...)
		//	{
		//		for (auto& id : table.ids())
		//		{
		//			ids.insert(id);
		//		}
		//	}
		//}

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

		//template <size_t... Is, typename Tuple, typename F>
		//auto process_each(std::index_sequence<Is...>, Tuple&& tuple, F&& f)
		//{
		//	do_in_order([&] { f(std::get<Is>(std::forward<Tuple>(tuple))); }...);
		//}

		//template <typename Tuple, typename F>
		//void for_each(Tuple&& tuple, F&& f) 
		//{
		//	auto indexes = get_indexes(tuple);
		//	for_each(indexes, std::forward<Tuple>(tuple), std::forward<F>(f));
		//}

		//template <typename T>
		//typename decltype(auto) getComponent(EntityId id, const T& table)
		//{
		//	return *table[id];
		//}

		//template <typename F, typename... Components>
		//void processPip(EntityId id, F&& f, Components... comps)
		//{
		//	f(id, comps...);
		//}

		//template <typename Component>
		//void insertIds(std::unordered_multiset<EntityId>& ids, TableRef<Component> table)
		//{
		//	for (auto& id : table.ids())
		//	{
		//		ids.insert(id);
		//	}
		//}

		//template <typename... Args, typename Func>
		//void for_each(const std::tuple<Args...>& t, Func&& f) 
		//{
		//	for_each(t, f, std::index_sequence_for<Args...>{});
		//}

		//template <class Tuple, size_t... Is>
		//void function(Tuple tuple, index_sequence<Is...>)
		//{
		//	some_func(std::get<Is>(tuple)...);
		//}

	private:
		const Database& m_database;
		std::tuple<Tables...> m_tables;
		//std::tuple<Table<Components>...> m_components;
	};

	//class Query
	//{
	//public:
	//	template <typename Component, typename... Tables>
	//	static Query<Tables...> hasComponent()
	//	{
	//		Database db;
	//		return Query<Tables...>(db, db.table<Component>());
	//	}
	//};

	//template <typename... Tables>
	//class LineQuery
	//{
	//public:
	//	LineQuery(const Database& database) : m_database(database) {}

	//	//template <typename... Tables>
	//	template <typename... Components>
	//	LineQuery& hasComponents()
	//	{
	//		m_tables = std::make_tuple(m_database.table<Components>()...);
	//		return *this;
	//	}

	//	template <typename... Components>
	//	void execute(std::function<void(EntityId, const Components&...)>&& process)
	//	{

	//	}

	//private:
	//	const Database& m_database;
	//	std::tuple<const Tables&...> m_tables;
	//};

	Query<> query(Database& database);

	//template <typename... Tables>
	//LineQuery<Tables...> lineQuery(Database& database)
	//{
	//	return LineQuery<Tables...>(database);
	//}

	template <typename Component>
	void addComponent(EntityId id, Component&& component);

	template <typename Component>
	void query(Table<Component>& table, std::function<void(EntityId)>&& process);

	template <typename F>
	void execute(F&& process)
	{ }
	
	//template <typename Component>
	//void query(Table<Component>& table, std::function<void(Component&)>&& process);

	//template <typename Component>
	//void query(Table<Component>& table, std::function<void(const Component&)>&& process);

	template <typename Component>
	void query(Table<Component>& table, std::function<void(EntityId, Component&)>&& process);

	template <typename Component>
	void query(const Table<Component>& table, std::function<void(EntityId, const Component&)>&& process);

	//template <typename... Components>
	//void query(const TableRef<Components>... tables, std::function<void(EntityId, const Components&...)>&& process)
	//{
	//}

	template <typename Component>
	void query(const Table<Component>& table, std::function<void(EntityId)>&& process);
	
	template <typename Component>
	void addComponent(EntityId id, Component && component)
	{
	}

	template <typename Component>
	void query(Table<Component>& table, std::function<void(EntityId)>&& process)
	{
		table.forEach(std::move(process));
	}

	template <typename Component>
	void query(Table<Component>& table, std::function<void(EntityId, Component&)>&& process)
	{
		table.forEach(std::move(process));
	}

	//template<typename Component>
	//inline Query<Component> Query::inTable(ConstTableRef<Component> table)
	//{
	//	return Query<Component>(table);
	//}

	//template <typename Component>
	//inline Query& Query::inTable(ConstTableRef<Component> table)
	//{
	//	table[9]

	//	table.ids();

	//	std::make_tuple()

	//	return *this;
	//}

	//template <typename... Components>
	//inline void Query::execute(std::function<void(EntityId, const Components&...)>&& process)
	//{
	//	for (int i = 0; i < sizeof...(Components); ++i)
	//	{ 

	//	}

	//	tuple = std::tuple<T_values...>(values...);

	//	std::make_tuple()

	//	for (auto& id : m_ids)
	//	{ 

	//		process(id, const Components&... components)
	//	}
	//	
	//	m_tables
	//}
	//template<typename... Tables>
	//template<typename Component>
	//inline Query Query<...Tables>::inTable(ConstTableRef<Component> table)
	//{
	//	return Query();
	//}

	//template<typename ...Tables>
	//template<typename ...Components>
	//inline void Query<...Tables>::execute(std::function<void(EntityId, const Components&...)>&& process)
	//{
	//}
}