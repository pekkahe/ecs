#include <Precompiled.hpp>
#include <scene/Scene.hpp>

#include <graphics/Mesh.hpp>
#include <scene/Transform.hpp>
#include <scene/TransformGizmo.hpp>

using namespace eng;

Scene::Scene(std::shared_ptr<Window> window) :
    m_window(std::move(window)),
    m_transformSystem(m_database, m_window),
    m_renderSystem(m_database),
    m_cameraSystem(m_database, m_window),
    m_selectionSystem(m_database, m_window)
{
    registerSystem(m_transformSystem);
    registerSystem(m_renderSystem);
    registerSystem(m_cameraSystem);
    registerSystem(m_selectionSystem);

    createCamera();
    createGizmo();
}

Scene::~Scene()
{
}

void Scene::registerSystem(ISystem& system)
{
    m_systems.emplace_back(&system);

    system.onRegistered(*this);
}

void Scene::update()
{
    // TODO: unit test Updated, Deleted

    for (auto system : m_systems)
    {
        system->commitUpdated(m_database);
        system->commitDeleted(m_database);
    }

    // TODO: multithreading, within system update or between updates?
    // causality scheduling (const, non-const) for individual queries?
    for (auto system : m_systems)
    {
        system->update(*this);
    }

    m_database.purgeDeleted();
    m_database.clearTags();
}

EntityId Scene::createEntity()
{
    return m_database.createEntity();
}

EntityId Scene::createCamera()
{
    auto id = createEntity();

    Transform transform;
    transform.rotation = glm::quatLookAt(
        vec3(0.0f, 0.0f, -1.0f), Camera::WorldUp);

    m_cameraSystem.addCamera(id, Camera());
    m_cameraSystem.addCameraControl(id, CameraControl());
    m_transformSystem.addTransform(id, std::move(transform));

    m_database.table<Added>().assign(id, Added());
    m_database.table<Updated>().assign(id, Updated());

    return id;
}

EntityId Scene::createCube(vec3 position)
{
    Mesh mesh;
    mesh.vertices = std::vector<vec3>
    {
        vec3(0.5f,   0.5f, -0.5f),
        vec3(0.5f,  -0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),

        vec3(0.5f,   0.5f,  0.5f),
        vec3(0.5f,  -0.5f,  0.5f),
        vec3(-0.5f, -0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f)
    };
    mesh.colors = std::vector<vec3>
    {
        vec3(0.9f, 0.9f, 0.9f),
        vec3(0.9f, 0.9f, 0.9f),
        vec3(0.9f, 0.9f, 0.9f),
        vec3(0.9f, 0.9f, 0.9f),

        vec3(0.6f, 0.6f, 0.6f),
        vec3(0.6f, 0.6f, 0.6f),
        vec3(0.6f, 0.6f, 0.6f),
        vec3(0.6f, 0.6f, 0.6f)
    };
    mesh.indices = std::vector<unsigned>
    {
        0, 1, 3, // front
        1, 2, 3,

        4, 5, 7, // back
        5, 6, 7,

        4, 0, 7, // top
        0, 3, 7,

        5, 1, 6, // bottom
        1, 2, 6,

        3, 2, 7, // left
        2, 6, 7,

        4, 5, 0, // right
        5, 1, 0
    };

    auto id = createEntity();

    Transform transform;
    transform.position = position;

    m_renderSystem.addMesh(id, std::move(mesh));
    m_transformSystem.addTransform(id, std::move(transform));

    m_database.table<Added>().assign(id, Added());
    m_database.table<Updated>().assign(id, Updated());

    return id;
}

EntityId Scene::createGizmo()
{
    auto id = createEntity();

    m_transformSystem.addTransform(id, Transform());
    m_transformSystem.addTransformGizmo(id, TransformGizmo());

    return id;
}
