#include "Essentials.h"
#include "NonEssentials.h"

class CashTracker
{
private:
	Essentials _essentials;
	NonEssentials _nonEssentials;
	string _user;

public:
	CashTracker();
	~CashTracker();
	void mainMenu();	//Main Function that runs and calls everything else
	void hAddExistingCategoryPurchase(int fChoice);	// helper function for smAddNewPurchase()
	void hAddNewCategoryPurchase(int fChoice);	// helper functinon for smAddNewPurchase()
	void smAddNewPurchase(int fChoice);		//option for the second menu
	void printFullReport();				// prints reports to the screen, self explanitory
	void printEssentials();
	void printNonEssentials();
	void printSingleCategory(int fChoice);	// prints category report to the screen
	int essestialOrNonEssential();		// prompts user to determine the type of purchase, not used in this version
	void findCategoryTotal(int fChoice);	// calls the next two functions based on parameter
	void hPrintEssentialTotal();		// helper function to print essential total spent
	void hPrintNonEssentialTotal();		// helper function to print nonessential total spent
	void hPrintCategories(int fChoice);	// helper function to print categories
	double essentialTotal();			// returns the total of all the Essential Purchases
	double nonEssentialTotal();			// returns the total of all the NonEssential Purchases
	double fullTotal();					// returns the total of both Essenial and NonEssential Purchases added together
	void smRunReports(int fChoice);		// second menu option
	void smRunSpendingTotals(int fChoice);	// second menu option
	void mmEssentials(int fChoice);		// main menu option
	void mmNonEssentials(int fChoice);	// main menu option
	void mmAll();						// main menu option to view both types of purchases
	void amSpendingBreakDown();			// all menu option, prints breakdown of purchases to the screen
	void eSpendingBreakDown();
	void neSpendingBreakDown();
	void monthPurchReportEssentials();
	void monthPurchReportNonEssentials();
};