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
			this->mmAll();
			break;
		case 4:
			break;	// Exit
		}
	}
}

int CashTracker::essestialOrNonEssential()	// Not used since I changed the interface, but returns the type of purchase to be viewed
{
	int choice = 0;

		while (choice != 1 && choice != 2)	//getting input from the user
		{
			cout << endl << "(1)Essential Purchase	or	(2)NonEssential Purchase: " << endl;
			cin >> choice;
		}
	return choice;
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
	}
}

void CashTracker::printFullReport()	// prints all purchases to the screen 
{
	this->printEssentials();	// printing Essential purchases
	this->printNonEssentials();	// printing NonEssential purchases
	cout << endl << endl;
}

void CashTracker::printEssentials()	// Prints all Essential Purchases to the screen
{
	cout << endl << "ESSENTIAL PURCHASES:" << endl;
	cout << endl << "----------------------------------------------------------------------";
	auto itE = _essentials._eCategories.begin();	// Iterator for the Essentials hashTable
	for (; itE != _essentials._eCategories.end(); itE++)	//Iterating through each category
	{
		itE->second.printFullReport();	// calling for each category to print their purchases
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}
void CashTracker::printNonEssentials() // Prints all NonEssential Purchases to the screen
{
	cout << endl  << "NONESSENTIALS PURCHASES:" << endl;
	cout << endl << "----------------------------------------------------------------------";
	auto itN = _nonEssentials._nCategories.begin();	//itterator for the NonEssentials hashTable
	for (; itN != _nonEssentials._nCategories.end(); itN++)		// Iterating through each category
	{
		itN->second.printFullReport();	// calling for each category to print their purchases
	}

	cout << endl << "----------------------------------------------------------------------" << endl;
}
void CashTracker::printSingleCategory(int fChoice)
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

void CashTracker::smRunReports(int fChoice)	// second menu for Reports Option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int choice = 0;	//will determine full or catergory report

			// getting the user input, handling invalid inputs
	while (cout << "Report Menu: " << endl << "(1) Full Report" << endl << "(2) Category Report" << endl << "(3)Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)	// full report
	{
		if (fChoice == 1)	// Essential
		{
			this->printEssentials();
		}
		else if(fChoice == 2)	// NonEssential
		{
			this->printNonEssentials();
		}
	}

	else if(choice == 2)	// category report
	{
		this->printSingleCategory(fChoice);
	}
	else if (choice == 3)
	{
		return;
	}

}


void CashTracker::smRunSpendingTotals(int fChoice)		// second menu option for Totals option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int choice = 0;	//will determine full or catergory spending report

		// getting user input, handling invalid input
	while (cout << "Spending Menu: " << endl << "(1) Full Spending Report" << endl << "(2) Category Spending Report" << endl << "(3) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
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
		return;
	}

}

void CashTracker::findCategoryTotal(int fChoice)	// Prompts user for category then displays its total
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
}

void CashTracker::hPrintEssentialTotal()	// called by smRunSpendingTotals(int fChoice)
{											// prints the total spent on essentials to the screen

	double rTotal = this->essentialTotal();	// getting the Essential total
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << endl << "Money spent on Essentials is $" << rTotal << endl << endl;;	// printing the total to the screen
	cout << endl << "----------------------------------------------------------------------" << endl;
}
void CashTracker::hPrintNonEssentialTotal()	  // called by smRunSpendingTotals(int fChoice)
{											  // prints the total spent on NonEssentials to the screen

	double rTotal = this->nonEssentialTotal();	// getting the NonEssential total
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << endl << "Money spent on NonEssentials is $" << rTotal << endl << endl;	// printing the NonEssential total to the screen
	cout << endl << "----------------------------------------------------------------------" << endl;
}

double CashTracker::essentialTotal()
{
	double rTotal = 0.00;	//Running total 
	auto it = this->_essentials._eCategories.begin();	// iterator for the Essentails hashTable
	for (; it != this->_essentials._eCategories.end(); it++)	// iterating through the hashTable
	{
		rTotal += it->second.getTotalSpent();	// adding each category's total to the running total
	}

	return rTotal;
}

double CashTracker::nonEssentialTotal()
{
	double rTotal = 0.0;	//Running total 
	auto it = this->_nonEssentials._nCategories.begin();	// iterator for the NonEssentials hashTable
	for (; it != this->_nonEssentials._nCategories.end(); it++)		// iterating through the hashTable
	{
		rTotal += it->second.getTotalSpent();	// adding each category's total to the running total
	}

	return rTotal;
}

double CashTracker::fullTotal()	// calculates and returns sum of Essential purchases and NonEssential Purchases
{
	double total = 0.0;
	total += this->essentialTotal();
	total += this->nonEssentialTotal();
	return total;
}


void CashTracker::mmEssentials(int fChoice)		// Function called from the main menu that goes to secondary Essentials menu
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int sChoice = 0; // the choice the user will make from this secondary screen

		// getting user input, handling invalid input
	while (cout << endl << "Essentials Menu: " << endl << "(1) Purchase Reports" << endl << "(2) Spending Reports" << endl << "(3) Add Purchase" << endl << "(4) Back" << endl && !(cin >> sChoice) || sChoice != 1 && sChoice != 2 && sChoice != 3 && sChoice != 4)
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
		this->smRunSpendingTotals(fChoice);	
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
	while (cout << endl << "NonEssentials Menu: " << endl << "(1) Purchase Reports" << endl << "(2) Spending Reports" << endl << "(3) Add Purchase" << endl  << "(4) Back" << endl && !(cin >> sChoice) || sChoice != 1 && sChoice != 2 && sChoice != 3)
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
		this->smRunSpendingTotals(fChoice);
	}
	else if (sChoice == 3)	// Add Purchase
	{
		this->smAddNewPurchase(fChoice);
	}
}

void CashTracker::mmAll()
{
	int sChoice = 0; // the choice the user will make from this secondary screen

			// getting user input, handling invalid input
	while (cout << endl << "All Menu: " << endl << "(1) Full Report" << endl << "(2) Full Spending Total" << endl << "(3) Spending Breakdown" << endl << "(4) Back" << endl && !(cin >> sChoice) || sChoice != 1 && sChoice != 2 && sChoice != 3 && sChoice != 4)
	{
		cout << "Enter a Valid Option; " << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (sChoice == 1)
	{
		this->printFullReport();	// Printing Full Report to the Screen
	}
	else if (sChoice == 2)
	{
		double total = this->fullTotal();
		cout << "Total Money Spent: $" << total << endl << endl;
	}
	else if (sChoice == 3)
	{
		this->amSpendingBreakDown();
	}
	else if (sChoice == 4)
	{
		return;
	}
}

void CashTracker::amSpendingBreakDown()
{
	double totalSpent = this->fullTotal();		// totalSpent = total money spent

	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "Spending Breakdown " << endl << endl;
	cout << std::setw(25) << std::left <<"Category:" << std::setw(25) << std::left << "Type of Purchase:" << std::setw(25) << std::left << "Money Spent:" << std::setw(25) << std::left << "% of Total Spent:" << endl;
	auto it = this->_essentials._eCategories.begin();
	double percentage = 0.0;
	for (; it != this->_essentials._eCategories.end(); it++)	// itertator for essentials hashTable
	{
		percentage = it->second.getTotalSpent() / totalSpent;
		percentage = std::round(percentage * 100);
		cout << std::setw(25) << std::left << it->second.getCatName()<< std::setw(25) << std::left << "Essential" << "$" << std::setw(25) << std::left << it->second.getTotalSpent() << (int)percentage << "%" << endl;
	}

	it = this->_nonEssentials._nCategories.begin();
	for (; it != this->_nonEssentials._nCategories.end(); it++)
	{
		percentage = it->second.getTotalSpent() / totalSpent;
		percentage = std::round(percentage * 100);
		cout << std::setw(25) << std::left << it->second.getCatName() << std::setw(25) << std::left << "NonEssential" << "$" << std::setw(25) << std::left << it->second.getTotalSpent() << (int)percentage << "%" << endl;
	}

	cout << endl << std::setw(25) << std::left << "Total" << std::setw(25) << std::left << "Both" << "$" << std::setw(25) << std::left << totalSpent << "100%" << endl;
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