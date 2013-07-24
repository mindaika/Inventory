#include <iostream>
#include <fstream>
#include "item.h"
#include "inventory.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// MODIFIED FROM ORIGINAL SOURCE

void AddItem(inventory& inv,char* name,double weight)
{
	std::cout << "Adding " << name << " with a weight of " << weight << "." << std::endl;
	inv.AddItem(item(name,weight));
}

void RemoveItem(inventory& inv,char* name)
{
	std::cout << "Removing " << name << "." << std::endl;
	inv.RemoveItem(name);
}

void doTest() 
{
	inventory inv;

	// Make sure printing an empty inventory works
	inv.PrintInventory();

	// Make sure adding the first one works
	AddItem(inv,"helmet",5);
	inv.PrintInventory();

	// Add some more items
	AddItem(inv,"bracelet of power",1);
	AddItem(inv,"red potion",2);
	inv.PrintInventory();

	// Add some duplicates
	AddItem(inv,"bracelet of power",1);
	inv.PrintInventory();

	// Add some same name, different weight items
	AddItem(inv,"red potion",5);
	AddItem(inv,"bracelet of power",7);
	inv.PrintInventory();

	// Add some heavy stuff
	AddItem(inv,"bag of gold coins",50);
	AddItem(inv,"bag of gold coins",50);

	// Now some removes
	RemoveItem(inv,"short sword");
	RemoveItem(inv,"helmet");
	RemoveItem(inv,"bracelet of power");
	inv.PrintInventory();

	RemoveItem(inv,"bracelet of power");
	RemoveItem(inv,"red potion");
	inv.PrintInventory();
}

int main() {
	doTest();

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		std::cout << "Memory leaks!" << std::endl;
	}
#endif

	std::cout << "Press Return to exit...";
	getchar();
	return 0;
}
