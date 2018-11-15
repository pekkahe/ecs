#pragma once

#include <component/System.hpp>
#include <core/Defines.hpp>
#include <scene/Hovered.hpp>
#include <scene/Selected.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class SelectionSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Hovered, m_hoveredTable);
        ADD_COMPONENT_FUNCTION(Selected, m_selectedTable);

    public:
        SelectionSystem(Database& db);

        void update(const Scene& scene) override;

    private:
        TableRef<Hovered> m_hoveredTable;
        TableRef<Selected> m_selectedTable;
    };
}