#include "CashTracker.h"

CashTracker::CashTracker()
{
	cout << std::setprecision(2) << std::fixed;

		// getting the user, handles invalid inputs
	while (cout << "Mitch or Mom?" << endl && cin >> this->_user && this->_user != "Mitch" && this->_user != "Mom")
	{
		cout << "Enter a Valid Option;" << endl << endl;
	}

	this->_essentials.buildEssentials(_user);
	this->_nonEssentials.buildNonEssentials(_user);
	cout << endl;
}

CashTracker::~CashTracker()
{
	this->_essentials.storeEssentials(_user);
	this->_nonEssentials.storeNonEssentials(_user);
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
				this->hPrintCategories(fChoice);
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
				this->hPrintCategories(fChoice);
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

void CashTracker::fullReportAll()	// prints all purchases to the screen 
{
	this->fullReportEssentials();	// printing Essential purchases
	this->fullReportNonEssentials();	// printing NonEssential purchases
	cout << endl << endl;
}

void CashTracker::fullReportEssentials()	// Prints all Essential Purchases to the screen
{
	this->_essentials.fullReport();
}
void CashTracker::fullReportNonEssentials() // Prints all NonEssential Purchases to the screen
{
	this->_nonEssentials.fullReport();
}
void CashTracker::categoryReport(int fChoice)
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int needsHelp = 0;		// used for handling a possible exception
	string choice = "";		// category the user will choose

	if (fChoice == 1)
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
				std::getline(std::cin, choice);

				Category cat = this->_essentials._eCategories.at(choice);	// finding the chosen category
				cout << endl << "----------------------------------------------------------------------";
				cat.printFullReport();	//calling for the category to print its purchase report
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
				this->hPrintCategories(fChoice);
			}
			try
			{
				cout << "Enter the Category: ";
				cin.ignore();
				std::getline(std::cin, choice);

				Category cat = this->_nonEssentials._nCategories.at(choice);	// finding the chosen category
				cout << endl << "----------------------------------------------------------------------";
				cat.printFullReport();	//calling for the category to print its purchase report
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

	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);

	if (month.front() == '0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

	if (fChoice == 1)
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
				this->hPrintCategories(fChoice);
			}
			try
			{
				cout << "Enter the Category: ";
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
		while (cout << "Purchase Report Menu: " << endl << "(1) Full Report" << endl << "(2) Monthy Report" << endl << "(3) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Enter a Valid Option;" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (choice == 1)
		{
			this->fullReportAll();
		}
		else if (choice == 2)
		{
			this->monthPurchReportsAll();
		}
		return;
	}

			// getting the user input, handling invalid inputs
	while (cout << "Purchase Report Menu: " << endl << "(1) Full Report" << endl << "(2) Category Report" << endl << "(3) Monthy Report" << endl << "(4) Monthly Category Report" << endl << "(5) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3 && choice !=4 && choice != 5)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)	// full report
	{
		if (fChoice == 1)	// Essential
		{
			this->fullReportEssentials();
		}
		else if(fChoice == 2)	// NonEssential
		{
			this->fullReportNonEssentials();
		}
	}

	else if(choice == 2)	// category report
	{
		this->categoryReport(fChoice);
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


double CashTracker::fullTotal()	// calculates and returns sum of Essential purchases and NonEssential Purchases
{
	double total = 0.0;
	total += this->_essentials.getTotalSpent();
	total += this->_nonEssentials.getTotalSpent();
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

void CashTracker::spendingBreakdownAll()
{
	double total = this->fullTotal();

	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << std::setw(25) << std::left << "Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;
	this->_essentials.fullBreakdown(total);
	this->_nonEssentials.fullBreakdown(total);
	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "Both" << "$" << std::setw(25) << std::left << total << "100%" << endl;
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::hPrintCategories(int fChoice)
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

void CashTracker::spendingBreakdownEssential()
{
	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "Essential Spending Breakdown " << endl << endl;
	this->_essentials.fullBreakdown();
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::spendingBreakdownNonEssential()
{
	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "NonEssential Spending Breakdown " << endl << endl;
	this->_nonEssentials.fullBreakdown();
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::monthPurchReportNonEssentials()
{
	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);
	
	if (month.front() =='0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

	cout << endl << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_nonEssentials.monthReport(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::monthPurchReportEssentials()
{
	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);

	if (month.front() == '0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

	cout << endl << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthReport(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::monthPurchReportsAll()
{
	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);

	if (month.front() == '0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

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
		this->spendingBreakDownTotals(fChoice);
	}
	else if (choice == 2)
	{
		this->spendingBreakDownMonthly(fChoice);
	}
	else if (choice == 3)
	{
		return;
	}
}

void CashTracker::spendingBreakDownTotals(int fChoice)
{	
		// fChoice should be 1 for essentials, 2 for nonEssentials, and 3 for all
	if (fChoice == 1)
	{
		this->spendingBreakdownEssential();
	}
	else if (fChoice == 2)
	{
		this->spendingBreakdownNonEssential();
	}
	else if (fChoice == 3)
	{
		this->spendingBreakdownAll();
	}
}

void CashTracker::spendingBreakDownMonthly(int fChoice)
{
		// fChoice should be 1 for essentials, 2 for nonEssentials, and 3 for all
	if (fChoice == 1)
	{
		this->spendingBreadownMonthlyEssentials();
	}
	else if (fChoice == 2)
	{
		this->spendingBreakdownMonthlyNonEsentials();
	}
	else if (fChoice == 3)
	{
		this->spendingBreakdownMonthlyAll();
	}
}

void CashTracker::spendingBreadownMonthlyEssentials()
{
	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);

	if (month.front() == '0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

	cout << endl << endl << "SPENDING BREAKDOWN-" << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthBreakdown(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::spendingBreakdownMonthlyNonEsentials()
{
	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);

	if (month.front() == '0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

	cout << endl << endl << "SPENDING BREAKDOWN-" << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_nonEssentials.monthBreakdown(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

void CashTracker::spendingBreakdownMonthlyAll()
{
	string month = "";
	cout << "Enter the Month you want to see (mm): ";
	cin.ignore();
	getline(cin, month);

	if (month.front() == '0')
	{
		month.erase(month.begin());
	}
	int monthNum = std::stoi(month);

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