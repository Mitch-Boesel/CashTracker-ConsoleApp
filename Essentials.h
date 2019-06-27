#include "category.h"

class Essentials
{
private:
	int _user;

public:
	std::unordered_map<string, Category> _eCategories;

	Essentials();
	~Essentials();
};