#include "category.h"

Category::Category()
{
	this->_numPurchases = 0;
	this->_totalSpent = 0.0;	
	this->_catName = "";
}

Category::Category(string nField, bool ess)
{
	this->_numPurchases = 0;
	this->_totalSpent = 0.0;
	this->_catName = nField;
	this->isEssential = ess;
}

Category::Category(double nTotSpent, int nPurch, string nField, bool nIsEssential)
{
	this->_totalSpent = nTotSpent;
	this->_catName = nField;
	this->_numPurchases = nPurch;
	this->isEssential = nIsEssential;
}
void Category::newPurchase()
{
	string loc = "";
	string date = "";
	double spent = 0.0;
	cout << "Business/Description: ";
	cin.ignore();
	getline(cin, loc);
	cout << "Date of the purchase (mm/dd/yy): ";
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
void Category::printYearlyReport(int desiredYear)
{
	cout << endl << _catName << ":";
	char delim = '/';
	string date = "";
	int purchYear = 0;

	for (std::vector<Purchase>::iterator it = _purchHistory.begin(); it != _purchHistory.end(); it++)
	{
		date = it->getDatePurchased();

		date = date.substr(date.find(delim), date.back());	// getting the year out of the date
		date.erase(date.begin());
		date = date.substr(date.find(delim), date.back());
		date.erase(date.begin());
		
		purchYear = stoi(date);

		if (purchYear == desiredYear)
		{
			cout << endl;
			cout << endl << "	Business/Description: " << it->getDescription();
			cout << endl << "	Date: " << it->getDatePurchased();
			cout << endl << "	Money Spent: " << it->getMoneySpent() << endl;
		}

	}
}

string Category::getIsEssential()
{
	return this->isEssential == true ? "Essential" : "NonEssential";
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
		file << endl << it->getDescription() << "," << it->getDatePurchased() << "," << it->getMoneySpent();
	}
}

std::vector<Purchase> & Category::getPurchVector()
{
	return this->_purchHistory;
}

double Category::calcMonthSpent(int desiredMonth)
{
	double monthTotal = 0.0;
	string date = "";
	char delim = '/';
	string month = "0";
	int purchMonth = 0;

	auto it = this->_purchHistory.begin();
	for (; it != this->_purchHistory.end(); it++)
	{
		date = it->getDatePurchased();

		if (date.front() == '0')	// if the date starts with a 0, take the 0 off
		{
			date.erase(date.begin());	// taking the 0 off
		}

		month = date.substr(0, date.find(delim));
		purchMonth = stoi(month);

		if (purchMonth == desiredMonth)	// if the purchase happened in the right month, print it 
		{
			monthTotal += it->getMoneySpent();
		}
	}

	return monthTotal;
}

void Category::printMonth(int desiredMonth)
{
	string date = "";
	string month = "0";
	char delim = '/';
	int purchMonth = 0;
	int i = 0;

	cout << endl << this->getCatName() << ": ";

	auto it = this->_purchHistory.begin();
	for (; it != this->_purchHistory.end(); it++)
	{
		date = it->getDatePurchased();
		if (date.front() == '0')	// if the date starts with a 0, take the 0 off
		{
			date.erase(date.begin());	// taking the 0 off
		}

		month = date.substr(0, date.find(delim));
		purchMonth = stoi(month);

		if (purchMonth == desiredMonth)	// if the purchase happened in the right month, print it 
		{
			cout << endl;
			cout << endl << "	Business: " << it->getDescription();
			cout << endl << "	Date: " << it->getDatePurchased();
			cout << endl << "	Money Spent: " << it->getMoneySpent() << endl;
			i++;
		}
	}
	
	if (i == 0)
	{
		cout <<		"No Purchases this Month!" << endl;
	}
}

double Category::calcYearSpent(int desiredYear)
{
	double yearTotal = 0.0;
	string date = "";
	char delim = '/';
	int purchYear = 0;

	auto it = this->_purchHistory.begin();
	for (; it != this->_purchHistory.end(); it++)
	{
		date = it->getDatePurchased();

		date = date.substr(date.find(delim), date.back());	// getting the year out of the date
		date.erase(date.begin());
		date = date.substr(date.find(delim), date.back());
		date.erase(date.begin());	// date should be the year (yy)

		purchYear = stoi(date);

		if (purchYear == desiredYear)	// if the purchase happened in the right month, print it 
		{
			yearTotal += it->getMoneySpent();
		}
	}

	return yearTotal;


}