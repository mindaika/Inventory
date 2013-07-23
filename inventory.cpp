#include <iostream>
#include "inventory.h"
#include <assert.h>

// Default constructor
inventory::inventory()
{
	headPointer = nullptr;
	currentItemPointer = nullptr;
	maxWeight = DEFAULT_MAX_WEIGHT;
	totalCount = 0;
	totalWeight = 0;
} // end default constructor

// Paramaterized constructor
inventory::inventory(double max)
{
	headPointer = nullptr;
	currentItemPointer = nullptr;
	maxWeight = max;
	totalCount = 0;
	totalWeight = 0;
} // end paramaterized constructor

// default destructor
// Kills any items remaining... like a good fuction. Who's a good function? That's right. 
// You're a good function. Now go get the the object! Go!
inventory::~inventory()
{
	currentItemPointer = headPointer;
	while (headPointer != nullptr) {
		currentItemPointer = currentItemPointer->getNextItemPointer();
		delete headPointer;
		headPointer = currentItemPointer;
	}

} // end destructor

// Pre-condition: an Item object
// Post-condition: If successful, an item of name "name" has been
// added to the bag, and totalItemCount has increased by 1
// Paramaters: a reference to the object to be added
// Returns: 1 on successfully processed addition attempt, 2 on processed attempt, but failed addition
int inventory::AddItem(item &newItem)
{
	int itemAddSuccess = 0;
	item* newItemPointer = new item(newItem);
	double weightAdded = newItemPointer->getItemWeight();
	std::string itemName = newItemPointer->getItemName();
	currentItemPointer = headPointer;

	if ((totalWeight + newItemPointer->getItemWeight()) > maxWeight) {
		std::cout << "You're not strong enough to pick up the " << newItemPointer->getItemName() << " with everything else you're carrying." << std::endl;
		itemAddSuccess = 2;
		delete newItemPointer;
		newItemPointer = nullptr;
	}

	while(!itemAddSuccess) {
		if (headPointer == nullptr) {
			// First item in list
			headPointer = newItemPointer;
			itemAddSuccess = 1;
		} else if (currentItemPointer->getItemName().compare(newItemPointer->getItemName()) == 0) {
			if (currentItemPointer->getItemWeight() == newItemPointer->getItemWeight()) {
				currentItemPointer->increaseItemCount();
				itemAddSuccess = 1;
				delete newItemPointer;
				newItemPointer = nullptr;
			} else {
				std::cout << "Error: tried to add duplicate items with differing weights." << std::endl;
				itemAddSuccess = 2; // Also adds philosophical discussion about the meaning of "success"
				delete newItemPointer;
				newItemPointer = nullptr;
			}
		} else if (currentItemPointer->getItemName().compare(newItemPointer->getItemName()) > 0) {
			// currentItemPointer points to only object in 1 object list, and object pointed to is later in the alphabet
			assert(headPointer==currentItemPointer);
			newItemPointer->setNextItemPointer(headPointer);
			headPointer = newItemPointer;
			itemAddSuccess = 1;
		} else if (currentItemPointer->getNextItemPointer() == nullptr) {
			// currentItemPointer points to last object in chain, which is not later in the alphabet
			currentItemPointer->setNextItemPointer(newItemPointer);
			itemAddSuccess = 1;
		} else if (currentItemPointer->getNextItemPointer()->getItemName().compare(newItemPointer->getItemName()) > 0) {
			// Next item is later in the alphabet than newItem
			newItemPointer->setNextItemPointer(currentItemPointer->getNextItemPointer());
			currentItemPointer->setNextItemPointer(newItemPointer);
			itemAddSuccess = 1;
		} else {
			currentItemPointer = currentItemPointer->getNextItemPointer();
		}
	}
	
	if (itemAddSuccess == 1) {
		totalCount = totalCount + 1;
		totalWeight = totalWeight + weightAdded;
		std::cout << "You picked up a " << itemName << std::endl;
	}
	return itemAddSuccess;
}

// Pre-condition: None
// Post-condition: If successful, an item of name "name" has been
// removed from the bag, and totalItemCount has decreased by 1
// Paramaters: the name of an object to be removed
// Returns: 1 on successful operation
int inventory::RemoveItem(char* name)
{
	std::string itemToRemove(name);
	bool itemMatch = 0;
	item* destroyer;
	currentItemPointer = headPointer;
	while (currentItemPointer != nullptr) {
		// First item is only item in list; item matches search string; more than one copy of item in list
		if (currentItemPointer->getItemName().compare(itemToRemove) == 0 && currentItemPointer->getNextItemPointer()->getItemCount() > 1) {
			destroyer = currentItemPointer;
			currentItemPointer->getNextItemPointer()->decreaseItemCount();
			totalWeight = totalWeight - (currentItemPointer->getItemWeight());
			delete destroyer;
			destroyer = nullptr;
			currentItemPointer = nullptr;
			itemMatch = 1;
			totalCount--;
			std::cout << "You dropped a " << itemToRemove << std::endl;
		// First item is only item in list; item matches search string; only one copy of item in list
		} else if (currentItemPointer->getItemName().compare(itemToRemove) == 0 && currentItemPointer->getNextItemPointer()->getItemCount() == 1) {
			destroyer = currentItemPointer->getNextItemPointer();
			currentItemPointer->setNextItemPointer(currentItemPointer->getNextItemPointer()->getNextItemPointer());
			totalWeight = totalWeight - (destroyer->getItemWeight());
			delete destroyer;
			destroyer = nullptr;
			currentItemPointer = nullptr;
			itemMatch = 1;
			totalCount--;
			std::cout << "You dropped a " << itemToRemove << std::endl;
		// First item is only item in list; item does not search string
		} else if (currentItemPointer->getNextItemPointer() == nullptr) {
			currentItemPointer = nullptr;
		// Item in list; item matches search string; more than one copy of item in list
		} else if (currentItemPointer->getNextItemPointer()->getItemName().compare(itemToRemove) == 0 && (currentItemPointer->getNextItemPointer()->getItemCount() > 1) ) {
			currentItemPointer->getNextItemPointer()->decreaseItemCount();
			totalWeight = totalWeight - (currentItemPointer->getNextItemPointer()->getItemWeight());
			currentItemPointer = nullptr;
			itemMatch = 1;
			totalCount--;
			std::cout << "You dropped a " << itemToRemove << std::endl;
		// Item in list; item matches search string; only one copy of item in list
		} else if (currentItemPointer->getNextItemPointer()->getItemName().compare(itemToRemove) == 0 && (currentItemPointer->getNextItemPointer()->getItemCount() == 1) ) {
			destroyer = currentItemPointer->getNextItemPointer();
			currentItemPointer->setNextItemPointer(currentItemPointer->getNextItemPointer()->getNextItemPointer());
			totalWeight = totalWeight - (destroyer->getItemWeight());
			delete destroyer;
			destroyer = nullptr;
			currentItemPointer = nullptr;
			itemMatch = 1;
			totalCount--;
			std::cout << "You dropped a " << itemToRemove << std::endl;
		// Search string does not match next item; advance itemPointer
		} else {
			currentItemPointer = currentItemPointer->getNextItemPointer();
		}
	};

	if (itemMatch == 0) {
		std::cout << "You don't have a " << itemToRemove << " in your inventory.\n";
	}
	return 1;
}

// Pre-condition: None
// Post-condition: None
// Returns: totalCount
int inventory::GetCurrentCount() const
{
	return totalCount;
}

// Pre-condition: None
// Post-condition: None
// Returns: totalWeight
double inventory::GetCurrentWeight() const
{
	return totalWeight;
}

// Pre-condition: None
// Post-condition: None
// Prints out formatted list of Item objects
void inventory::PrintInventory() //const
{
	currentItemPointer = headPointer;
	std::cout << "\nCurrent inventory: \n";
	if (currentItemPointer == nullptr) {
		std::cout << std::setw(20) << "(no items)\n\n";
	} else {
		while (currentItemPointer != nullptr) {
			std::cout << std::setw(9) << "[" << currentItemPointer->getItemCount() 
				<< "] " << currentItemPointer->getItemName() << " (weight: " 
				<< currentItemPointer->getItemWeight() << ")\n";
			currentItemPointer = currentItemPointer->getNextItemPointer();
		}
		std::cout << "Total items: " << GetCurrentCount() << std::endl;
		std::cout << "Total weight: " << GetCurrentWeight() << std::endl << std::endl;
	}
}
