#include "category.h"

class NonEssentials
{
private:
	double _totalSpent;

public:
	std::unordered_map<string, Category> _nCategories;
	void buildNonEssentials();
	void storeNonEssentials();
	void yearlyReport(int desiredYear);
	void monthReport(int desiredMonth);
	void yearlyBreakdown(int desiredYear);
	void yearlyBreakdown(int desiredYear, int totalSpent);
	void monthBreakdown(int desiredMonth);
	void monthBreakdown(int desiredMonth, double allMonthTotal);

	double calcMonthSpent(int desiredMonth);
	double calcYearSpent(int desiredYear);
	void setTotalSpent();
	double getTotalSpent();

};