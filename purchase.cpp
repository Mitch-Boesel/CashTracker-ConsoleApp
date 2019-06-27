#include "purchase.h"

Purchase::Purchase()	// basic constructor
{
	_location = "";
	_moneySpent = 0.0;
	_datePurchased = "";
}

Purchase::Purchase(string nLocation, double nMoneySpent, string nDate)	// copy constructor?
{
	_location = nLocation;
	_moneySpent = nMoneySpent;
	_datePurchased = nDate;
}

	// getters
string Purchase::getLocation()
{
	return this->_location;
}

double Purchase::getMoneySpent()
{
	return this->_moneySpent;
}

string Purchase::getDatePurchased()
{
	return this->_datePurchased;
}