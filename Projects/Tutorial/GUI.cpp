#include "GUI.h"

void GUI::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::draw() {
    //IMGUI RENDER
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui window
    {
        ImGui::Begin("My Window");                          // Create a window called "Hello, ImGui!" and append into it.
        ImGui::Text("L System");               // Display some text (you can use a format strings too)
        ImGui::LabelText("label", "Value");
        ImGui::SliderFloat("size", &size, 0.01, 0.1);
        
        ImGui::Text("How many Iterations?");
        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { iterations--; }
        ImGui::SameLine(0.0f, spacing);
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { iterations++; }
        ImGui::PopItemFlag();
        ImGui::SameLine();
        ImGui::Text("%d", iterations);

        ImGui::Text("Edge-Rewriting");
        for (int i = 0; i < 6; i++)
        {
            if (i > 0)
                ImGui::SameLine();
            ImGui::PushID(i);
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
            ImGui::Button("Click");
            ImGui::PopStyleColor(3);
            ImGui::PopID();
        }

        ImGui::Text("Stochastic");
            ImGui::Button("Random1");
            ImGui::SetItemTooltip("Re-Click to generate random values");
            ImGui::SameLine();
            ImGui::Button("Random2");
            ImGui::SetItemTooltip("Re-Click to generate random values");
        ImGui::End();
    }

    ImGui::ShowDemoWindow();

    //UIrender();
}

void GUI::UIrender() {
    //IMGUI RENDER
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::cleanup() {
    //IMGUI CLEANUP
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}