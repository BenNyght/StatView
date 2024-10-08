#include "PerformanceGraphElement.h"

#include <format>

#include "imgui.h"
#include "implot.h"
#include "PerformanceStatsElement.h"
#include "StatisticGroup.h"

PerformanceGraphElement::PerformanceGraphElement(std::shared_ptr<PerformanceStatsElement> performanceStatsElement, std::shared_ptr<StatisticGroup> statistics)
	: performanceStatsElement(performanceStatsElement), statistics(statistics)
{}

void PerformanceGraphElement::Draw()
{
    if (performanceStatsElement->selection.empty())
	{
		performanceStatsElement->selection.push_back(static_cast<size_t>(0));
	}

    auto& allStatistics = statistics->statistics;
    if (allStatistics.size() == 0 || allStatistics[0].size == 0)
    {
	    static Statistic blankStatistic { "" };
		if (blankStatistic.size == 0)
		{
			blankStatistic.AddValue(0);
		}

		DrawGraph(blankStatistic);
    }
    else
    {
        for (const size_t selection : performanceStatsElement->selection)
		{
			auto statistic = allStatistics[selection];
			DrawGraph(statistic);
		}
    }
}

void PerformanceGraphElement::DrawGraph(Statistic& statistic)
{
    static bool showLines = true;
    static bool showFills = true;
    static float fillRef = 0;
    static int shadeMode = 0;

    DrawGraphControls(showLines, showFills, fillRef, shadeMode);

    const size_t length = statistic.size;
    std::string title = std::format("{} (Count: {})", statistic.name, length);
    if (ImPlot::BeginPlot(title.c_str())) 
    {
        const auto labels = statistic.labels;

        const double range = statistic.max - statistic.min;
        const double min = statistic.min;
        const double max = statistic.max + (range * 0.15);

        ImPlot::SetupAxes("Index","Value");
        ImPlot::SetupAxesLimits(0, length, min, max);

        std::string legendName = statistic.name;
        if (statistic.suffix.empty() == false)
        {
			legendName += "(" + statistic.suffix + ")";
        }

        if (showFills) 
        {
            ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
            ImPlot::PlotShaded(legendName.c_str(), labels.data(), statistic.values.data(), length, shadeMode == 0 ? -INFINITY : shadeMode == 1 ? INFINITY : fillRef, 0);
            ImPlot::PopStyleVar();
        }

        if (showLines)
        {
            ImPlot::PlotLine(legendName.c_str(), labels.data(), statistic.values.data(), length);
        }
        ImPlot::EndPlot();
    }
}

void PerformanceGraphElement::DrawGraphControls(bool& showLines, bool& showFills, float& fillRef, int& shadeMode)
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