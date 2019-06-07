#include "NonEssentials.h"

NonEssentials::NonEssentials()	// Essentials constructor, building from previous data
{
	//this->_nextKey = 0;	//setting key to 0
	std::ifstream eFile;		//opening the Essentials file
	eFile.open("NonEssentials.txt");

	string store = "", date = "", field = "", sMoney = "", nItems = "", blank = "";		//declaring a bunch of variables I'll need
	double money = 0.0;
	int numItems = 0;

	while (eFile.eof() != true)	//parsing the file while I'm not at the end
	{
		getline(eFile, field, ',');	//get the category name
		Category* newCategory = new Category(this->_nextKey, money, numItems, field);
	//	this->_nextKey++;	//incrementing the _key
		getline(eFile, nItems);
		numItems = stoi(nItems); //number of purchases there will be

		for (int i = 0; i < numItems; i++)	//parsing and saving all the parsed purchases
		{
			getline(eFile, store, ',');	//parsing the line
			getline(eFile, date, ',');
			getline(eFile, sMoney);
			money = std::stod(sMoney);	//converting to a double
			Purchase* newPurchase = new Purchase(store, money, date);	//creating the new purchase object
			newCategory->addPurchase(*newPurchase);	//adding the purchase to the _history vector withing the category object
		}
		// by now the all the purchases will be added to the Category object
		this->_groups.insert(std::make_pair(newCategory->getKey(), *newCategory));	//adding the category to the Essentials hash table (_groups)
		getline(eFile, blank);	//eating up the blank line between categories or the last line
	}
	eFile.close();
}

NonEssentials::~NonEssentials()
{
	std::ofstream oFile;		//creating the file to write to when application closes
	oFile.open("NonEssentials.txt");
	oFile.clear();

	std::unordered_map<int, Category>::iterator it = this->_groups.begin();	//iterator to iterate through the hash table
	for (; it != this->_groups.end(); it++)	// this loop prints the contents of the essentials hash table to the Essentials.txt file
	{
		oFile << it->second.getField() << "," << it->second.getNumPurchases << endl;
		it->second.printPurchasesToFile(oFile);
		oFile << endl;
	}
	oFile.close();
}

int NonEssentials::getNextKey()
{
	return this->_nextKey;
}