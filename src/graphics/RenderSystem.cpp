#include <Precompiled.hpp>
#include <graphics/RenderSystem.hpp>

#include <component/Query.hpp>

#include <scene/Scene.hpp>
#include <scene/Transform.hpp>
#include <ui/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <imgui.h>
#include <imgui_impl_opengl3.h>

using namespace eng;
using namespace eng::gfx;

RenderSystem::RenderSystem(Database& db) :
    m_meshTable(db.createTable<Mesh>())
{
    m_shaders.emplace_back(Shader(
        "../shaders/vertex_proj.vert",
        "../shaders/fragment_col.frag"));

    m_textures.emplace_back(Texture(
        "../data/container.jpg", GL_CLAMP_TO_EDGE, GL_NEAREST, GL_RGB));
    m_textures.emplace_back(Texture(
        "../data/awesomeface.png", GL_REPEAT, GL_NEAREST, GL_RGBA));
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(const Scene&)
{
    query()
        .hasComponent<Added>()
        .hasComponent(m_meshTable)
        .execute([&](
            EntityId id,
            const Added&,
            Mesh& mesh)
    {
        // Generate objects
        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);

        // Bind Vertex Array Object
        glBindVertexArray(mesh.VAO);

        // Bind Vertex Buffer Object to GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

        // Bind Element Buffer Object to GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

        // Link vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0); // shader: vec3 Pos
        glEnableVertexAttribArray(0);
    });

    query()
        .hasComponent<Deleted>()
        .hasComponent(m_meshTable)
        .execute([&](
            EntityId id, 
            const Deleted&,
            Mesh& mesh)
    {
        glDeleteVertexArrays(1, &mesh.VAO);
        glDeleteBuffers(1, &mesh.VBO);
        glDeleteBuffers(1, &mesh.EBO);
    });
}

void RenderSystem::beginFrame()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::render()
{
    auto camera = query().find<Camera>();
    assert(camera != nullptr && "No camera in scene");

    query()
        .hasComponent<Transform>()
        .hasComponent<Mesh>()
        .execute([&](
            EntityId id, 
            const Transform& transform,
            const Mesh& mesh)
    {
        m_shaders[0].use();
        m_shaders[0].setMatrix("view", camera->view);
        m_shaders[0].setMatrix("projection", camera->projection);
        m_shaders[0].setMatrix("model", transform.modelMatrix());

        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    });
}

void RenderSystem::endFrame()
{
}