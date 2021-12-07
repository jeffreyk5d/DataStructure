#include "BagInterface.h"
#include "Node.h"
#include <cstddef>
#include <string>

template<class ItemType>
class LinkedBag : public BagInterface<ItemType>
{
private:
	Node<ItemType>* headPtr; // Pointer to first node
	int itemCount;           // Current count of bag items

public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
	virtual ~LinkedBag();                       // Destructor should be virtual
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	void copy(const LinkedBag<ItemType>* anotherBag);
	void compact();
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	vector<ItemType> toVector() const;
}; // end LinkedBag

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor


template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
	clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;

	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
	Node<ItemType>* nextNodePtr = new Node<ItemType>();
	
	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);
	
	headPtr = nextNodePtr;
	itemCount++;

	return true;
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if

		counter++;
		curPtr = curPtr->getNext();
	} // end while

	return frequency;
}  // end getFrequencyOf


template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while

	return bagContents;
}  // end

template<class ItemType>
void LinkedBag<ItemType>::copy(const LinkedBag<ItemType>* anotherBag)
{	
	//add your code here	
	Node<ItemType>* data = anotherBag->headPtr;	
	Node<ItemType>* prePtr = nullptr;
	while (data != nullptr) {
		Node<ItemType>* tmpPtr;
		tmpPtr = new Node<ItemType>;
		tmpPtr->setItem(data->getItem());		
		tmpPtr->setNext(nullptr);	
		if (prePtr == nullptr) {
			headPtr = tmpPtr;
			prePtr = headPtr;
			data = data->getNext();
			itemCount++;
			continue;
		}
		else {
			prePtr->setNext(tmpPtr);
		}
		prePtr = prePtr->getNext();		
		data = data->getNext();
		itemCount++;
	}
	
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::compact()
{
	//add your code here
	Node<ItemType>* compare = headPtr;

	while (compare!=nullptr) {
		Node<ItemType>* currPtr = headPtr;
		Node<ItemType>* prePtr = nullptr;
		while (currPtr!=nullptr) {
			while (currPtr!=compare&&currPtr!=nullptr&&compare->getItem() == currPtr->getItem()) {
				if (prePtr == nullptr) {
					headPtr = headPtr->getNext();					
				}
				else {
					currPtr=currPtr->getNext();
					prePtr->setNext(currPtr);
				}
				itemCount--;
			}
			if (currPtr == nullptr) {
				break;
			}
			prePtr = currPtr;
			currPtr = currPtr->getNext();
		}		
		compare = compare->getNext();
	}
}  // end


/*
Node<ItemType>* temp = anotherBag->headPtr;
	Node<ItemType>* move = new Node<ItemType>;
	for (;temp;temp = temp->getNext()) {

		Node<ItemType>* newnode = new Node<ItemType>();
		newnode->setItem(temp->getItem());

		if (headPtr == nullptr) {
			headPtr = newnode;
			move = headPtr;
		}
		else {
			move->setNext(newnode);
			move = move->getNext();
		}
		itemCount++;
	}
	return;*/

/*
Node<ItemType>* temp1=headPtr;
	Node<ItemType>* temp2 = nullptr;

	for (;temp1;temp1 = temp1->getNext()) {
		Node<ItemType>* pre = nullptr;
		pre = temp1;
		for (temp2 = temp1->getNext();temp2;temp2 = temp2->getNext()) {
			if (temp2->getItem() == temp1->getItem()) {
				itemCount--;
				pre->setNext(temp2->getNext());
				delete temp2;
				temp2 = pre;
			}
			pre = temp2;
		}
	}
	return;*/