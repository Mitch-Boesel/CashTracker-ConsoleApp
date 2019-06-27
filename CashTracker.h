#include "Essentials.h"
#include "NonEssentials.h"

class CashTracker
{
private:
	Essentials _essentials;
	NonEssentials _nonEssentials;

public:
	void mainMenu();	//Main Function that runs and calls everything else
	void hAddExistingCategoryPurchase(int fChoice);	// helper function for smAddNewPurchase()
	void hAddNewCategoryPurchase(int fChoice);	// helper functinon for smAddNewPurchase()
	void smAddNewPurchase(int fChoice);		//option for the second menu
	void printFullReport();				// prints reports to the screen, self explanitory
	void printEssentials();
	void printNonEssentials();
	void printSingleCategory(int fChoice);	// prints category report to the screen
	int essestialOrNonEssential();		// prompts user to determine the type of purchase, not used in this version
	void findCategoryTotal(int EorN);	// calls the next two functions based on parameter
	void hPrintEssentialTotal();		// helper function to print essential total spent
	void hPrintNonEssentialTotal();		// helper function to print nonessential total spent
	void smRunReports(int fChoice);		// second menu option
	void smRunSpendingTotals(int fChoice);	// second menu option
	void mmEssentials(int fChoice);		// main menu option
	void mmNonEssentials(int fChoice);	// main menu option
};