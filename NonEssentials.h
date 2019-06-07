#include "category.h"

class NonEssentials
{
private:
//	int _nextKey; changing hash key to a string

public:
	std::unordered_map<string, Category> _groups;
//	int getNextKey(); chagning hash key to a string	
	NonEssentials();
	~NonEssentials();

};