#pragma once

#include <imgui.h>
#include <memory>
#include <string>
#include <vector>

#include "IDrawer.h"

class GuiDrawer
{
public:
	GuiDrawer();

	void Draw();

	static inline std::string GuiName = "Main Window";

private:
	std::vector<std::shared_ptr<IDrawer>> activeDrawers;
	std::vector<std::shared_ptr<IDrawer>> drawers;

	void SetupDockBuilder();

	template <typename TDrawer>
	void DockDrawer(ImGuiID dockId, ImGuiDockNodeFlags dockFlags);

	template <typename TDrawer>
	void AddDockedDrawer(ImGuiID dockId);

	template <typename TDrawer>
	void AddDrawer();

	template <class TDrawer>
	void AddActiveDrawer();

	template <class TDrawer>
	void RemoveActiveDrawer();
};
