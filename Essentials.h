#include "category.h"

class Essentials
{
private:
	double _totalSpent;

public:
	std::unordered_map<string, Category> _eCategories;

	void buildEssentials(string user);	// more or less the Constructor
	void storeEssentials(string user);	// more or less the destructor
	void fullReport();					// prints all purchases to the screen
	void monthReport(int desiredMonth);	// prints a months of purchases to the screen
	void fullBreakdown();				// used when doing a strictly essentials breakdown
	void fullBreakdown(int totalSpent);	// used when doing an All breakdown
	void monthBreakdown(int desiredMonth);	// breakdown for a month
	void monthBreakdown(int desiredMonth, double allMonthTotal);
	void setTotalSpent();				// setter for _totalSpent
	double getTotalSpent();				// getter for _totalSpent
	double calcMonthSpent(int desiredMonth);	// gets the amount spent in a certain month
};