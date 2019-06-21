#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>    
#include <fstream>
#pragma once

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Purchase
{
private:
	string _location;
	double _moneySpent;
	string _datePurchased;

public:

	Purchase();
	Purchase(string nLocation, double nMoneySpent, string nDate);
	string getLocation();
	double getMoneySpent();
	string getDatePurchased();
};