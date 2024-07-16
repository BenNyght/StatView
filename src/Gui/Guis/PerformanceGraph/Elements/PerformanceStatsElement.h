#pragma once

#include <imgui.h>

class PerformanceStatsElement
{
public:
	PerformanceStatsElement();
	void Draw() const;

	mutable ImVector<size_t> selection;
};
