#pragma once

#include <iostream>
#include <map>
#include <ostream>

class ILateUpdate
{
public:
    ILateUpdate()
	{ 
		id = ++currentId;
		objects[id] = this;

		std::cout << "Constructed Update" << std::endl;
	}

    ILateUpdate(const ILateUpdate&)
	{
	    id = ++currentId;
	    objects[id] = this;
	}

	virtual ~ILateUpdate()
	{
		objects.erase(id);

		std::cout << "Deconstructed Update" << std::endl;
	}

    virtual void LateUpdate() = 0;

	static std::map<int, ILateUpdate*>& GetMapOfObjects()
	{
		return objects;
	}

private:
    inline static int currentId;
    inline static std::map<int, ILateUpdate*> objects;

    int id;
};