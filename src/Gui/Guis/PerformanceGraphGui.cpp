#include "PerformanceGraphGui.h"

#include "imgui.h"
#include "implot.h"
#include "Parsing/VrApiStatistics.h"
#include "Stats/PerformanceStats.h"

PerformanceGraphGui::PerformanceGraphGui()
{
    PerformanceStats::GenerateTestData();
}

void PerformanceGraphGui::Draw() const
{
	ImGui::Begin(PerformanceGraphGui::GuiName.c_str(), nullptr);

    static bool show_lines = true;
    static bool show_fills = true;
    static float fill_ref = 0;
    static int shade_mode = 0;

    DrawGraphControls(show_lines, show_fills, fill_ref, shade_mode);

    auto fps = VrApiStatistics::GetInstance().Fps;

    if (ImPlot::BeginPlot("Performance")) 
    {
        const size_t length = fps.size;
        const auto labels = fps.labels;

        const double range = fps.max - fps.min;
        const double min = fps.min;
        const double max = fps.max + (range * 0.15);

        ImPlot::SetupAxes("Index","Value");
        ImPlot::SetupAxesLimits(0, length, min, max);

        if (show_fills) {
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
            ImPlot::PlotShaded("Frame Time", labels.data(), fps.values.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, 0);
            //ImPlot::PlotShaded("Stock 2", labels, PerformanceStats::frameTime.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
            ImPlot::PopStyleVar();
        }
        if (show_lines) {
            ImPlot::PlotLine("Frame Time", labels.data(), fps.values.data(), length);
            //ImPlot::PlotLine("Stock 2", labels, PerformanceStats::frameTime.data(), length);
        }
        ImPlot::EndPlot();
    }

    ImGui::End();
}

void PerformanceGraphGui::DrawGraphControls(bool& showLines, bool& showFills, float& fillRef, int& shadeMode)
{
	ImGui::Checkbox("Lines",&showLines); ImGui::SameLine();
    ImGui::Checkbox("Fills",&showFills);

    if (showFills) 
    {
        ImGui::SameLine();
        if (ImGui::RadioButton("To -INF",shadeMode == 0))
        {
	        shadeMode = 0;
        }

        ImGui::SameLine();
        if (ImGui::RadioButton("To +INF",shadeMode == 1))
        {
	        shadeMode = 1;
        }

        ImGui::SameLine();
        if (ImGui::RadioButton("To Ref",shadeMode == 2))
        {
	        shadeMode = 2;
        }

        if (shadeMode == 2) {
            ImGui::SameLine();
            ImGui::SetNextItemWidth(49);
            ImGui::DragFloat("##Ref",&fillRef, 1, -100, 500);
        }
    }
}