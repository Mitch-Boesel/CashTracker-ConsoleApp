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

Category::Category(double nTotSpent, int nPurch, string nField)
{
	this->_totalSpent = nTotSpent;
	this->_catName = nField;
	this->_numPurchases = nPurch;

}
void Category::newPurchase()
{
	string loc = "";
	string date = "";
	double spent = 0.0;
	cout << "Business you bought from: ";
	getline(cin, loc);
	cout << "Date of the purchase: ";
	getline(cin, date);
		//getting the amount the user spent on the purchase, handles exceptions
	while (cout << "Amount of the purchase (No Dollar Sign): " && !(cin >> spent))
	{
		cout << "Enter a Valid Option; " << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	cout << endl;

	Purchase nPurchase = Purchase(loc, spent, date);
	_purchHistory.push_back(nPurchase);
	this->setTotalSpent(spent);
	this->_numPurchases++;

}

void Category::setTotalSpent(double addTo)
{
	this->_totalSpent += addTo;
}

void Category::printTotalSpent()
{
	cout << "Total money spent on " << _catName << " this month is : " << _totalSpent;
}
void Category::printFullReport()
{
	cout << endl << _catName << ":";
	for (std::vector<Purchase>::iterator it = _purchHistory.begin(); it != _purchHistory.end(); it++)
	{
		cout << endl;
		cout << endl << "	Business: " << it->getLocation();
		cout << endl << "	Date: " << it->getDatePurchased();
		cout << endl << "	Money Spent: " << it->getMoneySpent() << endl;
	}
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
	this->setTotalSpent(pAdd.getMoneySpent());
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
		file << endl << it->getLocation() << "," << it->getDatePurchased() << "," << it->getMoneySpent();
	}
}

std::vector<Purchase> & Category::getPurchVector()
{
	return this->_purchHistory;
}

/*Category & operator = ( Category &rhs)
{

}
*/