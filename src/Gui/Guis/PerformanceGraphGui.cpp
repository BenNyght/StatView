#include "PerformanceGraphGui.h"

#include "imgui.h"
#include "implot.h"
#include "Stats/PerformanceStats.h"

PerformanceGraphGui::PerformanceGraphGui()
{
    PerformanceStats::GenerateTestData();
}

void PerformanceGraphGui::Draw() const
{
	ImGui::Begin("Graph");

    static bool show_lines = true;
    static bool show_fills = true;
    static float fill_ref = 0;
    static int shade_mode = 0;
    static ImPlotShadedFlags flags = 0;
    ImGui::Checkbox("Lines",&show_lines); ImGui::SameLine();
    ImGui::Checkbox("Fills",&show_fills);
    if (show_fills) {
        ImGui::SameLine();
        if (ImGui::RadioButton("To -INF",shade_mode == 0))
            shade_mode = 0;
        ImGui::SameLine();
        if (ImGui::RadioButton("To +INF",shade_mode == 1))
            shade_mode = 1;
        ImGui::SameLine();
        if (ImGui::RadioButton("To Ref",shade_mode == 2))
            shade_mode = 2;
        if (shade_mode == 2) {
            ImGui::SameLine();
            ImGui::SetNextItemWidth(49);
            ImGui::DragFloat("##Ref",&fill_ref, 1, -100, 500);
        }
    }

    if (ImPlot::BeginPlot("Stock Prices")) {
        ImPlot::SetupAxes("Days","Price");
        ImPlot::SetupAxesLimits(0,100,0,500);

        auto length = PerformanceStats::frameTime.size();
        auto labels = PerformanceStats::label.data();

        if (show_fills) {
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
            ImPlot::PlotShaded("Stock 1", labels, PerformanceStats::frameTime.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
            ImPlot::PlotShaded("Stock 2", labels, PerformanceStats::frameTime.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
            ImPlot::PlotShaded("Stock 3", labels, PerformanceStats::frameTime.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
            ImPlot::PopStyleVar();
        }
        if (show_lines) {
            ImPlot::PlotLine("Stock 1", labels, PerformanceStats::frameTime.data(), length);
            ImPlot::PlotLine("Stock 2", labels, PerformanceStats::frameTime.data(), length);
            ImPlot::PlotLine("Stock 3", labels, PerformanceStats::frameTime.data(), length);
        }
        ImPlot::EndPlot();
    }

    ImGui::End();
}