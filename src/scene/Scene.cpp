#include <Precompiled.hpp>

#include <component/Components.hpp>
#include <scene/Scene.hpp>

using namespace eng;

Scene::Scene() :
	m_transformSystem(m_database),
	m_renderSystem(m_database)
{
	registerSystem(m_transformSystem);
	registerSystem(m_renderSystem);
}

Scene::~Scene()
{
}

void Scene::update()
{
	// sync()

	for (auto system : m_systems)
	{
		system->update();
	}

	// sync()
}

void Scene::createTestMesh()
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

	m_renderSystem.addComponent(id, std::move(mesh));
	m_transformSystem.addComponent(id, Transform());
}

EntityId Scene::createEntity()
{
	auto id = m_database.createEntity();

	return id;
}

Query<> Scene::query() const
{
	return Query<>(m_database);
}

void Scene::registerSystem(System& system)
{
	m_systems.emplace_back(&system);
}
