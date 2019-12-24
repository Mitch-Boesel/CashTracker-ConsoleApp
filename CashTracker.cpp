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
	int fChoice = 0;	//first choice, will be used for the main while loop. 1 for Essential or 2 for NonEssential 
	
	while (fChoice != 4)	// Main Menu Screen that will loop until the user chooses to exit
	{
			//Displays the main menu, handles invalid inputs
		while (cout << endl << "Main Menu:" << endl << "(1) Add Purchase" << endl << "(2) Purchase Reports" << endl << "(3) Spending Breakdowns" << endl << "(4) Exit" << endl && !(cin >> fChoice) || fChoice != 1 && fChoice != 2 && fChoice != 3 && fChoice != 4)
		{
			cout << "Enter a Valid Option; " << endl << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
	switch(fChoice)	//Essentials
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

void CashTracker::addNewPurchase()
{
	cout << "Adding a new Purchase!" << endl << endl;

	if (this->_essentials._eCategories.empty() == true)	// checking to see if its the first purchase
	{
		this->addNewCategoryPurchase();
	}
	else		// Not the first purchase 
	{
		cout << "Enter the category" << endl;
		cout << "New Category (0):  " << endl;
		std::vector<Category> vec = this->_essentials._eCategories;
		for (int i = 0; i < vec.size(); i++)
		{
			cout << vec[i].getCatName() << " (" << i+1 << "): " << endl;
		}

		int choice;
		cin >> choice;

		if (choice == 0)
			this->addNewCategoryPurchase();
		else
		{
			this->_essentials._eCategories[choice-1].newPurchase();
			this->_essentials.setTotalSpent();
		}
	}
}

void CashTracker::addNewCategoryPurchase()
{
		// fChoice should be a 1 or 2, 1 for essential 2 for nonEssential

		string name = "";
		string ess = "";
		bool essential = true;
		cout << "Enter the Name of the New Category: ";
		cin.ignore();
		std::getline(std::cin, name);	// getting the name of the new category
		cout << "Is this category deemed essential?(true or false)";
		cin >> ess;
		if (ess != "true")
			essential = false;
		Category* nCat = new Category(name, essential);	// Creating the new Category
		nCat->newPurchase();	// Prompting the user for the new purchase data to be added to the category

		_essentials._eCategories.push_back(*nCat);	// Adding the new category to the Essentials hashTable
		this->_essentials.setTotalSpent();
	
}

void CashTracker::yearlyReport()	// Prints all Essential Purchases to the screen
{
	int desiredYear = this->desiredYear();
	cout << endl << "20" << desiredYear << "- ";

	this->_essentials.yearlyReport(desiredYear);
}
void CashTracker::yearlyCategoryReport()
{
	int desiredYear = this->desiredYear();

	cout << "Enter the category" << endl;
	std::vector<Category> vec = this->_essentials._eCategories;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << " (" << i + 1 << ") " << vec[i].getCatName() << ": " << endl;
	}

	int choice;
	cin >> choice;


	Category cat = this->_essentials._eCategories[choice-1];	// finding the chosen category
	cout << endl << "----------------------------------------------------------------------";
	cat.printYearlyReport(desiredYear);	//calling for the category to print its purchase report
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::categoryReportMonth()
{
	int monthNum = this->desiredMonth();

	cout << "Enter the category" << endl;
	std::vector<Category> vec = this->_essentials._eCategories;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << " (" << i+1 << ") " << vec[i].getCatName() << ": "  << endl;
	}

	int choice;
	cin >> choice;

	Category cat = this->_essentials._eCategories[choice-1];	// finding the chosen category
	cout << endl << "----------------------------------------------------------------------" << endl;
	if (this->printMonth(monthNum))
		cat.printMonth(monthNum);	//calling for the category to print its purchase report

	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}

void CashTracker::runReports()	// second menu for Reports Option
{											// Calls neccessary functions based on user input
											// Used for both Essential and NonEssential Secondary menu

		// fChoice should be a 1, 2 or 3, 1 for essential 2 for nonEssential 3 for all
	int choice = 0;	//will determine full or catergory report

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

	case 4:
		this->categoryReportMonth();
		break;

	case 5:
		return;
	}
}

void CashTracker::yearlyBreakdown()
{
	int desiredYear = this->desiredYear();

	cout << "SPENDING BREAKDOWN-";
	cout << endl << "----------------------------------------------------------------------" << endl;
	cout << "Essential Spending Breakdown " << endl << endl;
	this->_essentials.yearlyBreakdown(desiredYear);
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}


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


void CashTracker::runBreakDowns()
{
	int choice = 0;

	while (cout << "Spending Breakdown Menu: " << endl << "(1) Yearly Breakdown" << endl << "(2) Monthly Breakdown" << endl << "(3) Back" << endl && !(cin >> choice) || choice != 1 && choice != 2 && choice != 3)
	{
		cout << "Enter a Valid Option;" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (choice == 1)
	{
		this->yearlyBreakdown();
	}
	else if (choice == 2)
	{
		this->monthlyBreakDown();
	}
	else if (choice == 3)
	{
		return;
	}
}

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