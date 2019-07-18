#include "CashTracker.h"

CashTracker::CashTracker()
{
	cout << std::setprecision(2) << std::fixed;

	this->_essentials.buildEssentials();
	this->_nonEssentials.buildNonEssentials();
	cout << endl;
}

CashTracker::~CashTracker()
{
	this->_essentials.storeEssentials();
	this->_nonEssentials.storeNonEssentials();
}

void CashTracker::mainMenu()
{
	cout << "Welcome to CASH TRACKER" << endl;
	int fChoice = 0;	//first choice, will be used for the main while loop. 1 for Essential or 2 for NonEssential 
	
	while (fChoice != 4)	// Main Menu Screen that will loop until the user chooses to exit
	{
			//Displays the main menu, handles invalid inputs
		while (cout << endl << "Main Menu:" << endl << "(1) Essentials" << endl << "(2) NonEssentials" << endl << "(3) All Purchases" << endl << "(4) Exit" << endl && !(cin >> fChoice) || fChoice != 1 && fChoice != 2 && fChoice != 3 && fChoice != 4)
		{
			cout << "Enter a Valid Option; " << endl << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
	switch(fChoice)	//Essentials
		{
		case 1:
			this->mmEssentials(fChoice);	// Takes you to Essentails secondary menu
			break;
		case 2:
			this->mmNonEssentials(fChoice);	// Takes you to NonEssentials secondary menu
			break;
		case 3:
			this->mmAll(fChoice);
			break;
		case 4:
			break;	// Exit
		}
	}
}

void CashTracker::smAddNewPurchase(int fChoice)		// secondary menu function, will call the appropriate functions for type of new purchase
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int nOrE = 0;	//new or existing

	if (fChoice == 1 && this->_essentials._eCategories.empty() == true)	// checking to see if its the first essential purchase
	{
		this->hAddNewCategoryPurchase(fChoice);
	}
	else if (fChoice == 2 && this->_nonEssentials._nCategories.empty() == true)	// checking to see if its the first nonEssential purchase
	{
		this->hAddNewCategoryPurchase(fChoice);
	}
	else		// Not the first purchase of either
	{
			// determining if the new purchase will be in an existing or a new category, handles invalid input
		while (cout << "(1) Existing Category		(2) New Category		(3) Back: " && !(cin >> nOrE) || nOrE != 1 && nOrE != 2 && nOrE != 3)
		{
			
			cout << "Enter a Valid Option;" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	if (nOrE == 1)	// New purchase on an existing category
	{
		this->hAddExistingCategoryPurchase(fChoice);
	}
	else if(nOrE == 2) // New purchase to a new category
	{
		this->hAddNewCategoryPurchase(fChoice);
	}
	else if (nOrE == 3)
	{
		return;
	}

}

void CashTracker::hAddExistingCategoryPurchase(int fChoice)		// Helper function to smAddNewPurchase()
{																// adds new purchase to an existing category
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int needsHelp = 0;	// used if exception is thrown for invalid user input
	string pCat = "";	// the category the user will enter

	if (fChoice == 1)	//essential purchase
	{
		while (needsHelp != 3)	// 3 is what needsHelp will be set to if user inputs corrent input
		{
			if (needsHelp == 1)	// printing out the existing categories if the user chooses
			{
				this->categoryHelp(fChoice);
			}
			try	// getting the category from the user then calling the category's newPurchase() function
			{
				cout << "Enter Category: ";
				cin.ignore();
				std::getline(std::cin, pCat);	// getting category from the user
				Category & chosenCat = this->_essentials._eCategories.at(pCat);
				chosenCat.newPurchase();
				this->_essentials.setTotalSpent();
				needsHelp = 3;	// settings needsHelp to 3 which means the user inpute was valid 
			}
			catch (const std::out_of_range)		// exception handling if the user enteres a nonexistant category
			{
						// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

		}
	}

	else if(fChoice == 2)	// NonEssential
	{
		while (needsHelp != 3)	// 3 is what needsHelp will be set to if user inputs corrent input
		{
			if (needsHelp == 1)	// printing out the existing categories if the user chooses
			{
				this->categoryHelp(fChoice);
			}
			try	// getting the category from the user then calling the category's newPurchase() function
			{
				cout << "Enter Category: ";
				cin.ignore();
				std::getline(std::cin, pCat);	// getting category from the user
				Category & chosenCat = this->_nonEssentials._nCategories.at(pCat);
				chosenCat.newPurchase();
				this->_essentials.setTotalSpent();
				needsHelp = 3;	// settings needsHelp to 3 which means the user inpute was valid 
			}
			catch (const std::out_of_range)		// exception handling if the user enteres a nonexistant category
			{
				// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

		}
	}
}

void CashTracker::hAddNewCategoryPurchase(int choice)
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	if (choice == 1)	// Essential
	{
		string name = "";
		cout << "Enter the Name of the New Category: ";
		cin.ignore();
		std::getline(std::cin, name);	// getting the name of the new category
		Category* nCat = new Category(name);	// Creating the new Category
		nCat->newPurchase();	// Prompting the user for the new purchase data to be added to the category

		_essentials._eCategories.insert(std::make_pair(nCat->getCatName(), *nCat));	// Adding the new category to the Essentials hashTable
		this->_essentials.setTotalSpent();
	}

	else if(choice == 2)	// NonEssential
	{
		string name = "";
		cout << "Enter the Name of the New Category: ";
		cin.ignore();
		std::getline(cin, name);	//getting the name of the new category
		Category* nCat = new Category(name);	// creating the new category
		nCat->newPurchase();	// Prompting the user for the new purchase data to be added to the category

		_nonEssentials._nCategories.insert(std::make_pair(nCat->getCatName(), *nCat)); // Adding the new category to the NonEssentials hashTable
		this->_nonEssentials.setTotalSpent();
	}
}

void CashTracker::yearlyReportAll()	// prints all purchases to the screen 
{
	int desiredYear = this->desiredYear();

	cout << endl << "ALL PURCHASES FROM 20" << desiredYear << "-" << endl;
	cout << "-------------------------------------" << endl;
	this->_essentials.yearlyReport(desiredYear);
	this->_nonEssentials.yearlyReport(desiredYear);
}

void CashTracker::yearlyReportEssentials()	// Prints all Essential Purchases to the screen
{
	int desiredYear = this->desiredYear();
	cout << endl << "20" << desiredYear << "- ";

	this->_essentials.yearlyReport(desiredYear);
}
void CashTracker::yearlyReportNonEssentials() // Prints all NonEssential Purchases to the screen
{
	int desiredYear = this->desiredYear();
	cout << endl << "20" << desiredYear << "- ";

	this->_nonEssentials.yearlyReport(desiredYear);
}
void CashTracker::yearlyCategoryReport(int fChoice)
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int needsHelp = 0;		// used for handling a possible exception
	string choice = "";		// category the user will choose
	int desiredYear = this->desiredYear();

	if (fChoice == 1)
	{
		while (needsHelp != 3)
		{
			if (needsHelp == 1)
			{
				this->categoryHelp(fChoice);
			}
			try
			{
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(std::cin, choice);

				Category cat = this->_essentials._eCategories.at(choice);	// finding the chosen category
				cout << endl << "----------------------------------------------------------------------";
				cat.printYearlyReport(desiredYear);	//calling for the category to print its purchase report
				cout << endl << "----------------------------------------------------------------------" << endl << endl;
				needsHelp = 3;
			}
			catch (const std::out_of_range)	// user entered a nonexistant category
			{
				// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}


	else if (fChoice == 2)
	{
		while (needsHelp != 3)
		{
			if (needsHelp == 1)
			{
				this->categoryHelp(fChoice);
			}
			try
			{
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(std::cin, choice);

				Category cat = this->_nonEssentials._nCategories.at(choice);	// finding the chosen category
				cout << endl << "----------------------------------------------------------------------";
				cat.printYearlyReport(desiredYear);	//calling for the category to print its purchase report
				cout << endl << "----------------------------------------------------------------------" << endl << endl;
				needsHelp = 3;
			}
			catch (const std::out_of_range)	// user entered a nonexistant category
			{
					// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}
}

void CashTracker::categoryReportMonth(int fChoice)
{
	int needsHelp = 0;		// used for handling a possible exception
	string choice = "";		// category the user will choose

	int monthNum = this->desiredMonth();

	if (fChoice == 1)
	{
		while (needsHelp != 3)
		{
			if (needsHelp == 1)
			{
				this->categoryHelp(fChoice);
			}
			try
			{
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(std::cin, choice);

				Category cat = this->_essentials._eCategories.at(choice);	// finding the chosen category
				cout << endl << "----------------------------------------------------------------------" << endl;
				if (this->printMonth(monthNum))
				{
					cat.printMonth(monthNum);	//calling for the category to print its purchase report
				}				
				cout << endl << "----------------------------------------------------------------------" << endl << endl;
				needsHelp = 3;
			}
			catch (const std::out_of_range)	// user entered a nonexistant category
			{
				// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}


	else if (fChoice == 2)
	{
		while (needsHelp != 3)
		{
			if (needsHelp == 1)
			{
				this->categoryHelp(fChoice);
			}
			try
			{
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(std::cin, choice);

				Category cat = this->_nonEssentials._nCategories.at(choice);	// finding the chosen category
				cout << endl << "----------------------------------------------------------------------"  << endl;
				if (this->printMonth(monthNum))
				{
					cat.printMonth(monthNum);	//calling for the category to print its purchase report
				}
				cout << endl << "----------------------------------------------------------------------" << endl << endl;
				needsHelp = 3;
			}
			catch (const std::out_of_range)	// user entered a nonexistant category
			{
				// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}
}

void CashTracker::smRunReports(int fChoice)	// second menu for Reports Option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1, 2 or 3, 1 for essential 2 for nonEssential 3 for all
	int choice = 0;	//will determine full or catergory report

	if (fChoice == 3)
	{
		while (cout << "Purchase Report Menu: " << endl << "(1) Yearly Report" << endl << "(2) Monthy Report" << endl << "(3) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Enter a Valid Option;" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (choice == 1)
		{
			this->yearlyReportAll();
		}
		else if (choice == 2)
		{
			this->monthPurchReportsAll();
		}
		return;
	}

			// getting the user input, handling invalid inputs
	while (cout << "Purchase Report Menu: " << endl << "(1) Yearly Report" << endl << "(2) Yearly Category Report" << endl << "(3) Monthy Report" << endl << "(4) Monthly Category Report" << endl << "(5) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3 && choice !=4 && choice != 5)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)	// full report
	{
		if (fChoice == 1)	// Essential
		{
			this->yearlyReportEssentials();
		}
		else if(fChoice == 2)	// NonEssential
		{
			this->yearlyReportNonEssentials();
		}
	}

	else if(choice == 2)	// category report
	{
		this->yearlyCategoryReport(fChoice);
	}
	else if (choice == 3)
	{
		if (fChoice == 1)
		{
			this->monthPurchReportEssentials();
		}
		else if (fChoice == 2)
		{
			this->monthPurchReportNonEssentials();
		}
	}
	else if (choice == 4)
	{
		this->categoryReportMonth(fChoice);
	}
	else if (choice == 5)
	{
		return;
	}

}


/*void CashTracker::smRunSpendingTotals(int fChoice)		// second menu option for Totals option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int choice = 0;	//will determine full or catergory spending report

		// getting user input, handling invalid input
	while (cout << "Spending Report Menu: " << endl << "(1) Full Spending Report" << endl << "(2) Category Spending Report" << endl << "(3) Spending Breakdown" << endl << "(4) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3 && choice != 4)
	{
		cout << "Enter a Valid Option; " << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)	// Full Total
	{
		if (fChoice == 1)	// Essential
		{
			this->hPrintEssentialTotal();
		}
		else if(fChoice == 2)	// NonEssential
		{
			this->hPrintNonEssentialTotal();
		}
	}
	else if (choice == 2)	// Category Spending Total
	{
		this->findCategoryTotal(fChoice);
	}
	else if (choice == 3)
	{
		if (fChoice == 1)
		{
			this->eSpendingBreakDown();
		}
		else if (fChoice == 2)
		{
			this->neSpendingBreakDown();
		}
	}
	else if (choice == 4)
	{
		return;
	}

}*/

/*void CashTracker::findCategoryTotal(int fChoice)	// Prompts user for category then displays its total
{													// Called by smRunSpendingTotals()

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential

	int needsHelp = 0;	// will be used if user enters a nonexistant category
	string cat = "";	// will be the name of the category

	if (fChoice == 1)	// Essential
	{
		while (needsHelp != 3)
		{
			if (needsHelp == 1)
			{
				this->hPrintCategories(fChoice);
			}

			try
			{ 
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(cin, cat);	
				Category C = this->_essentials._eCategories.at(cat);	// finding the category from the hashTable
				cout << "Total spent on " << cat << " : " << "$" << C.getTotalSpent() << endl << endl;	// printing the category's total to the screen
				needsHelp = 3;
			}
			catch (const std::out_of_range)
			{
				// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

		}
	}

	else if(fChoice == 2)	// NonEssential
	{
		while (needsHelp != 3)
		{
			if (needsHelp == 1)
			{
				this->hPrintCategories(fChoice);
			}

			try
			{
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(cin, cat);
				Category C = this->_nonEssentials._nCategories.at(cat);	// finding the category from the hashTable
				cout << "Total spent on " << cat << " : " << "$" << C.getTotalSpent() << endl << endl;	// printing the category's total to the screen
				needsHelp = 3;
			}
			catch (const std::out_of_range)
			{
				// prompting the user for input, handling invalid inputs
				while (cout << "Category not Found; Would you like to see existing categories?" << endl << "(1) Yes	(2)No: " && !(cin >> needsHelp) || needsHelp != 1 && needsHelp != 2)
				{
					cout << "Enter a Valid Option; " << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

		}
	}
}*/


double CashTracker::yearlyTotalAll(int desiredYear)	// calculates and returns sum of Essential purchases and NonEssential Purchases
{
	double total = 0.0;
	total += this->_essentials.calcYearSpent(desiredYear);
	total += this->_nonEssentials.calcYearSpent(desiredYear);
	return total;
}


void CashTracker::mmEssentials(int fChoice)		// Function called from the main menu that goes to secondary Essentials menu
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int sChoice = 0; // the choice the user will make from this secondary screen

		// getting user input, handling invalid input
	while (cout << endl << "Essentials Menu: " << endl << "(1) Purchase Reports" << endl << "(2) Spending Breakdowns" << endl << "(3) Add Purchase" << endl << "(4) Back" << endl && !(cin >> sChoice) || sChoice != 1 && sChoice != 2 && sChoice != 3 && sChoice != 4)
	{
		cout << "Enter a Valid Option; " << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	
	if (sChoice == 1)	// Reports
	{
		this->smRunReports(fChoice);
	}
	else if (sChoice == 2)	// Spending Totals
	{
		this->smRunBreakDowns(fChoice);
	}
	else if (sChoice == 3)	// Add Purchase
	{
		this->smAddNewPurchase(fChoice);
	}
	else if (sChoice == 4)
	{
		return;
	}
}

void CashTracker::mmNonEssentials(int fChoice)		// Function called from the main menu that goes to secondary NonEssentials menu
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int sChoice = 0;  // the choice the user will make from this secondary screen

	// getting user input, handling invalid input
	while (cout << endl << "NonEssentials Menu: " << endl << "(1) Purchase Reports" << endl << "(2) Spending BreakDowns" << endl << "(3) Add Purchase" << endl  << "(4) Back" << endl && !(cin >> sChoice) || sChoice != 1 && sChoice != 2 && sChoice != 3)
	{
		cout << "Enter a Valid Option; " << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (sChoice == 1)	// Reports
	{
		this->smRunReports(fChoice);
	}
	else if (sChoice == 2)	// Spending Totals
	{
		this->smRunBreakDowns(fChoice);
	}
	else if (sChoice == 3)	// Add Purchase
	{
		this->smAddNewPurchase(fChoice);
	}
}

void CashTracker::mmAll(int fChoice)
{
	int sChoice = 0; // the choice the user will make from this secondary screen

			// getting user input, handling invalid input
	while (cout << endl << "All Menu: " << endl << "(1) Reports" << endl << "(2) Spending Breakdown" << endl << "(3) Back" << endl && !(cin >> sChoice) || sChoice != 1 && sChoice != 2 && sChoice != 3)
	{
		cout << "Enter a Valid Option; " << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (sChoice == 1)
	{
		this->smRunReports(fChoice);
	}
	else if (sChoice == 2)
	{
		this->smRunBreakDowns(fChoice);
	}
	else if (sChoice == 3)
	{
		return;
	}
}

void CashTracker::yearlyBreakdownAll()
{
	int desiredYear = this->desiredYear();
	double total = this->yearlyTotalAll(desiredYear);

	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << std::setw(25) << std::left << "Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;
	this->_essentials.yearlyBreakdown(desiredYear, total);
	this->_nonEssentials.yearlyBreakdown(desiredYear, total);
	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "Both" << "$" << std::setw(25) << std::left << total << "100%" << endl;
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::categoryHelp(int fChoice)
{
			// fChoice will be either a 1 or 2, 1 for essentials 2 for nonEssentials
	if (fChoice == 1)
	{
		cout << endl << "Categories: " << endl;
		auto it = _essentials._eCategories.begin();
		for (; it != _essentials._eCategories.end(); it++)
		{
			cout << "	" << it->second.getCatName() << endl;
		}
		cout << endl;
	}
	else if (fChoice == 2)
	{
		cout << endl << "Categories: " << endl;
		auto it = _nonEssentials._nCategories.begin();
		for (; it != _nonEssentials._nCategories.end(); it++)
		{
			cout << "	" << it->second.getCatName() << endl;
		}
		cout << endl;
	}
}

void CashTracker::yearlyBreakdownEssential()
{
	int desiredYear = this->desiredYear();

	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "Essential Spending Breakdown " << endl << endl;
	this->_essentials.yearlyBreakdown(desiredYear);
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::yearlyBreakdownNonEssential()
{
	int desiredYear = this->desiredYear();

	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "NonEssential Spending Breakdown " << endl << endl;
	this->_nonEssentials.yearlyBreakdown(desiredYear);
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::monthPurchReportNonEssentials()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_nonEssentials.monthReport(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::monthPurchReportEssentials()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthReport(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::monthPurchReportsAll()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthReport(monthNum);
		cout << "-------------------------------------------" << endl;
		this->_nonEssentials.monthReport(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;

}

void CashTracker::smRunBreakDowns(int fChoice)
{
			// fChoice should be a 1 or a 2, 1 for essentials 2 for nonEssentials
	int choice = 0;

	while (cout << "Spending Breakdown Menu: " << endl << "(1) Yearly Breakdown" << endl << "(2) Monthly Breakdown" << endl << "(3) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)
	{
		this->yearlyBreakDowns(fChoice);
	}
	else if (choice == 2)
	{
		this->monthlyBreakDowns(fChoice);
	}
	else if (choice == 3)
	{
		return;
	}
}

void CashTracker::yearlyBreakDowns(int fChoice)
{	
		// fChoice should be 1 for essentials, 2 for nonEssentials, and 3 for all
	if (fChoice == 1)
	{
		this->yearlyBreakdownEssential();
	}
	else if (fChoice == 2)
	{
		this->yearlyBreakdownNonEssential();
	}
	else if (fChoice == 3)
	{
		this->yearlyBreakdownAll();
	}
}

void CashTracker::monthlyBreakDowns(int fChoice)
{
		// fChoice should be 1 for essentials, 2 for nonEssentials, and 3 for all
	if (fChoice == 1)
	{
		this->monthlyBreakDownEssentials();
	}
	else if (fChoice == 2)
	{
		this->monthlyBreakDownNonEsentials();
	}
	else if (fChoice == 3)
	{
		this->monthlyBreakDownAll();
	}
}

void CashTracker::monthlyBreakDownEssentials()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "SPENDING BREAKDOWN-" << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthBreakdown(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::monthlyBreakDownNonEsentials()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "SPENDING BREAKDOWN-" << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_nonEssentials.monthBreakdown(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::monthlyBreakDownAll()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "SPENDING BREAKDOWN-" << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		double monthTotal = 0.0;
		monthTotal += this->_essentials.calcMonthSpent(monthNum);
		monthTotal += this->_nonEssentials.calcMonthSpent(monthNum);

		this->_essentials.monthBreakdown(monthNum, monthTotal);
		this->_nonEssentials.monthBreakdown(monthNum, monthTotal);

		cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "All" << "$" << std::setw(25) << std::left << monthTotal << "100%" << endl;

	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

bool CashTracker::printMonth(int monthNum)
{
	switch (monthNum)
	{
	case 1:
		cout << "JANUARY- " << endl;
		return true;
		break;
	case 2:
		cout << "FEBRUARY- " << endl;
		return true;
		break;
	case 3:
		cout << "MARCH- " << endl;
		return true;
		break;
	case 4:
		cout << "APRIL- " << endl;
		return true;
		break;
	case 5:
		cout << "MAY- "<< endl;
		return true;
		break;
	case 6:
		cout << "JUNE- " << endl;
		return true;
		break;
	case 7:
		cout << "JULY- " << endl;
		return true;
		break;
	case 8:
		cout << "AUGUST- "<< endl;
		return true;
		break;
	case 9:
		cout << "SEPTEMBER- " << endl;
		return true;
		break;
	case 10:
		cout << "OCTOBER- " << endl;
		return true;
		break;
	case 11:
		cout << "NOVEMBER- " << endl;
		return true;
		break;
	case 12:
		cout << "DECEMBER- " << endl;
		return true;
		break;
	default:
		cout << "Invalid Month Entered; " << endl;
		return false;
		break;
	}
}

int CashTracker::desiredYear()
{
	int desiredYear = 0;

	while (cout << "Enter the Year you Want to See (yyyy): " && !(cin >> desiredYear) || (desiredYear < 2000))
	{
		cout << "Enter a valid option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	// desiredYear should be at least 2000 by now

	desiredYear = desiredYear - 2000;
	// desiredYear shoud now be yy
	
	return desiredYear;
}

int CashTracker::desiredMonth()
{
	int monthNum = 0;

	while (cout << "Enter the Month you want to see (mm): " && !(cin >> monthNum) || (monthNum < 1 || monthNum >12))
	{
		cout << "Enter a valid option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return monthNum;
}