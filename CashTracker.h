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
		void mmEssentials(int fChoice);		// main menu option
		void mmNonEssentials(int fChoice);	// main menu option
		void mmAll(int fChoice);						// main menu option to view both types of purchases
			void smRunReports(int fChoice);		// second menu option
				void fullReportAll();				// prints reports to the screen, self explanitory
					void fullReportEssentials();
					void fullReportNonEssentials();
				void categoryReport(int fChoice);	// prints category report to the screen
				void categoryReportMonth(int fChoice);
					void hPrintCategories(int fChoice);	// helper function to print categories if user wants to see them
				void monthPurchReportEssentials();		// Using fChoice to decide which of these 3 to call in smRunReports()
				void monthPurchReportNonEssentials();	// above
				void monthPurchReportsAll();			// above
			void smRunBreakDowns(int fChoice);
				void spendingBreakDownTotals(int fChoice);
					void spendingBreakdownAll();
					void spendingBreakdownEssential();
					void spendingBreakdownNonEssential();
				void spendingBreakDownMonthly(int fChoice);		
					void spendingBreadownMonthlyEssentials();
					void spendingBreakdownMonthlyNonEsentials();
					void spendingBreakdownMonthlyAll();


			void smAddNewPurchase(int fChoice);		//option for the second menu
				void hAddExistingCategoryPurchase(int fChoice);	// helper function for smAddNewPurchase()
				void hAddNewCategoryPurchase(int fChoice);	// helper functinon for smAddNewPurchase()
					
	
		// Helper Functions		

	double fullTotal();					// returns the total of both Essenial and NonEssential Purchases added together
	bool printMonth(int monthNum);

};