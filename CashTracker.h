#include "Essentials.h"
class CashTracker
{
private:
	Essentials _essentials;	// 

public:
	CashTracker();
	~CashTracker();
	void mainMenu();	//Main Function that runs and calls everything else
		void runReports();		// Called by mainMenu(), promts the user to choose type of report. Calls the appropriate indented function 
			void yearlyReport();
			void yearlyCategoryReport();
			void categoryReportMonth();
			void monthPurchReport();
		void runBreakDowns();			// Called by mainMenu(), promts the user to choose the type of breakdown. Calls the appropriate indented funciton
				void yearlyBreakdown();
				void monthlyBreakDown();
		void addNewPurchase();		//Called by mainMenu(), calls the indented function to handle the new purchase. May call indented function based on user input
				void addNewCategoryPurchase();
	// Helper Functions		
	bool printMonth(int monthNum);	// prints the desired month to the screen, used in formatting			
	int desiredYear();				// prompts user for their desired year
	int desiredMonth();				// prompts user for their desired month
};