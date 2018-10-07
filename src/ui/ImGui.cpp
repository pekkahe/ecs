#include <Precompiled.hpp>
#include <ui/ImGui.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace
{
    std::array<float, 16> unwrapMatrix(const eng::mat4& matrix)
    {
        const float* source = static_cast<const float*>(glm::value_ptr(matrix));

        std::array<float, 16> dest;
        for (int i = 0; i < 16; ++i)
        {
            dest[i] = source[i];
        }
        return dest;
    }
}

void eng::imgui::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //const char* glsl_version = "#version 330 core"; // core -> es
    ImGui_ImplOpenGL3_Init(NULL); // Use default GLSL version
}

void eng::imgui::deinit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//bool open = true;
void eng::imgui::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
    
    //::ImGui::ShowDemoWindow(&open);
}

void eng::imgui::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(::ImGui::GetDrawData());
}

bool eng::imgui::gizmoManipulate(
    mat4& model,
    const mat4& view,
    const mat4& projection,
    ImGuizmo::OPERATION operation)
{
    auto modelMatrix = unwrapMatrix(model);
    auto viewMatrix = unwrapMatrix(view);
    auto projectionMatrix = unwrapMatrix(projection);

    auto& io = ImGui::GetIO();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
    
    // Setup gizmo to be drawed
    ImGuizmo::Manipulate(
        &viewMatrix[0],
        &projectionMatrix[0],
        operation,
        ImGuizmo::LOCAL,
        &modelMatrix[0],
        nullptr,
        nullptr,  // useSnap ? &snap[0]
        nullptr,  // boundSizing ? bounds
        nullptr); // boundSizingSnap ? boundsSnap 

    model = glm::make_mat4(&modelMatrix[0]);

    // Return whether gizmo was manipulated this frame or not
    return ImGuizmo::IsUsing();
}

//ImGuizmo::DrawCube(viewMatrix, projectionMatrix, modelMatrix);
//float translation[3] = { 0 };
//float rotation[3] = { 0 };
//float scale[3] = { 0 };
//ImGuizmo::DecomposeMatrixToComponents(modelMatrix, translation, rotation, scale);
//ImGui::InputFloat3("Tr", matrixTranslation, 3);
//ImGui::InputFloat3("Rt", matrixRotation, 3);
//ImGui::InputFloat3("Sc", matrixScale, 3);
//ImGuizmo::RecomposeMatrixFromComponents(translation, rotation, scale, modelMatrix);

