#include "purchase.h"
#pragma once

class Category
{
private:
	std::vector<Purchase> _purchHistory; // the vector of purchases for the field/category
	int _numPurchases;
	double _totalSpent;	//total of all the purchases
	string _catName;	// will double as the category name and the hash key

public:
	Category();
	Category(double nTotSpent, int nPurch, string ncatName);
	Category(string ncatName);
	void newPurchase();	//getting user input to add a new purchase to the _purchHistory vector
	void setTotalSpent(double addTo);	//called by newPurchase(), adds new purchase value to existing totalValue
	void printTotalSpent();	//prints total spent on the category
	void printFullReport();	// prints all the purchases in the vector
	void printSinglePurchase();		// probably wont use
	void printPurchaseLocation();	// probably wont use, prints all the purchase locations
	void addPurchase(Purchase pAdd);	// adds a passed in purchase to the _history vector, used in Essential/NonEssential Vector
		//getters
	int getNumPurchases();
	double getTotalSpent();
	string getCatName();
	void printPurchasesToFile(std::ofstream& file);	// writes entire vector of purchases to the file passed in
};

//Category & operator = (Category &rhs);