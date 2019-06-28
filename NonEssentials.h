#include "category.h"

class NonEssentials
{
private:

public:
	std::unordered_map<string, Category> _nCategories;
	void buildNonEssentials(string user);
	void storeNonEssentials(string user);

};