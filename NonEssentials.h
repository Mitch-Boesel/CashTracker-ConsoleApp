#include "category.h"

class NonEssentials
{
private:
	int _user;

public:
	std::unordered_map<string, Category> _nCategories;
//	int getNextKey(); chagning hash key to a string	
	NonEssentials();
	~NonEssentials();

};