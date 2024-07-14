#pragma once

#include <memory>

class GuiDrawer;

class Drawer
{
public:
    virtual void Draw() const = 0;
    virtual const std::string& GetName() const = 0;

    virtual ~Drawer() {}

    std::shared_ptr<GuiDrawer> guiDrawer;
};
