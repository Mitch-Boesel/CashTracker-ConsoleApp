#include "purchase.h"
#pragma once

class Category
{
private:
	std::vector<Purchase> _purchHistory; // the vector of purchases for the field/category
	int _numPurchases;
	double _totalSpent;	//total of all the purchases
	string _catName;	// will act as the category name and the hash key
	bool isEssential;

public:
	Category();
	Category(double nTotSpent, int nPurch, string ncatName, bool nIsEssential);
	Category(string ncatName, bool ess);
	void newPurchase();	//getting user input to add a new purchase to the _purchHistory vector
	void setTotalSpent(double addTo);	//called by newPurchase(), adds new purchase value to existing totalValue
	void printTotalSpent();	//prints total spent on the category
	void printYearlyReport(int desiredYear);	// prints all the purchases in the vector
	void addPurchase(Purchase pAdd);	// adds a passed in purchase to the _history vector, used in Essential/NonEssential Vector
	void printMonth(int desiredMonth);

	double calcMonthSpent(int desiredMonth);
	double calcYearSpent(int desiredYear);

		//getters
	int getNumPurchases();
	double getTotalSpent();
	string getCatName();
	string getIsEssential();
	std::vector<Purchase> & getPurchVector();

	void printPurchasesToFile(std::ofstream& file);	// writes entire vector of purchases to the file passed in
};