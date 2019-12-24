#include "Essentials.h"
class CashTracker
{
private:
	Essentials _essentials;
	//NonEssentials _nonEssentials;

public:
	CashTracker();
	~CashTracker();
	void mainMenu();	//Main Function that runs and calls everything else
		void runReports();		// second menu option
			void yearlyReport();
			void yearlyCategoryReport();	// prints category report to the screen
			void categoryReportMonth();
			void monthPurchReport();		// Using fChoice to decide which of these 3 to call in smRunReports()
			void monthPurchReports();			// above
		void runBreakDowns();			// secondary menu for spending Breakdowns
				void yearlyBreakdown();
				void monthlyBreakDowns();	// will call correct monthly breakdown function based on use input
				void monthlyBreakDown();	// monthly breakdowns for each group of purchases
		void addNewPurchase();		//option for the second menu
				void addNewCategoryPurchase();	// helper functinon for smAddNewPurchase()
					
	
		// Helper Functions		

	bool printMonth(int monthNum);				// prints the desired month to the screen, used in formatting			
	int desiredYear();				// prompts user for their desired year
	int desiredMonth();				// prompts user for their desired month
};