#pragma once
#include <memory>
#include <vector>

#include "ProgressItem.h"

class ProgressHandler
{
public:
	static void AddProgressItem(const std::shared_ptr<ProgressItem>& item);
	static void RemoveProgressItem(const std::shared_ptr<ProgressItem>& item);

	static std::vector<std::shared_ptr<ProgressItem>> ProgressItems;
};
