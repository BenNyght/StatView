#pragma once

#include <imgui.h>
#include <memory>
#include <string>
#include <vector>

#include "Drawer.h"
#include "Update/Implementations/IDraw.h"

class GuiDrawer : public std::enable_shared_from_this<GuiDrawer>, IDraw
{
public:
	void Draw() override;

	static inline std::string GuiName = "Main Window";

	template <typename TDrawer>
	void AddActiveDrawer()
	{
	    for (int i = 0; i < activeDrawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(activeDrawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            return;
	        }
		}

		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            activeDrawers.push_back(drawers[i]);
	            break;
	        }
		}
	}

	template <typename TDrawer>
	void RemoveActiveDrawer()
	{
		for (int i = 0; i < activeDrawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(activeDrawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            activeDrawers.erase(activeDrawers.begin() + i);
	        }
		}
	}

	template <typename TDrawer>
	void ToggleActiveDrawer()
	{
		for (int i = 0; i < activeDrawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(activeDrawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            activeDrawers.erase(activeDrawers.begin() + i);
	            return;
	        }
		}

		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            activeDrawers.push_back(drawers[i]);
	            break;
	        }
		}
	}

private:
	std::vector<std::shared_ptr<Drawer>> activeDrawers;
	std::vector<std::shared_ptr<Drawer>> drawers;
	std::shared_ptr<GuiDrawer> GuiDrawerInstance();

	void SetupDockBuilder();
	void SetupGuis();

	template <typename TDrawer>
	void DockDrawer(ImGuiID dockId, ImGuiDockNodeFlags dockFlags);

	template <typename TDrawer>
	void AddDockedDrawer(ImGuiID dockId);

	template <typename TDrawer>
	void AddDrawer();
};
