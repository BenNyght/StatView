#pragma once

class IDrawer
{
public:
    virtual void Draw() const = 0;
    virtual ~IDrawer() {}
};
