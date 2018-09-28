#pragma once

#include <component/Database.hpp>
#include <core/Defines.hpp>

namespace eng
{
	class System : public trait::non_copyable_nor_movable
	{
	public:
		template <typename Component>
		void addComponent(EntityId id, Component&& component);

		// Logic update once per frame.
		virtual void update() = 0;

	protected:
		System(Database& db) : m_database(db) {}
		virtual ~System() {}

		// - owns components and operates on them
		// - doesn't care about entities, but components (?)
		// - sync points for adding/removing components?

		template <typename Component>
		TableRef<Component> createTable(Database& db);

		template <typename Component>
		TableRef<Component> table();

	private:
		Database& m_database;
	};

	template<typename Component>
	inline void System::addComponent(EntityId id, Component&& component)
	{
		m_database.addComponent<Component>(id, std::forward<Component>(component));
	}

	template<typename Component>
	inline TableRef<Component> System::createTable(Database& db)
	{
		return db.createTable<Component>();
	}

	template<typename Component>
	inline TableRef<Component> System::table()
	{
		return m_database.table<Component>();
	}
}
