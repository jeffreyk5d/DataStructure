#include "BagInterface.h"
#include <cstddef>
#include <string>

template<class ItemType>
class ArrayBag : public BagInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 10; // Small size to test for a full bag
	ItemType items[DEFAULT_CAPACITY];      // Array of bag items
	int itemCount;                         // Current count of bag items 
	int maxItems;                          // Max capacity of the bag

public:
	ArrayBag();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	void copy(const ArrayBag<ItemType> anotherBag);
	void compact();
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	vector<ItemType> toVector() const;
}; // end ArrayBag


template<class ItemType>
ArrayBag<ItemType>::ArrayBag() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int curIndex = 0;       // Current array index

	while (curIndex < itemCount)
	{
		if (items[curIndex] == anEntry)
		{
			frequency++;
		}  // end if
		curIndex++;          // Increment to next entry
	}  // end while

	return frequency;
}  // end getFrequencyOf

template<class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;

	for (int i = 0; i < itemCount; i++)
		bagContents.push_back(items[i]);

	return bagContents;
}  // end toVector

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
	}

	return hasRoomToAdd;
}  // end add

template<class ItemType>
void ArrayBag<ItemType>::copy(const ArrayBag<ItemType> aBag)
{
	// add your code here
	for (int i = 0; i < aBag.getCurrentSize(); i++) {
		add(aBag.items[i]);
	}
	return;
}  // end

template<class ItemType>
void ArrayBag<ItemType>::compact()
{
	//add your code here
	for (int i = 0; i < getCurrentSize()-1; i++) {
		for (int j = i; j < getCurrentSize(); j++) {
			if (i!=j&&items[i] == items[j]) {
				for (int k = j; k < getCurrentSize(); k++) {
					items[k] = items[k+1];
				}				
				j--;
				itemCount--;
			}			
		}
	}
	return;
}  // end


/*
for (int i = 0;i < aBag.itemCount;i++)
		add(aBag.items[i]);


	return;*/

/*
for (int i = 0;i < itemCount;i++) {
		for (int j = i+1;j < itemCount;j++) {
			if (items[i] == items[j]) {
				for (int k = j;k < itemCount-1;k++)
					items[k] = items[k + 1];
				itemCount--;
				j--;

			}
		}
	}

	return;*/