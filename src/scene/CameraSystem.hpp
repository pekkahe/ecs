#pragma once

#include <component/System.hpp>

#include <scene/Camera.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class CameraSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Camera, m_cameraTable);

    public:
        CameraSystem(Database& db);
        ~CameraSystem();

        void update(const Scene& scene) override;

        void setAspectRatio(float aspectRatio);

    private:
        TableRef<Camera> m_cameraTable;
    };
}