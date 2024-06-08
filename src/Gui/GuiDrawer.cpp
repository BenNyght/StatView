
#include "GuiDrawer.h"

#include <vector>
#include <memory>

#include "IDrawer.h"
#include "Guis/HelloWorldGui.h"
#include "Guis/PerformanceGraphGui.h"

GuiDrawer::GuiDrawer()
{
    drawers.push_back(std::make_unique<PerformanceGraphGui>());
    drawers.push_back(std::make_unique<HelloWorldGui>());
}

void GuiDrawer::Draw() const
{
    for (const auto& drawer : drawers) 
    {
        drawer->Draw();
    }
}
