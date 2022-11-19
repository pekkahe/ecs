#pragma once

#include <core/ecs/System.hpp>
#include <scene/Camera.hpp>
#include <scene/CameraControl.hpp>
#include <scene/CameraController.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class CameraSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Camera, m_cameraTable);
        ADD_COMPONENT_FUNCTION(CameraControl, m_cameraControlTable);

    public:
        CameraSystem(Database& db, std::shared_ptr<Window> window);
        ~CameraSystem() override;

        void update(const Scene& scene) override;

        // QUERY:  'updateCameraController'
        // READS:  CameraControl
        // WRITES: (Updated)
                       
        // QUERY:  'updateCameraFov'
        // READS:  (Updated), Camera, CameraControl
        // WRITES: Camera

        // QUERY:  'updateCameraMatrices'
        // READS:  (Updated), Transform
        // WRITES: Camera
        
        void setAspectRatio(float aspectRatio);

    private:
        TableRef<Camera> m_cameraTable;
        TableRef<CameraControl> m_cameraControlTable;

        std::shared_ptr<CameraController> m_cameraController;
    };
}