#include "purchase.h"

Purchase::Purchase()	// basic constructor
{
	_description = "";
	_moneySpent = 0.0;
	_datePurchased = "";
}

Purchase::Purchase(string nDescription, double nMoneySpent, string nDate)	// copy constructor?
{
	_description = nDescription;
	_moneySpent = nMoneySpent;
	_datePurchased = nDate;
}

	// getters
string Purchase::getDescription()
{
	return this->_description;
}

double Purchase::getMoneySpent()
{
	return this->_moneySpent;
}

string Purchase::getDatePurchased()
{
	return this->_datePurchased;
}