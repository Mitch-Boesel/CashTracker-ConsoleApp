#include "NonEssentials.h"

void NonEssentials::buildNonEssentials(string user)	// NonEssentials constructor, building from previous data in files
{
	std::ifstream eFile;		//opening the NonEssentials file
	if (user == "Mitch")
	{
		eFile.open("MitchNonEssentials.txt");
	}
	else if (user == "Mom")
	{
		eFile.open("MomNonEssentials.txt");
	}

	this->_totalSpent = 0.0;
	string description = "", date = "", category = "", sMoney = "", nItems = "";	//declaring a bunch of variables I'll need
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
				getline(eFile, description, ',');	//parsing the line
				getline(eFile, date, ',');
				getline(eFile, sMoney);
				money = std::stod(sMoney);	//converting spentMoney to a double
				Purchase* newPurchase = new Purchase(description, money, date);	//creating the new purchase object
				newCategory->addPurchase(*newPurchase);	//adding the purchase to the category vector
				this->_totalSpent += money;
			}
			// by now the all the purchases for that category will be added to the Category object
			this->_nCategories.insert(std::make_pair(newCategory->getCatName(), *newCategory));	//adding the category to the NonEssentials hash table (_groups)
		}
	}
	eFile.close();	// closing the file
}

void NonEssentials::storeNonEssentials(string user)
{
	std::ofstream oFile;		//creating the file to write to when application closes
	if (user == "Mitch")
	{
		oFile.open("MitchNonEssentials.txt");
	}
	else if (user == "Mom")
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

void NonEssentials::monthReport(int desiredMonth)
{
	cout << "NonEssentials Report: " << endl;

	string date = "";
	string month = "";
	char delim = '/';
	int purchMonth = 0;
	int i = 0;	// counter for formatting

	auto it = this->_nCategories.begin();
	for (; it != this->_nCategories.end(); it++)	// it is pointing to a category vector
	{
		i = 0;
		cout << endl << it->second.getCatName() << ":";

		auto it2 = it->second.getPurchVector().begin();		// it2 is pointing to a purchase
		for (; it2 != it->second.getPurchVector().end(); it2++)
		{
			date = it2->getDatePurchased();
			if (date.front() == '0')	// if the date starts with a 0, take the 0 off
			{
				date.erase(date.begin());	// taking the 0 off
			}

			month = date.substr(0, date.find(delim));
			purchMonth = stoi(month);

			if (purchMonth == desiredMonth)	// if the purchase happened in the right month, print it 
			{
				cout << endl;
				cout << endl << "	Business: " << it2->getDescription();
				cout << endl << "	Date: " << it2->getDatePurchased();
				cout << endl << "	Money Spent: " << it2->getMoneySpent() << endl;
				i++;
			}
		}
		if (i == 0)	// if no purchases in the category
		{
			cout << endl << "	No Purchases this Month!" << endl;
		}
	}
}

void NonEssentials::setTotalSpent()
{
	double rTotal = 0.0;	//Running total 
	auto it = this->_nCategories.begin();	// iterator for the NonEssentials hashTable
	for (; it != this->_nCategories.end(); it++)		// iterating through the hashTable
	{
		rTotal += it->second.getTotalSpent();	// adding each category's total to the running total
	}

	this->_totalSpent = rTotal;
}

double NonEssentials::getTotalSpent()
{
	return this->_totalSpent;
}

void NonEssentials::fullReport()
{
	cout << endl << "NONESSENTIALS PURCHASES:" << endl;
	cout << endl << "----------------------------------------------------------------------";
	auto itN = this->_nCategories.begin();	//itterator for the NonEssentials hashTable
	for (; itN != this->_nCategories.end(); itN++)		// Iterating through each category
	{
		itN->second.printFullReport();	// calling for each category to print their purchases
	}

	cout << endl << "----------------------------------------------------------------------" << endl;
}

void NonEssentials::fullBreakdown()
{
	double totalSpent = this->getTotalSpent();		// totalSpent = total money spent

	cout << std::setw(25) << std::left << "Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;
	auto it = this->_nCategories.begin();
	double percentage = 0.0;
	for (; it != this->_nCategories.end(); it++)
	{
		percentage = it->second.getTotalSpent() / totalSpent;
		percentage = std::round(percentage * 100);
		cout << std::setw(25) << std::left << it->second.getCatName() << std::setw(25) << std::left << "NonEssential" << "$" << std::setw(25) << std::left << it->second.getTotalSpent() << (int)percentage << "%" << endl;
	}

	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "NonEssentials" << "$" << std::setw(25) << std::left << totalSpent << "100%" << endl;
}

void NonEssentials::fullBreakdown(int totalSpent)
{
	auto it = this->_nCategories.begin();
	double percentage = 0.0;
	for (; it != this->_nCategories.end(); it++)
	{
		percentage = it->second.getTotalSpent() / totalSpent;
		percentage = std::round(percentage * 100);
		cout << std::setw(25) << std::left << it->second.getCatName() << std::setw(25) << std::left << "NonEssential" << "$" << std::setw(25) << std::left << it->second.getTotalSpent() << (int)percentage << "%" << endl;
	}
}

void NonEssentials::monthBreakdown(int desiredMonth)
{
	double totalSpent = this->calcMonthSpent(desiredMonth);
	double catMonthSpent = 0.0;
	double percentage = 0.0;

	cout << std::setw(25) << std::left << "Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;


	auto it = this->_nCategories.begin();
	for (; it != this->_nCategories.end(); it++)
	{
		catMonthSpent = it->second.calcMonthSpent(desiredMonth);
		if (catMonthSpent != 0.0)
		{
			percentage = catMonthSpent / totalSpent;
			percentage = std::round(percentage * 100);
			cout << std::setw(25) << std::left << it->second.getCatName() << std::setw(25) << std::left << "NonEssential" << "$" << std::setw(25) << std::left << catMonthSpent << (int)percentage << "%" << endl;

		}
	}

	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "NonEssentials" << "$" << std::setw(25) << std::left << totalSpent << "100%" << endl;
}

void NonEssentials::monthBreakdown(int desiredMonth, double allMonthTotal)
{
	double catMonthSpent = 0.0;
	double percentage = 0.0;

	auto it = this->_nCategories.begin();
	for (; it != this->_nCategories.end(); it++)
	{
		catMonthSpent = it->second.calcMonthSpent(desiredMonth);
		if (catMonthSpent != 0.0)
		{
			percentage = catMonthSpent / allMonthTotal;
			percentage = std::round(percentage * 100);
			cout << std::setw(25) << std::left << it->second.getCatName() << std::setw(25) << std::left << "NonEssential" << "$" << std::setw(25) << std::left << catMonthSpent << (int)percentage << "%" << endl;

		}
	}
}

double NonEssentials::calcMonthSpent(int desiredMonth)
{
	double monthTotal = 0.0;

	auto it = this->_nCategories.begin();
	for (; it != this->_nCategories.end(); it++)
	{
		monthTotal += it->second.calcMonthSpent(desiredMonth);
	}

	return monthTotal;

	return monthTotal;
}