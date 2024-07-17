
#include "StatisticSelectionElement.h"

#include <imgui.h>
#include <iostream>
#include <ostream>

#include "File/FileUtility.h"
#include "tinyfiledialogs.h"

void StatisticSelectionElement::Draw()
{
	if (ImGui::Button("Parse Logcat File"))
	{
		std::cout << "Button Down" << std::endl;

		FileUtility::OpenFilePanel("Select Logcat File", "", { "txt", "logcat" });
	}
}
