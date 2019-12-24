#include "Essentials.h"

void Essentials::buildEssentials()	// Essentials constructor, building from previous data stored in files
{

	std::ifstream eFile;		//opening the Essentials file

	eFile.open("MitchEssentials.txt");

	this->_totalSpent = 0.0;
	string description = "", date = "", category = "", spentMoney = "", nItems = "";		//declaring a bunch of variables I'll need
	double money = 0.0;		// will take the spentMoney string and convert to this money double
	int numItems = 0;		// convert nItems strings to this int
	string ess = "";

	if (eFile.peek() != (int)"")	// if the file isn't empty, parse it
	{
		while (eFile.eof() != true)	//parsing the file while I'm not at the end
		{
			numItems = 0;	// always resetting to 0
			money = 0.0;	//always resetting to 0
			ess = "";

			getline(eFile, category, ',');	//get the category name
			getline(eFile, ess, ',');
			Category* newCategory;
			if (ess == "true")
				newCategory = new Category(money, numItems, category, true);
			else
				newCategory = new Category(money, numItems, category, false);

			getline(eFile, nItems);	// getting the number of purchases for the category
			numItems = stoi(nItems); // converting the number of purchases to an int

			for (int i = 0; i < numItems; i++)	//parsing and saving all the parsed purchases
			{
				getline(eFile, description, ',');	//parsing the line
				getline(eFile, date, ',');
				getline(eFile, spentMoney);
				money = std::stod(spentMoney);	//converting spentMoney to a double
				Purchase* newPurchase = new Purchase(description, money, date);	//creating the new purchase object
				newCategory->addPurchase(*newPurchase);	//adding the purchase to the category vector
				this->_totalSpent += money;
			}
			// by now the all the purchases for that category will be added to the Category object
			//this->_eCategories.insert(std::make_pair(newCategory->getCatName(), *newCategory));	//adding the category to the Essentials hash table (_groups)
			this->_eCategories.push_back(*newCategory);
		}
	}
	eFile.close();	// closing the file
}

void Essentials::storeEssentials()
{
	std::ofstream oFile;		

	oFile.open("MitchEssentials.txt");

	oFile.clear();	// emptying the file

	int counter = 0;	// counter used for formatting
	std::vector<Category>::iterator it = this->_eCategories.begin();	//iterator for the Essentials hashTable
	for (; it != this->_eCategories.end(); it++)	// prinings the contents of the essentials hashTable to the Essentials.txt file
	{
		if (counter != 0)	// adding a space between every category
			oFile << endl;

		oFile << it->getCatName() << "," << it->getIsEssential() << "," <<it->getNumPurchases();	// writing the category and number of purchases 
		it->printPurchasesToFile(oFile);	// writing the purchases to the file
		counter++;	// in
	}
	oFile.close();
}

void Essentials::monthReport(int desiredMonth)
{
	cout << "Essentials Report: " << endl;

	string date = "";
	string month = "0";
	char delim = '/';
	int purchMonth = 0;
	int i = 0;	// counter for formatting

	auto it = this->_eCategories.begin();
	for (; it != this->_eCategories.end(); it++)	// it is pointing to a category vector
	{	
		i = 0;
		cout << endl << it->getCatName()<< ":";

		auto it2 = it->getPurchVector().begin();		// it2 is pointing to a purchase
		for (; it2 != it->getPurchVector().end(); it2++)
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

void Essentials::setTotalSpent()
{
	double rTotal = 0.00;	//Running total 
	auto it = this->_eCategories.begin();	// iterator for the Essentails hashTable
	for (; it != this->_eCategories.end(); it++)	// iterating through the hashTable
	{
		rTotal += it->getTotalSpent();	// adding each category's total to the running total
	}

	this->_totalSpent = rTotal;
}

double Essentials::getTotalSpent()
{
	return this->_totalSpent;
}

void Essentials::yearlyReport(int desiredYear)
{
	cout << "YEARLY PURCHASES:";
	cout << endl << "----------------------------------------------------------------------";
	auto itE = this->_eCategories.begin();	// Iterator for the Essentials hashTable
	for (; itE != this->_eCategories.end(); itE++)	//Iterating through each category
	{
		itE->printYearlyReport(desiredYear);	// calling for each category to print their purchases
	}
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void Essentials::yearlyBreakdown(int desiredYear)
{
	double totalSpent = this->calcYearSpent(desiredYear);		// totalSpent = total money spent

	cout << std::setw(25) << std::left << "Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;
	auto it = this->_eCategories.begin();
	double percentage = 0.0;
	for (; it != this->_eCategories.end(); it++)	// itertator for essentials hashTable
	{
		percentage = it->calcYearSpent(desiredYear) / totalSpent;
		percentage = std::round(percentage * 100);
		cout << std::setw(25) << std::left << it->getCatName() << std::setw(25) << std::left << it->getIsEssential() << "$" << std::setw(25) << std::left << it->getTotalSpent() << (int)percentage << "%" << endl;
	}
	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << it->getIsEssential() << "$" << std::setw(25) << std::left << totalSpent << "100%" << endl;
}

void Essentials::yearlyBreakdown(int desiredYear, int totalSpent)
{
	auto it = this->_eCategories.begin();
	double percentage = 0.0;

	for (; it != this->_eCategories.end(); it++)	// itertator for essentials hashTable
	{
		percentage = it->calcYearSpent(desiredYear) / totalSpent;
		percentage = std::round(percentage * 100);
		cout << std::setw(25) << std::left << it->getCatName() << std::setw(25) << std::left << it->getIsEssential() << "$" << std::setw(25) << std::left << it->getTotalSpent() << (int)percentage << "%" << endl;
	}
}

void Essentials::monthBreakdown(int desiredMonth)
{
	double totalSpent = this->calcMonthSpent(desiredMonth);
	double catMonthSpent = 0.0;
	double percentage = 0.0;

	cout << std::setw(25) << std::left << "Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;


	auto it = this->_eCategories.begin();
	for (; it != this->_eCategories.end(); it++)
	{
		catMonthSpent = it->calcMonthSpent(desiredMonth);
		if ( catMonthSpent != 0.0)
		{
			percentage = catMonthSpent / totalSpent;
			percentage = std::round(percentage * 100);
			cout << std::setw(25) << std::left << it->getCatName() << std::setw(25) << std::left << it->getIsEssential() << "$" << std::setw(25) << std::left << catMonthSpent << (int)percentage << "%" << endl;

		}
	}

	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "Essentials" << "$" << std::setw(25) << std::left << totalSpent << "100%" << endl;
}

void Essentials::monthBreakdown(int desiredMonth, double allMonthTotal)
{
	double catMonthSpent = 0.0;
	double percentage = 0.0;

	auto it = this->_eCategories.begin();
	for (; it != this->_eCategories.end(); it++)
	{
		catMonthSpent = it->calcMonthSpent(desiredMonth);
		if (catMonthSpent != 0.0)
		{
			percentage = catMonthSpent / allMonthTotal;
			percentage = std::round(percentage * 100);
			cout << std::setw(25) << std::left << it->getCatName() << std::setw(25) << std::left << it->getIsEssential() << "$" << std::setw(25) << std::left << catMonthSpent << (int)percentage << "%" << endl;

		}
	}
}
double Essentials::calcMonthSpent(int desiredMonth)
{
	double monthTotal = 0.0;

	auto it = this->_eCategories.begin();
	for (; it != this->_eCategories.end(); it++)
	{
		monthTotal += it->calcMonthSpent(desiredMonth);
	}

	return monthTotal;
}

double Essentials::calcYearSpent(int desiredYear)
{
	double yearTotal = 0.0;

	for (auto it : this->_eCategories)
	{
		yearTotal += it.calcYearSpent(desiredYear);
	}

	return yearTotal;
}