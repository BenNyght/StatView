#pragma once

class IDrawer
{
public:
    virtual void Draw() const = 0;
    virtual const std::string& GetName() const = 0;

    virtual ~IDrawer() {}
};
