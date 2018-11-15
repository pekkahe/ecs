#include <Precompiled.hpp>
#include <scene/Scene.hpp>

#include <graphics/Mesh.hpp>
#include <scene/Transform.hpp>
#include <scene/TransformGizmo.hpp>

using namespace eng;

Scene::Scene(std::shared_ptr<Window> window) :
    m_window(std::move(window)),
    m_transformSystem(m_database),
    m_renderSystem(m_database),
    m_cameraSystem(m_database, m_window),
    m_editorSystem(m_database)
{
    registerSystem(m_transformSystem);
    registerSystem(m_renderSystem);
    registerSystem(m_cameraSystem);
    registerSystem(m_editorSystem);

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
    // TODO: Move entity creation and deletion elsewhere
    // - Deletion is thread-safe since it's simply a tag which is lazily evaluated
    // - Creation is not, as it requires mutable access to various systems
    //
    //   How would a e.g. WeaponSystem instantiate a Bullet entity?
    //   1) WeaponSystem initiates the entity creation, by either
    //      a) directly creating the id if the database id counter is atomic
    //      b) letting the scene sync point create the id, and transfer the components
    //         to the scene database from the system's local database
    //   2) assigns the Bullet components (along with any other required components
    //      owned by the system) to it and marks it Added
    //   3) other systems react to the new component by adding their own components
    //      e.g. TransformSystem notices the entity with the Added and Bullet components
    //      and assigns a Transform component to it
    //   * this spreads out entity creation to multiple systems and makes it harder to
    //     understand how they are composed, but it should be easy to parallelize?
    //   * the entity would be in this "building process" phase for at least the initial and
    //     second frame, can this introduce errors in the form of too early incorrect queries?
    //   * if entity creation takes multiple frames, we might not want to render or activate
    //     it until the process is done
    //   * nevertheless, this adds a 1-2 frame delay to entity spawning and activation, how
    //     would this perform with input or visually sensitive contexts, e.g. firing a weapon?
    //
    //   Entity creation needs to be lock-free within systems (other options):
    //   a) add a synchronous "create" step for systems where they have mutable access
    //      to each other (and the database), and which is executed before the parallel
    //      update step
    //   b) change database entity id counter to atomic and allow ids to be created
    //      within concurrent system updates, but dispatch the component assignment
    //      (and mutable system access) to the start of next frame

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
    auto id = m_database.createEntity();

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
    auto id = m_database.createEntity();

    m_transformSystem.addTransform(id, Transform());
    m_editorSystem.addTransformGizmo(id, TransformGizmo());

    m_database.table<Added>().assign(id, Added());
    m_database.table<Updated>().assign(id, Updated());

    return id;
}
