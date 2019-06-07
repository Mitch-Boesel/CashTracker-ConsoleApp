#include "purchase.h"

class Category
{
private:
	std::vector<Purchase> _history; // the vector of purchases for the field/category
//	int _key;	//key for the hash table I'll implement;
	int _numPurchases;
	double _totalSpent;	//total of all the purchases
	string _field;

public:
	Category();
	Category(int nKey, int nTotSpent, int nPurch, string nField);
	Category(string nField);
	void newPurchase();	//getting user input to add a new purchase to the _history vector
	void setTotalSpent(double addTo);	//called by newPurchase(), adds new purchase value to existing totalValue
	void setKey(int nKey);
	void printTotalSpent();	//prints total spent on the field for the month
	void printFullReport();	// prints all the purchases in the vector
	void printSinglePurchase();		// probably wont use
	void printPurchaseLocation();	// probably wont use, prints all the purchase locations
	void addPurchase(Purchase pAdd);	// adds a passed in purchase to the _history vector, used in Essential/NonEssential Vector
	int getKey();			//getters
	int getNumPurchases();
	double getTotalSpent();
	string getField();
	void printPurchasesToFile(std::ofstream& file);	// writes entire vector of purchases to the file passed in
};