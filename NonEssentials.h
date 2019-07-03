#include "category.h"

class NonEssentials
{
private:
	double _totalSpent;

public:
	std::unordered_map<string, Category> _nCategories;
	void buildNonEssentials(string user);
	void storeNonEssentials(string user);
	void fullReport();
	void monthReport(int desiredMonth);
	void fullBreakdown();
	void fullBreakdown(int totalSpent);
	void monthBreakdown(int desiredMonth);
	void monthBreakdown(int desiredMonth, double allMonthTotal);
	double calcMonthSpent(int desiredMonth);
	void setTotalSpent();
	double getTotalSpent();

};