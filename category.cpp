#include "category.h"

Category::Category()
{
	this->_numPurchases = 0;
	this->_totalSpent = 0.0;	
	this->_catName = "";
}

Category::Category(string nField)
{
	this->_numPurchases = 0;
	this->_totalSpent = 0.0;
	this->_catName = nField;
}

Category::Category(int nTotSpent, int nPurch, string nField)
{
	this->_totalSpent = nTotSpent;
	this->_catName = nField;
	this->_numPurchases = nPurch;

}
void Category::newPurchase()
{
	char loc[50] = "";
	string date = "";
	double spent = 0.0;
	cout << endl << "Enter the location of the purchase: ";
	cin.getline(loc, sizeof(loc));
	cout << endl << "Enter the date of the purchase: ";
	cin >> date;
	cout << "Enter the amount of the purchase: ";
	cin >> spent;

	Purchase nPurchase = Purchase(loc, spent, date);
	_purchHistory.push_back(nPurchase);
	setTotalSpent(spent);
	this->_numPurchases++;

}

void Category::setTotalSpent(double addTo)
{
	_totalSpent += addTo;
}

void Category::printTotalSpent()
{
	cout << "Total money spent on " << _catName << " this month is : " << _totalSpent;
}
void Category::printFullReport()
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << _catName;
	for (std::vector<Purchase>::iterator it = _purchHistory.begin(); it != _purchHistory.end(); it++)
	{
		cout << endl;
		cout << endl << "	Location: " << it->getLocation();
		cout << endl << "	Date: " << it->getDatePurchased();
		cout << endl << "	Money Spent: " << it->getMoneySpent() << endl;
	}
	cout << endl << "----------------------------------------------------------------------";
}

/*void Category::printPurchaseLocation()	//probably wont use
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << _field;
	for (std::vector<Purchase>::iterator it = _history.begin(); it != _history.end(); it++)
	{
		cout << endl;
		cout << endl << "	Location: " << it->getLocation();
		cout << endl << "	Date: " << it->getDatePurchased();
	}
	cout << endl << "----------------------------------------------------------------------";
}*/

/*void Category::printSinglePurchase()	// probably wont use
{
	string store = "";
	cout << "What purchase do you wish to view?: " << endl;
	cin >> store;
}*/

void Category::addPurchase(Purchase pAdd)
{
	this->_purchHistory.push_back(pAdd);
	this->_numPurchases++;
}

int Category::getNumPurchases()
{
	return this->_numPurchases;
}
double Category::getTotalSpent()
{
	return this->_totalSpent;
}
string Category::getCatName()
{
	return this->_catName;
}

void Category::printPurchasesToFile(std::ofstream& file)
{
	std::vector<Purchase>::iterator it = this->_purchHistory.begin();

	for (; it != this->_purchHistory.end(); it++)
	{
		file << it->getLocation() << "," << it->getDatePurchased() << "," << it->getMoneySpent() << endl;
	}
}

