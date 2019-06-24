#include "NonEssentials.h"

NonEssentials::NonEssentials()	// Essentials constructor, building from previous data
{
	std::ifstream eFile;		//opening the NonEssentials file
	eFile.open("NonEssentials.txt");

	string store = "", date = "", category = "", sMoney = "", nItems = "";	// blank = ""		//declaring a bunch of variables I'll need
	double money = 0.0;
	int numItems = 0;

	if (eFile.peek() != (int)"")
	{
		while (eFile.eof() != true)	//parsing the file while I'm not at the end
		{
			numItems = 0; // reseting for each new category

			getline(eFile, category, ',');	//get the category name
			Category* newCategory = new Category(money, numItems, category);
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
			this->_nCategories.insert(std::make_pair(newCategory->getCatName(), *newCategory));	//adding the category to the Essentials hash table (_groups)
			//getline(eFile, blank);	//eating up the blank line between categories or the last line
		}
	}
	eFile.close();
}

NonEssentials::~NonEssentials()
{
	std::ofstream oFile;		//creating the file to write to when application closes
	oFile.open("NonEssentials.txt");
	oFile.clear();

	int counter = 0;
	std::unordered_map<string, Category>::iterator it = this->_nCategories.begin();	//iterator to iterate through the hash table
	for (; it != this->_nCategories.end(); it++)	// this loop prints the contents of the essentials hash table to the Essentials.txt file
	{
		if (counter != 0)
			oFile << endl;

		oFile << it->second.getCatName() << "," << it->second.getNumPurchases();
		it->second.printPurchasesToFile(oFile);
		counter++;
	}
	oFile.close();
}