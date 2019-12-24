#include "category.h"

class Essentials
{
private:
	double _totalSpent;	// going to be irrelevent since im changing everything to months and years

public:
	std::vector<Category> _eCategories;

	void buildEssentials();	// more or less the Constructor
	void storeEssentials();	// more or less the destructor
	void yearlyReport(int desiredYear);					// prints all purchases to the screen
	void monthReport(int desiredMonth);	// prints a months of purchases to the screen
	void yearlyBreakdown(int desiredYear);				// used when doing a strictly essentials breakdown
	void yearlyBreakdown(int desiredYear, int totalSpent);	// used when doing an All breakdown
	void monthBreakdown(int desiredMonth);	// breakdown for a month
	void monthBreakdown(int desiredMonth, double allMonthTotal);
	void setTotalSpent();				// setter for _totalSpent
	double getTotalSpent();				// getter for _totalSpent
	double calcMonthSpent(int desiredMonth);	// gets the amount spent in a certain month
	double calcYearSpent(int desiredYear);
};