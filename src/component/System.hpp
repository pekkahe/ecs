#pragma once

#include <component/Database.hpp>
#include <component/Query.hpp>
#include <core/Defines.hpp>

// Generate function definition for a component assignment function.
#define ADD_COMPONENT_FUNCTION(ComponentName, TableField) \
        void add ## ComponentName (EntityId id, ComponentName&& component) \
        { \
            TableField.assign(id, std::forward<ComponentName>(component)); \
        }

namespace eng
{
    class Scene;
    class ISystem : public trait::non_copyable
    {
    public:
        // Notification on the system's registration to a scene.
        virtual void onRegistered(const Scene& scene) = 0;

        // System logic update executed once per frame.
        virtual void update(const Scene& scene) = 0;

        // Push the system's Updated tags into the database.
        virtual void commitUpdated(Database& db) = 0;
        // Push the system's Deleted tags into the database.
        virtual void commitDeleted(Database& db) = 0;
    };

    class System : public ISystem
    {
    public:
        void onRegistered(const Scene& scene) override;

        void commitUpdated(Database& database) override;
        void commitDeleted(Database& database) override;

    protected:
        virtual ~System() {}

        template <typename Component>
        TableRef<Component> createTable(Database& db);
        
        // Build a query with pre-built read-only access to the scene database.
        Query<> query() const { return Query<>(*m_database); }

        // Mark an entity with the Updated tag, for one whole frame,
        // starting from the next frame.
        void markUpdated(EntityId id);
        // Mark an entity with the Deleted tag, for one whole frame,
        // starting from the next frame, after which the entity is
        // removed from the scene database.
        void markDeleted(EntityId id);

    private:
        const Database* m_database;

        // Each system has their own tag component tables, which are synchronized
        // with the scene database at the start of each frame. This ensures that 
        // all systems can react to tags regardless of their update order, and 
        // provides a thread-safety mechanism for concurrent system updated (TBD).

        Table<Updated> m_updatedTable;
        Table<Deleted> m_deletedTable;
    };

    template<typename Component>
    inline TableRef<Component> System::createTable(Database& db)
    {
        // todo: unnecessary at the moment, but can be an entry point for the system's
        // table registration, i.e. a way to get rid of the ADD_COMPONENT_FUNCTION macro,
        // maybe with some template metaprogramming..?

        return db.createTable<Component>();
    }
}
