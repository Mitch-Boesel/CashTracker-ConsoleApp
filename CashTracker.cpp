#include "CashTracker.h"

void CashTracker::mainMenu()
{
	int choice = 0;
	while (choice != 6)
	{
		cout << "(1) Print Full Spending Report" << endl;
		cout << "(2) Print Essential Purchases" << endl;
		cout << "(3) Print NonEssential Purchases" << endl;
		cout << "(4) Print a Single Category Report" << endl;
		cout << "(5) Add a New Purchase" << endl;
		cout << "(6) Exit CashTracker" << endl << endl;
		cin >> choice;

		switch (choice)
		{
			case 1:
				this->printFullReport();
				break;
			case 2:
				this->printEssentials();
				break;
			case 3:
				this->printNonEssentials();
				break;
			case 4:
				this->printSingleCategory();
				break;
			case 5:
				this->addNewPurchase();
				break;
			case 6:
				break;
		}
	}

}

int CashTracker::essestialOrNonEssential()
{
	int choice = 0;

		while (choice != 1 && choice != 2)	//getting input from the user
		{
			cout << endl << "(1)Essential Purchase	(2)NonEssential Purchase: " << endl;
			cin >> choice;
		}
	return choice;
}

void CashTracker::addNewPurchase()
{
	int choice = this->essestialOrNonEssential();
	int nOrE = 0;	//new or existing
	while (nOrE != 1 && nOrE != 2)
	{
		cout << "(1) existing category, (2) new category: ";
		cin >> nOrE;
	}
	if (nOrE == 1)
	{
		this->addNewExistingCategoryPurchase(choice);
	}
	else
	{
		this->addNewCategoryPurchase(choice);
	}

}
void CashTracker::addNewExistingCategoryPurchase(int choice)
{

	if (choice == 1)	//essential purchase
	{
		cout << endl << "Categories: " << endl;
		auto it = _essentials._eCategories.begin();
		for (; it != _essentials._eCategories.end(); it++)	//printing out all the category choices
		{
			cout << "	" << it->second.getCatName() << endl;
		}
		string pCat = "";
		cin >> pCat;
		
		it = _essentials._eCategories.begin();
		for (; it != _essentials._eCategories.end(); it++)	//finding the chosen category
		{
			if (pCat == it->second.getCatName())
			{
				break;
			}
		}
		it->second.newPurchase();

	}

	else
	{
		cout << endl << "Categories: " << endl;
		auto it = _nonEssentials._nCategories.begin();
		for (; it != _nonEssentials._nCategories.end(); it++)	//printing out all the category choices
		{
			cout << "	" << it->second.getCatName() << endl;
		}
		string pCat = "";
		cin >> pCat;

		it = _nonEssentials._nCategories.begin();
		for (; it != _nonEssentials._nCategories.end(); it++)	//finding the chosen category
		{
			if (pCat == it->second.getCatName())
			{
				break;
			}
		}
		it->second.newPurchase();

	}
}

void CashTracker::addNewCategoryPurchase(int choice)
{
	if (choice == 1)
	{
		string name = "";
		cout << "Enter the Name of the New Category: ";
		cin.ignore();
		std::getline(std::cin, name);
		Category* nCat = new Category(name);
	//	nCat->setKey(_essentials.getNextKey());
		nCat->newPurchase();

		_essentials._eCategories.insert(std::make_pair(nCat->getCatName(), *nCat));
	}

	else
	{
		string name = "";
		cout << "Enter the Name of the New Category: ";
		std::getline(cin, name);
		Category* nCat = new Category(name);
		//nCat->setKey(_nonEssentials.getNextKey());
		nCat->newPurchase();

		_nonEssentials._nCategories.insert(std::make_pair(nCat->getCatName(), *nCat));
	}
	//_groups.insert(std::make_pair(newCategory->getKey(), *newCategory));	//adding the category to the Essentials hash table (_groups)
	
}

void CashTracker::printFullReport()
{
	this->printEssentials();
	this->printNonEssentials();
	cout << endl << endl;
}
void CashTracker::printEssentials()
{
	cout << endl << "ESSENTIAL PURCHASES:" << endl;
	auto itE = _essentials._eCategories.begin();	// Iterator for essentail
	for (; itE != _essentials._eCategories.end(); itE++)
	{
		itE->second.printFullReport();
	}
	cout << endl;
}
void CashTracker::printNonEssentials()
{
	cout << "NONESSENTIALS PURCHASES:" << endl;
	auto itN = _nonEssentials._nCategories.begin();	//itterator for nonEssential
	for (; itN != _nonEssentials._nCategories.end(); itN++)
	{
		itN->second.printFullReport();
	}

	cout << endl;
}
void CashTracker::printSingleCategory()
{
	int eOrN = this->essestialOrNonEssential();


}