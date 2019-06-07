#include "CashTracker.h"

void CashTracker::mainMenu()
{

}

int CashTracker::essestialOrNonEssential()
{
	int choice = 0;

	if (choice != 1 && choice != 2)	//getting the input from the user
	{
		while (choice != 1 && choice != 2)
		{
			cout << "Enter (1) for an Essential Purchase or a (2) for a NonEssential Purchase: ";
			cin >> choice;
		}
	}
	return choice;
}

void CashTracker::addNewPurchase()
{
	int choice = this->essestialOrNonEssential();
	int nOrE = 0;	//new or existing
	while (nOrE != 1 && nOrE != 2)
	{
		cout << "Enter 1 to add a new purchase to an existing category, enter 2 to add a new purchase to a new category: ";
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
		auto it = _essentials._groups.begin();
		for (; it != _essentials._groups.end(); it++)	//printing out all the category choices
		{
			cout << "	" << it->second.getField() << endl;
		}
		string pCat = "";
		cin >> pCat;
		
		it = _essentials._groups.begin();
		for (; it != _essentials._groups.end(); it++)	//finding the chosen category
		{
			if (pCat == it->second.getField())
			{
				break;
			}
		}
		it->second.newPurchase();

	}

	else
	{
		cout << endl << "Categories: " << endl;
		auto it = _nonEssentials._groups.begin();
		for (; it != _nonEssentials._groups.end(); it++)	//printing out all the category choices
		{
			cout << "	" << it->second.getField() << endl;
		}
		string pCat = "";
		cin >> pCat;

		it = _nonEssentials._groups.begin();
		for (; it != _nonEssentials._groups.end(); it++)	//finding the chosen category
		{
			if (pCat == it->second.getField())
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
		cin >> name;
		Category* nCat = new Category(name);
		nCat->setKey(_essentials.getNextKey());
		nCat->newPurchase();

		_essentials._groups.insert(std::make_pair(nCat->getKey(), *nCat));
	}

	else
	{
		string name = "";
		cout << "Enter the Name of the New Category: ";
		cin >> name;
		Category* nCat = new Category(name);
		nCat->setKey(_nonEssentials.getNextKey());
		nCat->newPurchase();

		_nonEssentials._groups.insert(std::make_pair(nCat->getKey(), *nCat));
	}
	//_groups.insert(std::make_pair(newCategory->getKey(), *newCategory));	//adding the category to the Essentials hash table (_groups)
	
}

void CashTracker::printFullReport()
{

}
void CashTracker::printEssentials()
{

}
void CashTracker::printNonEssentials()
{

}
void CashTracker::printSingleCategory()
{

}