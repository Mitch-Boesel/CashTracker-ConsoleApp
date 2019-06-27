#include "NonEssentials.h"

NonEssentials::NonEssentials()	// NonEssentials constructor, building from previous data in files
{
	cout << "(1)Mitch or (2)Mom?" << endl << endl;
	cin >> this->_user;
	std::ifstream eFile;		//opening the NonEssentials file
	if (_user == 1)
	{
		eFile.open("MitchNonEssentials.txt");
	}
	else if (_user == 2)
	{
		eFile.open("MomNonEssentials.txt");
	}

	string store = "", date = "", category = "", sMoney = "", nItems = "";	//declaring a bunch of variables I'll need
	double money = 0.0;		// will take the spentMoney string and convert to this money double
	int numItems = 0;		// convert nItems strings to this int

	if (eFile.peek() != (int)"")	// if the file isn't empty, parse it
	{
		while (eFile.eof() != true)	//parsing the file while I'm not at the end
		{
			numItems = 0; //  always reseting for each new category
			money = 0.0;  // always reseting for each new category

			getline(eFile, category, ',');	//get the category name
			Category* newCategory = new Category(money, numItems, category);
			getline(eFile, nItems);	// getting the number of purchases for the category
			numItems = stoi(nItems);	// converting the number of purchases to an int

			for (int i = 0; i < numItems; i++)	//parsing and saving all the parsed purchases
			{
				getline(eFile, store, ',');	//parsing the line
				getline(eFile, date, ',');
				getline(eFile, sMoney);
				money = std::stod(sMoney);	//converting spentMoney to a double
				Purchase* newPurchase = new Purchase(store, money, date);	//creating the new purchase object
				newCategory->addPurchase(*newPurchase);	//adding the purchase to the category vector
			}
			// by now the all the purchases for that category will be added to the Category object
			this->_nCategories.insert(std::make_pair(newCategory->getCatName(), *newCategory));	//adding the category to the NonEssentials hash table (_groups)
		}
	}
	eFile.close();	// closing the file
}

NonEssentials::~NonEssentials()
{
	std::ofstream oFile;		//creating the file to write to when application closes
	if (_user == 1)
	{
		oFile.open("MitchNonEssentials.txt");
	}
	else if (_user == 2)
	{
		oFile.open("MomNonEssentials.txt");
	}								//oFile.open("NonEssentials.txt");
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