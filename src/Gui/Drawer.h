#pragma once

#include <memory>
#include <string>

class GuiDrawer;

class Drawer
{
public:
    virtual void Draw() const = 0;
    virtual const std::string& GetName() const = 0;

    virtual ~Drawer() {}

    bool enabled = true;
    int instanceId = 0;
    std::shared_ptr<GuiDrawer> guiDrawer;
};
