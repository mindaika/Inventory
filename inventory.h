#ifndef _INVENTORY
#define _INVENTORY
#include "item.h"

class inventory
{
private:
	static const int DEFAULT_MAX_WEIGHT = 100; // Default maximum for inventory weight
	double maxWeight; // User set maximum for inventory weight
	double totalWeight; // Combined weight of items in the bag
	int totalCount; // Combined count of Items in the bag
	item* currentItemPointer; // Pointer to current item; used for list traversal
	item* headPointer; // Pointer to the head of the list
public:
	int GetCurrentCount() const;
	double GetCurrentWeight() const;
	void PrintInventory();
	int AddItem(item&);
	int RemoveItem(char*);
	inventory();
	inventory(double);
	~inventory();
}; // end Inventory
#endif