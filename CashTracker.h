#include "Essentials.h"
#include "NonEssentials.h"

class CashTracker
{
private:
	Essentials _essentials;
	NonEssentials _nonEssentials;

public:
	void mainMenu();
	void addNewExistingCategoryPurchase(int choice);
	void addNewCategoryPurchase(int choice);
	void addNewPurchase();
	void printFullReport();
	void printEssentials();
	void printNonEssentials();
	void printSingleCategory();
	int essestialOrNonEssential();	
};