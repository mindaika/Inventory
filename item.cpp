#include "item.h"

// Parameterized constructor, with defaults
item::item(const char* name = "Boiled Rock", const double weight = 0)
{
	std::string tempName(name);
	itemName = tempName;
	itemWeight = weight;
	nextItemPointer = nullptr;
	count = 1;
} // end parameterized constructor

// Default destructor
item::~item()
{
	nextItemPointer = nullptr;
} // end destructor

// Pre-condition: None
// Post-condition: None
// Returns: itemName
std::string item::getItemName() const
{
	return itemName;
}

// Pre-condition: None
// Post-condition: None
// Returns: itemWeight
double item::getItemWeight() const
{
	return itemWeight;
}

// Pre-condition: None
// Post-condition: nextItemPointer is set to value of next
// Returns: None
void item::setNextItemPointer(item* next)
{
	nextItemPointer = next;
}

// Pre-condition: None
// Post-condition: None
// Returns: nextItemPointer
item* item::getNextItemPointer() const
{
	return nextItemPointer;
}

// Pre-condition: None
// Post-condition: None
// Returns: count
int item::getItemCount() const
{
	return count;
}

// Pre-condition: None
// Post-condition: Item count is incrememented by one
// Returns: None
void item::increaseItemCount()
{
	count++;
}

// Pre-condition: None
// Post-condition: Item count is decremented by one
// Returns: None
void item::decreaseItemCount()
{
	count--;
}