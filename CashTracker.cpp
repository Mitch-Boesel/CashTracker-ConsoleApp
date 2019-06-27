#include "CashTracker.h"

void CashTracker::mainMenu()
{
	cout << "Welcome to CASH TRACKER" << endl << endl;
	int fChoice = 0;	//first choice, will be used for the main while loop. 1 for Essential or 2 for NonEssential 
	
	while (fChoice != 3)	// Main Menu Screen that will loop until the user chooses to exit
	{
		cout << "What Purchases would you like to see?" << endl;
		cout << "(1) Essentials" << endl << "(2) NonEssentials" << endl << "(3) Exit" << endl;
		cin >> fChoice;
		
		switch(fChoice)	//Essentials
		{
		case 1:
			this->mmEssentials(fChoice);	// Takes you to Essentails secondary menu
			break;
		case 2:
			this->mmNonEssentials(fChoice);	// Takes you to NonEssentials secondary menu
			break;
		case 3:
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
	while (nOrE != 1 && nOrE != 2)
	{
		cout << "(1) existing category	or	(2) new category: ";
		cin.ignore();	// hoping this will stop the weird loop that sometimes occurs
		cin >> nOrE;
	}
	if (nOrE == 1)	// New purchase on an existing category
	{
		this->hAddExistingCategoryPurchase(fChoice);
	}
	else if(nOrE == 2) // New purchase to a new category
	{
		this->hAddNewCategoryPurchase(fChoice);
	}

}

void CashTracker::hAddExistingCategoryPurchase(int fChoice)		// Helper function to smAddNewPurchase()
{																// adds new purchase to an existing category
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	if (fChoice == 1)	//essential purchase
	{
		cout << endl << "Categories: " << endl;
		auto it = _essentials._eCategories.begin();
		for (; it != _essentials._eCategories.end(); it++)	//printing out all the category choices
		{
			cout << "	" << it->second.getCatName() << endl;
		}
		string pCat = "";
		cout << "Enter Category: ";
		cin.ignore();
		std::getline(std::cin, pCat);	// getting category from the user

		Category & chosenCat = this->_essentials._eCategories.at(pCat);	//finding the category
		chosenCat.newPurchase();	// calling its newPurchase() function to promt the user for the purchase data

	}

	else if(fChoice == 2)	// NonEssential
	{
		cout << endl << "Categories: " << endl;
		auto it = _nonEssentials._nCategories.begin();
		for (; it != _nonEssentials._nCategories.end(); it++)	//printing out all the category choices
		{
			cout << "	" << it->second.getCatName() << endl;	
		}
		string pCat = "";
		cout << "Enter Category: ";
		cin.ignore();
		std::getline(std::cin, pCat);	// getting the category from the user

		Category & chosenCat = this->_nonEssentials._nCategories.at(pCat);	// finding the category
		chosenCat.newPurchase();	// calling its newPurchase() function to promt the user for the purchase data
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
	string choice = "";		// category the user will choose

	cout << "Enter the Category: ";
	cin.ignore();
	std::getline(std::cin, choice);		// getting category for the user

	if (fChoice == 1)	// Essential
	{
		Category cat = this->_essentials._eCategories.at(choice);	// finding the chosen category
		cout << endl << "----------------------------------------------------------------------";
		cat.printFullReport();	//calling for the category to print its purchase report
		cout << endl << "----------------------------------------------------------------------" << endl << endl;
	}

	else if(fChoice == 2)	// NonEssential
	{
		Category cat = this->_nonEssentials._nCategories.at(choice);	// finding the chosen category
		cout << endl << "----------------------------------------------------------------------";
		cat.printFullReport();	//calling for the category to print its purchase report
		cout << endl << "----------------------------------------------------------------------" << endl << endl;
	}
}

void CashTracker::smRunReports(int fChoice)	// second menu for Reports Option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int choice = 0;	//will determine full or catergory report
	cout << "(1) Full Report" << endl << "(2) Category Report" << endl;
	cin >> choice;	// getting the choice from the user

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

}


void CashTracker::smRunSpendingTotals(int fChoice)		// second menu option for Totals option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int choice = 0;	//will determine full or catergory spending report
	cout << "(1) Full Total" << endl << "(2) Category Total" << endl;
	cin >> choice;	// getting choice from the user

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
	if (choice == 2)	// Category Spending Total
	{
		this->findCategoryTotal(fChoice);
	}

}

void CashTracker::findCategoryTotal(int fChoice)	// Prompts user for category then displays its total
{													// Called by smRunSpendingTotals()

		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	string cat = "";	// will be the name of the category
	cout << "Enter the Category: ";
	cin.ignore();
	std::getline(cin, cat);		// getting category from the user

	if (fChoice == 1)	// Essential
	{
		Category C = this->_essentials._eCategories.at(cat);	// finding the category from the hashTable
		cout << "Total spent on " << cat << " : " << C.getTotalSpent() << endl;	// printing the category's total to the screen
	}

	else if(fChoice == 2)	// NonEssential
	{
		Category C = this->_nonEssentials._nCategories.at(cat);	// finding the category from the hashTable
		cout << "Total spent on " << cat << " : " << C.getTotalSpent() << endl;	// printing the category's total to the screen
	}
}

void CashTracker::hPrintEssentialTotal()	// called by smRunSpendingTotals(int fChoice)
{											// prints the total spent on essentials to the screen

	double rTotal = 0.00;	//Running total 
	auto it = this->_essentials._eCategories.begin();	// iterator for the Essentails hashTable
	for (; it != this->_essentials._eCategories.end(); it++)	// iterating through the hashTable
	{
		rTotal += it->second.getTotalSpent();	// adding each category's total to the running total
	}

	cout << endl << "Money spent on Essentials is " << rTotal << endl << endl;;	// printing the total to the screen
}
void CashTracker::hPrintNonEssentialTotal()	  // called by smRunSpendingTotals(int fChoice)
{											  // prints the total spent on NonEssentials to the screen
	double rTotal = 0.0;	//Running total 
	auto it = this->_nonEssentials._nCategories.begin();	// iterator for the NonEssentials hashTable
	for (; it != this->_nonEssentials._nCategories.end(); it++)		// iterating through the hashTable
	{
		rTotal += it->second.getTotalSpent();	// adding each category's total to the running total
	}

	cout << endl << "Money spent on NonEssentials is " << rTotal << endl;	// printing the NonEssential total to the screen
}

void CashTracker::mmEssentials(int fChoice)		// Function called from the main menu that goes to secondary Essentials menu
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int sChoice = 0; // the choice the user will make from this secondary screen
	cout << endl << "Essentials: " << endl;
	cout << "(1) Reports" << endl << "(2) Spending Totals" << endl << "(3) Add Purchase" << endl;
	cin >> sChoice;	// getting the choice from the user

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

void CashTracker::mmNonEssentials(int fChoice)		// Function called from the main menu that goes to secondary NonEssentials menu
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential
	int sChoice = 0;  // the choice the user will make from this secondary screen
	cout << endl << "NonEssentials: " << endl;
	cout << "(1) Reports" << endl << "(2) Spending Totals" << endl << "(3) Add Purchase" << endl;
	cin >> sChoice;	// getting the choice from the user

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