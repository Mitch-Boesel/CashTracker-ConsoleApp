#include "category.h"

class Essentials
{
private:

public:
	std::unordered_map<string, Category> _eCategories;

	void buildEssentials(string user);
	void storeEssentials(string user);
};