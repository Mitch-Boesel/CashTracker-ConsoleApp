#include "category.h"

class Essentials
{
private:
//	int _nextKey; changing hash key to an int

public:
	std::unordered_map<string, Category> _eCategories;

	Essentials();
	~Essentials();
};