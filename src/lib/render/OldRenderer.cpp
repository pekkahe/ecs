#include <Precompiled.hpp>
#include <render/OldRenderer.hpp>

#include <core/ecs/Query.hpp>
#include <scene/components/Camera.hpp>
#include <ui/Window.hpp>

using namespace eng;
using namespace eng::gfx;

Renderer::Renderer()
{
    m_shaders.emplace_back(Shader(
        "../shaders/vertex.vert",
        "../shaders/fragment.frag"));
    m_shaders.emplace_back(Shader(
        "../shaders/vertex.vert", 
        "../shaders/fragment2.frag"));
    m_shaders.emplace_back(Shader(
        "../shaders/vertex_tex.vert",
        "../shaders/fragment_tex.frag"));
    m_shaders.emplace_back(Shader(
        "../shaders/vertex_proj.vert",
        "../shaders/fragment_tex.frag"));
    m_shaders.emplace_back(Shader(
        "../shaders/vertex_proj.vert",
        "../shaders/fragment2.frag"));

    m_textures.emplace_back(Texture(
        "../data/container.jpg", GL_CLAMP_TO_EDGE, GL_NEAREST, GL_RGB));
    m_textures.emplace_back(Texture(
        "../data/awesomeface.png", GL_REPEAT, GL_NEAREST, GL_RGBA));

    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
}

void Renderer::beginFrame()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Scene&)
{
}

void Renderer::endFrame()
{
}

void Renderer::drawTriangle()
{
    // Vertex data
    float vertices[] = 
    {
         // Positions        // Colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top 
    };

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Generate and bind a Vertex Buffer Object to GL_ARRAY_BUFFER
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //! Render loop
    m_shaders[0].use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::drawTwoTriangles()
{
    // Vertex data
    float vertices[] =
    {
        // First triangle
        -0.1f, 0.0f, 0.0f,
        -0.6f, 0.5f, 0.0f,
         0.4f, 0.5f, 0.0f,
        // Second triangle
         0.1f,  0.0f, 0.0f,
         0.6f, -0.5f, 0.0f,
        -0.4f, -0.5f, 0.0f,
    };

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind a Vertex Buffer Object to GL_ARRAY_BUFFER
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Link vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //! Render loop
    m_shaders[0].use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::drawTwoTrianglesWithOwnBuffers()
{
    // Vertex data
    float vertices[][9] =
    {
        // First triangle
        {
            -0.1f, 0.0f, 0.0f,
            -0.6f, 0.5f, 0.0f,
            0.4f, 0.5f, 0.0f
        },
        // Second triangle
        {
            0.1f, 0.0f, 0.0f,
            0.6f, -0.5f, 0.0f,
            -0.4f, -0.5f, 0.0f
        }
    };

    //unsigned int verticesCount = 18;
    
    // Generate Vertex Array Objects and Vertex Buffer Objects
    unsigned int VAO[2];
    unsigned int VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // Setup first triangle vertices
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]), vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup second triangle vertices
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[1]), vertices[1], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //! Render loop
    m_shaders[0].use();
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::drawTwoTrianglesWithOwnBuffersAndPrograms()
{
    // Vertex data
    float vertices[][9] =
    {
        // First triangle
        {
            -0.1f, 0.0f, 0.0f,
            -0.6f, 0.5f, 0.0f,
            0.4f, 0.5f, 0.0f
        },
        // Second triangle
        {
            0.1f, 0.0f, 0.0f,
            0.6f, -0.5f, 0.0f,
            -0.4f, -0.5f, 0.0f
        }
    };

    //unsigned int verticesCount = 18;

    // Generate Vertex Array Objects and Vertex Buffer Objects
    unsigned int VAO[2];
    unsigned int VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // Setup first triangle vertices
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]), vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup second triangle vertices
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[1]), vertices[1], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //! Render loop
    m_shaders[0].use();
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    float timeValue = static_cast<float>(glfwGetTime());
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

    m_shaders[1].use();
    m_shaders[1].setFloat("ourColor", greenValue);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::drawRectangle()
{
    // Vertex data
    float vertices[] = 
    {
        0.5f,  0.5f, 0.0f,	// Top right
        0.5f, -0.5f, 0.0f,	// Bottom right
        -0.5f, -0.5f, 0.0f,	// Bottom left
        -0.5f,  0.5f, 0.0f	// Top left 
    };
    unsigned int indices[] = 
    {  // Note that we start from 0!
        0, 1, 3,   // First triangle
        1, 2, 3    // Second triangle
    };

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Generate and bind a Vertex Buffer Object to GL_ARRAY_BUFFER
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and bind a Element Buffer Object to GL_ELEMENT_ARRAY_BUFFER
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Link vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //! Render loop
    m_shaders[0].use();
    glBindVertexArray(VAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Default
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::drawTexture()
{
    // Setup four vertices with three attributes
    float vertices[] = {
         // Positions         // Colors           // Texture coordinates
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // Top left 
    };

    unsigned int indices[] =
    {    // Note that we start from 0
         0, 1, 3,   // First triangle
         1, 2, 3    // Second triangle
    };

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind a Vertex Buffer Object to GL_ARRAY_BUFFER
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and bind a Element Buffer Object to GL_ELEMENT_ARRAY_BUFFER
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Link vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_shaders[2].use();
    m_shaders[2].setInt("texture1", 0);
    m_shaders[2].setInt("texture2", 1);

    //! Render loop
    // Activate the texture unit first before binding texture
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, m_textures[0].id());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textures[1].id());

    glBindVertexArray(VAO);

    {
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        m_shaders[2].setMat4("transform", trans);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    {
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::scale(trans, glm::sin((float) glfwGetTime()) * glm::vec3(1.0f, 1.0f, 1.0f));
        
        m_shaders[2].setMat4("transform", trans);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Renderer::drawCube(const Camera& camera)
{
    float vertices[] = 
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = 
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind a Vertex Buffer Object to GL_ARRAY_BUFFER
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Link vertex attributes
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_shaders[3].use();
    m_shaders[3].setInt("texture1", 0);
    m_shaders[3].setInt("texture2", 1);

    m_shaders[3].setMat4("view", camera.viewMatrix);
    m_shaders[3].setMat4("projection", camera.projectionMatrix);

    //! Render loop
    // Activate the texture unit first before binding texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textures[0].id());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textures[1].id());

    glBindVertexArray(VAO);

    for (int i = 0; i < 10; i++)
    {
        float angle = 20.0f * i;

        glm::mat4 model(1.0f);
        model = glm::translate(model, cubePositions[i]);
        if (i % 3 == 0)
        {
            angle = (float) glfwGetTime() * 25.0f;
        }
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        m_shaders[3].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}
