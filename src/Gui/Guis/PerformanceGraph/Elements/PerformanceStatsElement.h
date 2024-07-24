#pragma once

#include <imgui.h>
#include <memory>

#include "StatisticGroup.h"

class PerformanceStatsElement
{
public:
	PerformanceStatsElement(std::shared_ptr<StatisticGroup> statistics);
	void Draw() const;

	mutable ImVector<size_t> selection;

private:
	std::shared_ptr<StatisticGroup> statisticGroup;
};
