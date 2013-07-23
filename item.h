#ifndef _ITEM
#define _ITEM
#include <string>
#include <iomanip>

class item
{
private:
	std::string itemName;	// The name of the item
	double itemWeight;		// The weight of the item
	item* nextItemPointer;	// A pointer to the next item in a linked list implementation
	int count;				// The number of items of this type in existence
public:
	item(const char*, const double);
	~item();
	std::string getItemName() const;
	item* getNextItemPointer() const;
	double getItemWeight() const;
	int getItemCount() const;
	void setNextItemPointer(item*);
	void increaseItemCount();
	void decreaseItemCount();
}; // end Item

#endif
