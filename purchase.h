#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>    
#include <fstream>
#include <iomanip>
#include <limits>
#include <time.h>
#pragma once

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Purchase
{
private:
	string _description;
	double _moneySpent;
	string _datePurchased;

public:

	Purchase();
	Purchase(string ndescription, double nMoneySpent, string nDate);
	string getDescription();
	double getMoneySpent();
	string getDatePurchased();
};