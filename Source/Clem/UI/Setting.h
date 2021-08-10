// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

class Setting : public Layer
{
    void update(Time dt) override
    {
        if(!visible)
            return;

        ImGui::Begin("Setting", &visible);

        showFps(dt);

        int inputRate  = Main::getInputRate();
        int updateRate = Main::getUpdateRate();
        int renderRate = Main::getRenderRate();

        ImGui::PushItemWidth(70);
        LEFT_LABEL(ImGui::SliderInt, "Input rate ", &inputRate, 125, 1000, "%.1f");
        LEFT_LABEL(ImGui::SliderInt, "Update rate", &updateRate, 30, 240, "%.1f");
        LEFT_LABEL(ImGui::SliderInt, "Render rate", &renderRate, 30, 240, "%.1f");
        ImGui::PopItemWidth();

        Main::setInputRate(inputRate);
        Main::setUpdateRate(updateRate);
        Main::setRenderRate(renderRate);

        if(ImGui::BeginMenu("OpenGL info"))
        {
            ImGui::Text("Version : %s", glGetString(GL_VERSION));
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("Vendor  : %s", glGetString(GL_VENDOR));
            ImGui::EndMenu();
        }

        ImGui::End();
    }

private:
    void showFps(Time dt)
    {
        ImVec4 red(1, 0, 0, 1), yellow(1, 1, 0, 1), green(0, 1, 0, 1);
        auto   fps = Main::getFrameRate();

        static std::array<float, 120> fpsArray;
        static int                    i = 0;
        if(i < 120)
            fpsArray[i++] = 1000.f / dt.milliseconds();
        else
            i = 0;
        // auto fps = std::accumulate(fpsArray.begin(), fpsArray.end(), 0) / fpsArray.size();
        LEFT_LABEL(ImGui::PlotLines, "FPS", fpsArray.data(), (int)fpsArray.size());

        ImVec4 color;
        if(fps < 30)
            color = red;
        else if(fps < 60)
            color = yellow;
        else
            color = green;
        ImGui::TextColored(color, "%3u", fps);
        ImGui::SameLine();
        ImGui::Text("FPS, %4.1f ms/frame", 1000.f / fps);
    }

    bool visible = true;
};

} // namespace clem::ui
