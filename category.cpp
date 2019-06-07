#include "category.h"

Category::Category()
{
	this->_key = 0;
	this->_totalSpent = 0.0;
	this->_field = "";
}

Category::Category(string nField)
{
	this->_key = 0;
	this->_totalSpent = 0.0;
	this->_field = nField;
	this->_numPurchases = 0;
}

Category::Category(int nKey, int nTotSpent, int nPurch, string nField)
{
	this->_key = nKey;
	this->_totalSpent = nTotSpent;
	this->_field = nField;
	this->_numPurchases = nPurch;

}
void Category::newPurchase()
{
	string loc = "";
	string date = "";
	double spent = 0.0;
	cout << endl << "Enter the location of the purchase: ";
	cin >> loc;
	cout << endl << "Enter the date of the purchase: ";
	cin >> date;
	cout << "Enter the amount of the purchase: ";
	cin >> spent;

	Purchase nPurchase = Purchase(loc, spent, date);
	_history.push_back(nPurchase);
	setTotalSpent(spent);
	this->_numPurchases++;

}

void Category::setTotalSpent(double addTo)
{
	_totalSpent += addTo;
}

void Category::printTotalSpent()
{
	cout << "Total money spent on " << _field << " this month is : " << _totalSpent;
}
void Category::printFullReport()
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << _field;
	for (std::vector<Purchase>::iterator it = _history.begin(); it != _history.end(); it++)
	{
		cout << endl;
		cout << endl << "	Location: " << it->getLocation();
		cout << endl << "	Date: " << it->getDatePurchased();
		cout << endl << "	Money Spent: " << it->getMoneySpent();
	}
	cout << endl << "----------------------------------------------------------------------";
}

void Category::printPurchaseLocation()	//probably wont use
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
}

void Category::printSinglePurchase()	// probably wont use
{
	string store = "";
	cout << "What purchase do you wish to view?: " << endl;
	cin >> store;
}

void Category::addPurchase(Purchase pAdd)
{
	this->_history.push_back(pAdd);
	this->_numPurchases++;
}

int Category::getKey()
{
	return this->_key;
}

int Category::getNumPurchases()
{
	return this->_numPurchases;
}
double Category::getTotalSpent()
{
	return this->_totalSpent;
}
string Category::getField()
{
	return this->_field;
}

void Category::printPurchasesToFile(std::ofstream& file)
{
	std::vector<Purchase>::iterator it = this->_history.begin();

	for (; it != this->_history.end(); it++)
	{
		file << it->getLocation << "," << it->getDatePurchased << "," << it->getMoneySpent << endl;
	}
}

void Category::setKey(int nKey)
{
	this->_key = nKey;
}