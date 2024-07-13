
#include "ProgressHandler.h"

std::vector<std::shared_ptr<ProgressItem>> ProgressHandler::ProgressItems {};

void ProgressHandler::AddProgressItem(const std::shared_ptr<ProgressItem>& item)
{
	bool exists = false;
    for (const auto& existingItem : ProgressItems) 
    {
        if (existingItem->Name == item->Name) 
        {
            exists = true;
            break;
        }
    }

    if (exists == false)
    {
	    ProgressItems.push_back(item);
    }
}

void ProgressHandler::RemoveProgressItem(const std::shared_ptr<ProgressItem>& item)
{
    const int size = static_cast<int>(ProgressItems.size());
	for (int i = size - 1; i >= 0; --i)
	{
		if (ProgressItems[i]->Name == item->Name)
		{
			ProgressItems.erase(std::next(ProgressItems.begin(), i));
		}
	}
}
