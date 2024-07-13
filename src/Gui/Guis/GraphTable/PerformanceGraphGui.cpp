#include "PerformanceGraphGui.h"

#include <format>

#include "imgui.h"
#include "implot.h"
#include "StatsGui.h"
#include "Parsing/VrApiStatistics.h"

void PerformanceGraphGui::Draw() const
{
	ImGui::Begin(GuiName.c_str(), nullptr);

    static bool show_lines = true;
    static bool show_fills = true;
    static float fill_ref = 0;
    static int shade_mode = 0;

    DrawGraphControls(show_lines, show_fills, fill_ref, shade_mode);

    auto statistics = VrApiStatistics::GetInstance().GetStatistics();
	for (const size_t selection : StatsGui::Selection)
	{
		auto statistic = statistics[selection];
        if (statistic->size == 0)
        {
	        continue;
        }

        const size_t length = statistic->size;
        std::string title = std::format("{} (Count: {})", statistic->name, length);
        if (ImPlot::BeginPlot(title.c_str())) 
	    {
	        const auto labels = statistic->labels;

	        const double range = statistic->max - statistic->min;
	        const double min = statistic->min;
	        const double max = statistic->max + (range * 0.15);

	        ImPlot::SetupAxes("Index","Value");
	        ImPlot::SetupAxesLimits(0, length, min, max);

	        if (show_fills) 
            {
	            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
	            ImPlot::PlotShaded((statistic->name + "_1").c_str(), labels.data(), statistic->values.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, 0);
	            //ImPlot::PlotShaded("Stock 2", labels, PerformanceStats::frameTime.data(), length, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref, flags);
	            ImPlot::PopStyleVar();
	        }

	        if (show_lines) 
            {
	            ImPlot::PlotLine((statistic->name + "_1").c_str(), labels.data(), statistic->values.data(), length);
	            //ImPlot::PlotLine("Stock 2", labels, PerformanceStats::frameTime.data(), length);
	        }
	        ImPlot::EndPlot();
	    }
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

std::string& PerformanceGraphGui::GetName() const
{
	return GuiName;
}