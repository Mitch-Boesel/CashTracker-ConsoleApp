#include "Essentials.h"
#include "NonEssentials.h"

class CashTracker
{
private:
	Essentials _essentials;
	NonEssentials _nonEssentials;

public:
	CashTracker();
	~CashTracker();
	void mainMenu();	//Main Function that runs and calls everything else
		void mmEssentials(int fChoice);		// main menu option
		void mmNonEssentials(int fChoice);	// main menu option
		void mmAll(int fChoice);						// main menu option to view both types of purchases
			void smRunReports(int fChoice);		// second menu option
				void yearlyReportAll();				// prints reports to the screen, self explanitory
					void yearlyReportEssentials();
					void yearlyReportNonEssentials();
				void yearlyCategoryReport(int fChoice);	// prints category report to the screen
				void categoryReportMonth(int fChoice);
				void monthPurchReportEssentials();		// Using fChoice to decide which of these 3 to call in smRunReports()
				void monthPurchReportNonEssentials();	// above
				void monthPurchReportsAll();			// above
			void smRunBreakDowns(int fChoice);			// secondary menu for spending Breakdowns
				void yearlyBreakDowns(int fChoice);		// will call correct yearly breakdown function based on user input
					void yearlyBreakdownAll();			// uearly breakdowns for each group of purchases
					void yearlyBreakdownEssential();
					void yearlyBreakdownNonEssential();
				void monthlyBreakDowns(int fChoice);	// will call correct monthly breakdown function based on use input
					void monthlyBreakDownEssentials();	// monthly breakdowns for each group of purchases
					void monthlyBreakDownNonEsentials();
					void monthlyBreakDownAll();
			void smAddNewPurchase(int fChoice);		//option for the second menu
				void hAddExistingCategoryPurchase(int fChoice);	// helper function for smAddNewPurchase()
				void hAddNewCategoryPurchase(int fChoice);	// helper functinon for smAddNewPurchase()
					
	
		// Helper Functions		

	double yearlyTotalAll(int desiredYear);		// returns the total of both Essenial and NonEssential Purchases added together
	bool printMonth(int monthNum);				// prints the desired month to the screen, used in formatting			
	int desiredYear();				// prompts user for their desired year
	int desiredMonth();				// prompts user for their desired month
	void categoryHelp(int fChoice);	// helper function to print categories if user wants to see them
};