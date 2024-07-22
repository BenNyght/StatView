#pragma once

#include <imgui.h>
#include <memory>

#include "VrApiStatistics.h"

class PerformanceStatsElement
{
public:
	PerformanceStatsElement(std::shared_ptr<VrApiStatistics> statistics);
	void Draw() const;

	mutable ImVector<size_t> selection;

private:
	std::shared_ptr<VrApiStatistics> statistics;
};
