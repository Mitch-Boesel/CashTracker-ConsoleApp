#include "CashTracker.h"

CashTracker::CashTracker()
{
	cout << std::setprecision(2) << std::fixed;

	this->_essentials.buildEssentials();
	//this->_nonEssentials.buildNonEssentials();
	cout << endl;
}

CashTracker::~CashTracker()
{
	this->_essentials.storeEssentials();
	//->_nonEssentials.storeNonEssentials();
}

void CashTracker::mainMenu()
{
	cout << "Welcome to CASH TRACKER" << endl;
	int fChoice = 0;	// the users choice, (1) for adding a purchase, (2) for purchase reports, (3) for spending breakdowns
	
	while (fChoice != 4)	// Main Menu Screen that will loop until the user chooses to exit
	{
			//Displays the main menu, handles invalid inputs
		while (cout << endl << "Main Menu:" << endl << "(1) Add Purchase" << endl << "(2) Purchase Reports" << endl << "(3) Spending Breakdowns" << endl << "(4) Exit" << endl && !(cin >> fChoice) || fChoice != 1 && fChoice != 2 && fChoice != 3 && fChoice != 4)
		{
			cout << "Enter a Valid Option; " << endl << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
	switch(fChoice)	// calling appropriate function based on user input
		{
		case 1:
			this->addNewPurchase();
			break;
		case 2:
			this->runReports();
			break;
		case 3:
			this->runBreakDowns();
			break;
		case 4:
			break;	// Exit
		}
	}
}

// function called by the main menu for adding a new purchase
void CashTracker::addNewPurchase()
{
	cout << "Adding a new Purchase!" << endl << endl;

	if (this->_essentials._eCategories.empty() == true)	// checking to see if its the first purchase
	{
		this->addNewCategoryPurchase();
	}
	else		// Not the first purchase 
	{
		// printing the categories for the user to choose
		cout << "Enter the category" << endl;
		cout << "New Category (0):  " << endl;
		std::vector<Category> vec = this->_essentials._eCategories;
		for (int i = 0; i < vec.size(); i++)
		{
			cout << vec[i].getCatName() << " (" << i+1 << "): " << endl;
		}

		// getting the users choice
		int choice;
		cin >> choice;

		// if its a 0, the user is adding a new category
		if (choice == 0)
			this->addNewCategoryPurchase();
		// else, the user is adding a new purchase to an existing category
		else
		{
			// getting the appropriate category and calling its new purchase function
			this->_essentials._eCategories[choice-1].newPurchase();
			this->_essentials.setTotalSpent();
		}
	}
}

// function that handles creating a new category, and adding a purchase to the category
void CashTracker::addNewCategoryPurchase()
{
		// local variables to be used
		string name = "";
		string ess = "";		// string value of the whether the category is deemed essential by the user
		bool essential = true;	// boolean value to be set based on the above variable

		// prompting the user for information on the new category
		cout << "Enter the Name of the New Category: ";
		cin.ignore();
		std::getline(std::cin, name);	// getting the name of the new category
		cout << "Is this category deemed essential?(true or false)";
		cin >> ess;
		// setting the boolean essential value based on the user input
		if (ess != "true")
			essential = false;

		Category* nCat = new Category(name, essential);	// Creating the new Category
		nCat->newPurchase();	// Prompting the user for the new purchase data to be added to the category

		_essentials._eCategories.push_back(*nCat);	// Adding the new category to the main vector
		this->_essentials.setTotalSpent();			// setting the main vectors total spent member variable
	
}

// Prints all Purchases to the screen
void CashTracker::yearlyReport()
{
	int desiredYear = this->desiredYear();
	cout << endl << "20" << desiredYear << "- ";

	this->_essentials.yearlyReport(desiredYear);
}

// Prints all the purchases of a certain category
void CashTracker::yearlyCategoryReport()
{
	// getting the desired year from the user
	int desiredYear = this->desiredYear();

	// printing all the categories for the user to choose from
	cout << "Enter the category" << endl;
	std::vector<Category> vec = this->_essentials._eCategories;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << " (" << i + 1 << ") " << vec[i].getCatName() << ": " << endl;
	}

	// getting the users choice
	int choice;
	cin >> choice;

	// displaying all the categories purchases for the year
	Category cat = this->_essentials._eCategories[choice-1];	// finding the chosen category
	cout << endl << "----------------------------------------------------------------------";
	cat.printYearlyReport(desiredYear);	//calling for the category to print its purchase report
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

// Prints a certain categories purchases for a particular month
void CashTracker::categoryReportMonth()
{
	// getting the users desired year
	int monthNum = this->desiredMonth();

	// displaying the categories for the user to choose
	cout << "Enter the category" << endl;
	std::vector<Category> vec = this->_essentials._eCategories;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << " (" << i+1 << ") " << vec[i].getCatName() << ": "  << endl;
	}

	// getting the users choice
	int choice;
	cin >> choice;

	// displaying the purchases of the chosen category for the chosen month
	Category cat = this->_essentials._eCategories[choice-1];	// finding the chosen category
	cout << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
		cat.printMonth(monthNum);	//calling for the category to print its purchase report

	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

// Called by the main menu function, promts the user for what report they would like to see
void CashTracker::runReports()
{
	int choice = 0;	

	// getting the user input, handling invalid inputs
	while (cout << "Purchase Report Menu: " << endl << "(1) Yearly Report" << endl << "(2) Yearly Category Report" << endl << "(3) Monthy Report" << endl << "(4) Monthly Category Report" << endl << "(5) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3 && choice !=4 && choice != 5)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	switch (choice)
	{

	case 1:// full report
		this->yearlyReport();
		break;

	case 2:	// category report
		this->yearlyCategoryReport();
		break;

	case 3: // monthly purchase report
		this->monthPurchReport();
		break;

	case 4: // category month report
		this->categoryReportMonth();
		break;

	case 5:	// return the main menu
		return;
	}
}

// displays the spending breakdown of every category for a year
void CashTracker::yearlyBreakdown()
{
	int desiredYear = this->desiredYear();

	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "Essential Spending Breakdown " << endl << endl;
	this->_essentials.yearlyBreakdown(desiredYear);
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

// Displays all purchases for a certain month
void CashTracker::monthPurchReport()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthReport(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

// Called by the Main Menu function, prompts user for the type of breakdown they want
void CashTracker::runBreakDowns()
{
	int choice = 0;

	while (cout << "Spending Breakdown Menu: " << endl << "(1) Yearly Breakdown" << endl << "(2) Monthly Breakdown" << endl << "(3) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)	// Breakdown for a year
	{
		this->yearlyBreakdown();
	}
	else if (choice == 2)	// Breakdown for a month
	{
		this->monthlyBreakDown();
	}
	else if (choice == 3)	// Return to main menu
	{
		return;
	}
}

// Prints the spending breakdown for a particular month
void CashTracker::monthlyBreakDown()
{
	int monthNum = this->desiredMonth();

	cout << endl << endl << "SPENDING BREAKDOWN-" << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
	{
		this->_essentials.monthBreakdown(monthNum);
	}
	cout << endl << "----------------------------------------------------------------------" << endl;
}

// Takes the user input for a month, and returns if its a valid month option
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

// prompts the user to enter a year they want to see, returns their input
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

// promts the user for what month they would like to see, returns their input
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