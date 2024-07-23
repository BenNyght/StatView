#pragma once

#include <imgui.h>
#include <memory>
#include <string>
#include <vector>

#include "Drawer.h"
#include "HelloWorldGui.h"
#include "ImGuiDemoGui.h"
#include "Update/Implementations/IDraw.h"

class GuiDrawer : public std::enable_shared_from_this<GuiDrawer>, IDraw
{
public:
	void Draw() override;

	static inline std::string GuiName = "Main Window";

	template <typename TDrawer>
	TDrawer* AddDrawer()
	{
		std::shared_ptr<TDrawer> drawer = std::make_shared<TDrawer>();
		drawer->guiDrawer = GuiDrawerInstance();

		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr && drawers[i]->instanceId == drawer->instanceId) 
	        {
	            return foundDrawer;
	        }
		}

		drawers.push_back(drawer);
		return drawer.get();
	}

	template <typename TDrawer>
	void RemoveDrawer()
	{
		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            drawers.erase(drawers.begin() + i);
	        }
		}
	}

	void RemoveDrawer(const Drawer* drawer)
	{
		for (int i = 0; i < drawers.size(); ++i)
		{
	        if (drawers[i].get() == drawer) 
	        {
	            drawers.erase(drawers.begin() + i);
	        }
		}
	}

	template <typename TDrawer>
	void EnableDrawer(const bool enable)
	{
		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
	            drawers[i]->enabled = enable;
	            break;
	        }
		}
	}

	template <typename TDrawer>
	void ToggleDrawer()
	{
		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
				bool currentlyEnabled = drawers[i]->enabled;
	            drawers[i]->enabled = !currentlyEnabled;
	            break;
	        }
		}
	}

	template <typename TDrawer>
	TDrawer* GetDrawer() const
	{
		for (int i = 0; i < drawers.size(); ++i)
		{
			auto foundDrawer = dynamic_cast<TDrawer*>(drawers[i].get());
	        if (foundDrawer != nullptr) 
	        {
				return foundDrawer;
	        }
		}

		return nullptr;
	}

private:
	std::vector<std::shared_ptr<Drawer>> drawers;
	std::shared_ptr<GuiDrawer> GuiDrawerInstance();

	void SetupDockBuilder();
	void SetupGuis();

	template <typename TDrawer>
	void DockDrawer(ImGuiID dockId, ImGuiDockNodeFlags dockFlags);
	void DockDrawer(std::string guiName, ImGuiID dockId, ImGuiDockNodeFlags dockFlags);
};
