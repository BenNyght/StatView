#pragma once

#include <iostream>
#include <map>
#include <ostream>

class IDraw
{
public:
    IDraw()
	{ 
		id = ++currentId;
		objects[id] = this;

		std::cout << "Constructed Update" << std::endl;
	}

    IDraw(const IDraw&)
	{
	    id = ++currentId;
	    objects[id] = this;
	}

	virtual ~IDraw()
	{
		objects.erase(id);

		std::cout << "Deconstructed Update" << std::endl;
	}

    virtual void Draw() = 0;

	static std::map<int, IDraw*>& GetMapOfObjects()
	{
		return objects;
	}

private:
    inline static int currentId;
    inline static std::map<int, IDraw*> objects;

    int id;
};