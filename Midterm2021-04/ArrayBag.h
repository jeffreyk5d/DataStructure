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
	bool remove(const ItemType& anEntry);
	bool remove(const ArrayBag<ItemType>& aBag);
	void remove();
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
   	vector<ItemType> toVector() const;
}; // end ArrayBag


template<class ItemType>
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY)
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
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{


	// add yor code here


	return false;
}  // end remove

template<class ItemType>
void ArrayBag<ItemType>::remove()
{
	// add yor code here
	if (isEmpty()) {
		return;
	} 
	//sort
	string temp;
	for (int i = 0; i < getCurrentSize(); i++) {
		for (int j = 0; j < getCurrentSize(); j++) {
			if (items[i] > items[j]) {
				temp = items[i];
				items[i] = items[j];
				items[j] = temp;
			}
			
		}
	}

	int tag[20] = { 0 };
	int get[20] = { 0 };
	int count = 0;
	for (int i = 1; i < getCurrentSize(); i++) {
		if (items[i - 1] != items[i]) {
			tag[i-1] = 1;
			get[count] = i-1;
			count++;
			if (i == getCurrentSize() - 1) {
				tag[i] = 1;
				get[count] = i ;
				count++;
			}
		}
	}
	count = 0;
	for (int i = 0; i < 20; i++) {
		if (tag[i] == 1) {
			count++;
		}
	}
	string a[20] = { "0" };
	for (int i = 0; i < count; i++) {
		a[i] = items[get[i]];
	}
	clear();
	for (int i = 0; i < count; i++) {
		add(a[i]);
	}

}