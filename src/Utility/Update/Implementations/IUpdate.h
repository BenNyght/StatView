#pragma once

#include <iostream>
#include <map>
#include <ostream>

class IUpdate
{
public:
    IUpdate()
	{ 
		id = ++currentId;
		objects[id] = this;

		std::cout << "Constructed Update" << std::endl;
	}

    IUpdate(const IUpdate&)
	{
	    id = ++currentId;
	    objects[id] = this;
	}

	virtual ~IUpdate()
	{
		objects.erase(id);

		std::cout << "Deconstructed Update" << std::endl;
	}

    virtual void Update() = 0;

	static std::map<int, IUpdate*>& GetMapOfObjects()
	{
		return objects;
	}

private:
    inline static int currentId;
    inline static std::map<int, IUpdate*> objects;

    int id;
};