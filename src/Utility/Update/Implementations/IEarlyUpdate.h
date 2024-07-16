#pragma once

#include <iostream>
#include <map>
#include <ostream>

class IEarlyUpdate
{
public:
    IEarlyUpdate()
	{ 
		id = ++currentId;
		objects[id] = this;

		std::cout << "Constructed Update" << std::endl;
	}

    IEarlyUpdate(const IEarlyUpdate&)
	{
	    id = ++currentId;
	    objects[id] = this;
	}

	virtual ~IEarlyUpdate()
	{
		objects.erase(id);

		std::cout << "Deconstructed Update" << std::endl;
	}

    virtual void EarlyUpdate() = 0;

	static std::map<int, IEarlyUpdate*>& GetMapOfObjects()
	{
		return objects;
	}

private:
    inline static int currentId;
    inline static std::map<int, IEarlyUpdate*> objects;

    int id;
};