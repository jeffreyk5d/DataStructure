#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};

class ArrayPolynomial {
public:
	PolynomialTerm terms[MAX_TERMS];

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0;

		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

		terms[i].coef = coef;
		terms[i].expo = expo;

		return;
	}

	void printArrayBasedPoly()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			cout << terms[0].coef;
		else
			cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				cout << " + " << terms[i].coef;
			else
				cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	void printArrayBasedPolyRecursively()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			cout << terms[0].coef;
		else
			cout << terms[0].coef << "X^" << terms[0].expo;

		printArrayBasedPolyRecursively(1);
	}

	void printArrayBasedPolyRecursively(int i)
	{
		//add your code here
		if (terms[i].coef == 0) {			
			return;
		}
		else {
			if (terms[i].expo == 0) {
				cout <<" + "<< terms[i].coef;
			}
			else {
				cout << " + " << terms[i].coef<<"X^"<<terms[i].expo;
			}
		}
		printArrayBasedPolyRecursively(i + 1);		
	}

	void ArrayBasedDifferentiation()
	{
		//add your code here		
		
		for (int currSpot = 0; currSpot < MAX_TERMS; currSpot++) {
			if (terms[currSpot].coef == 0) {
				break;
			}
			if (terms[currSpot].expo == 0) {
				for (int i = currSpot; i < MAX_TERMS - 1; i++) {
					terms[i] = terms[i + 1];
				}
				currSpot--;
			}
			else {
				terms[currSpot].coef = terms[currSpot].expo * terms[currSpot].coef;
				terms[currSpot].expo = terms[currSpot].expo - 1;
			}
		}
		
		return;
	}

	void compactCopy(ArrayPolynomial& poly)
	{
		//add your code here
		int tag[MAX_TERMS] = { 0 };		
		int length = 0;
		int maxExpo = 0;
		while (poly.terms[length].coef!= 0) {
			length++;
		}
		int inputPosi = 0;
		for (int i = 0; i < length;i++) {
			maxExpo = 0;
			while (tag[maxExpo] != 0) {
				maxExpo++;
			}			
			for (int j = 0; j < length; j++) {
				if (tag[j] != 1) {
					if ( poly.terms[maxExpo].expo< poly.terms[j].expo) {
						maxExpo = j;
					}
				}								
			}
			tag[maxExpo] = 1;
			terms[inputPosi].coef = poly.terms[maxExpo].coef;
			terms[inputPosi].expo = poly.terms[maxExpo].expo;			
			inputPosi++;
		}		
		for (int i = 0; i < length-1; i++) {
			if (terms[i].expo == terms[i + 1].expo) {
				terms[i].coef = terms[i].coef + terms[i + 1].coef;
				for (int j = i+1; j < length; j++) {
					terms[j] = terms[j + 1];
				}
				length--;
				i--;
			}
		}
		
		
	}
};

/*
if (terms[i].coef != 0) {
			cout << " + ";
			if (terms[i].expo == 0)
				cout << terms[i].coef;
			else
				cout << terms[i].coef << "X^" << terms[i].expo;
			printArrayBasedPolyRecursively(i + 1);
		}*/

/*
int j = 0;
		for (int i = 0;;i++) { //3 2 2 1 1 0 0 0
			if (!terms[i].coef)
				break;
			if (terms[i].expo == 0) {
				for (j = i;!terms[j].coef;j++)
					terms[j] = terms[j + 1];
				terms[j].coef = 0;
				terms[j].expo = 0;
			}
			terms[i].coef *= terms[i].expo;
			terms[i].expo -= 1;
		}*/

/*
int size = 0;

		for (int i=0;i<MAX_TERMS;i++) {
			if (poly.terms[i].coef == 0)
				break;

			else {

				for (int j = 0;j < MAX_TERMS;j++) {

					if (terms[j].coef == 0) {
						terms[j] = poly.terms[i];
						break;
					}

					else if (terms[j].expo == poly.terms[i].expo) {
						if (terms[j].coef + poly.terms[i].coef == 0) {
							for (int k = j;k<size-1;k++) {
								terms[k] = terms[k + 1];
							}
							break;
						}
						else {
							terms[j].coef += poly.terms[i].coef;
							break;
						}
					}

					else if (poly.terms[i].expo > terms[j].expo) {
						for (int k = size;k > j;k--) {
							terms[k] = terms[k - 1];
						}
						terms[j] = poly.terms[i];
						break;
					}
				}
				size++;
			}
		}*/

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm* nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm* polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm* tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		LinkedPolynomialTerm* tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = polynomialTermPtr;

		polynomialTermPtr = tmpPtr;

		// add your code here 


		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm* termPtr = polynomialTermPtr;

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	void printLinkBasedPolyRecursively()
	{
		if (polynomialTermPtr == nullptr)
			return;

		if (polynomialTermPtr->expo == 0)
			cout << polynomialTermPtr->coef;
		else
			cout << polynomialTermPtr->coef << "X^" << polynomialTermPtr->expo;

		printLinkBasedPolyRecursively(polynomialTermPtr->nextTermPtr);
	}

	void printLinkBasedPolyRecursively(LinkedPolynomialTerm* currPtr)
	{
		//add your code here
		if (currPtr == nullptr) {
			return;
		}
		else {
			if (currPtr->expo == 0) {
				cout << " + " << currPtr->coef;
			}
			else {
				cout << " + " << currPtr->coef << "X^" << currPtr->expo;
			}
		}
		printLinkBasedPolyRecursively(currPtr->nextTermPtr);
		return;

	}

	int computeRecursively(int x)
	{
		return computeRecursively(x, polynomialTermPtr);
	}

	int computeRecursively(int x, LinkedPolynomialTerm* currPtr)
	{


		// add yor code here

		 
		return 0;
	}

	void LinkBasedDifferentiation()
	{
		//add your code here
		LinkedPolynomialTerm* currPtr = polynomialTermPtr;
		LinkedPolynomialTerm* prePtr = nullptr;
		if (polynomialTermPtr == nullptr) {
			return;
		}
		while (currPtr != nullptr) {
			if (currPtr->expo == 0||currPtr->coef==0) {
				if (prePtr == nullptr) {
					polynomialTermPtr = polynomialTermPtr->nextTermPtr;
				}
				else {
					currPtr = currPtr->nextTermPtr;
					prePtr->nextTermPtr = currPtr;
				}
			}
			else {
				currPtr->coef = currPtr->coef * currPtr->expo;
				currPtr->expo = currPtr->expo - 1;
			}
			if (currPtr == nullptr) {
				break;
			}
			prePtr = currPtr;
			currPtr = currPtr->nextTermPtr;
		}

		return;
	}

	void compactCopy(LinkedPolynomial& poly)
	{
		//add your code here
		LinkedPolynomialTerm* data=poly.polynomialTermPtr;		
		while (data != nullptr) {			
			LinkedPolynomialTerm* currPtr = polynomialTermPtr;			
			LinkedPolynomialTerm* prePtr = nullptr;
			LinkedPolynomialTerm* tmpPtr;
			tmpPtr = new LinkedPolynomialTerm;
			tmpPtr->coef = data->coef;
			tmpPtr->expo = data->expo;
			tmpPtr->nextTermPtr = nullptr;
			if (polynomialTermPtr == nullptr) {
				polynomialTermPtr = tmpPtr;
				data = data->nextTermPtr;
				continue;
			}
			while (currPtr != nullptr && data->expo < currPtr->expo) {
				prePtr = currPtr;
				currPtr = currPtr->nextTermPtr;
			}
			if (currPtr!=nullptr&&data->expo == currPtr->expo) {
				currPtr->coef = currPtr->coef + data->coef;				
				if (currPtr->coef == 0) {
					if (prePtr == nullptr) {
						polynomialTermPtr = polynomialTermPtr->nextTermPtr;
					}
					else {
						currPtr = currPtr->nextTermPtr;
						prePtr->nextTermPtr = currPtr;
					}
					if (currPtr == nullptr) {
						data = data->nextTermPtr;
						continue;
					}
				}
				data = data->nextTermPtr;
				continue;
			}
			tmpPtr->nextTermPtr = currPtr;
			if (prePtr == nullptr) {
				polynomialTermPtr = tmpPtr;
			}
			else {
				prePtr->nextTermPtr = tmpPtr;
			}

			data = data->nextTermPtr;
		}
		return;
	}
};

/*
if (currPtr) {
			cout << " + ";
			if (currPtr->expo == 0)
				cout << currPtr->coef;
			else
				cout << currPtr->coef << "X^" << currPtr->expo;
			printLinkBasedPolyRecursively(currPtr->nextTermPtr);
		}*/

/*
LinkedPolynomialTerm* pre = polynomialTermPtr;
		LinkedPolynomialTerm* temp = polynomialTermPtr;
		for (;temp;temp=temp->nextTermPtr) {
			if (temp->expo == 0) {
				if (temp == polynomialTermPtr) {
					temp = temp->nextTermPtr;
					delete polynomialTermPtr;
					polynomialTermPtr = temp;
				}
				else {
					pre->nextTermPtr = temp->nextTermPtr;
					delete temp;
					temp = pre->nextTermPtr;
				}
			}
			if (!temp)
				break;

			temp->coef *= temp->expo;
			temp->expo -= 1;
			pre = temp;
		}*/

/*
LinkedPolynomialTerm* temp = nullptr;
		LinkedPolynomialTerm* pre = nullptr;
		LinkedPolynomialTerm* ptr = poly.polynomialTermPtr;

		for (;ptr;ptr = ptr->nextTermPtr) {

			LinkedPolynomialTerm* newnode=new LinkedPolynomialTerm;
			if (!polynomialTermPtr) {
				newnode->coef = ptr->coef;
				newnode->expo = ptr->expo;
				newnode->nextTermPtr = nullptr;
				polynomialTermPtr = newnode;
				continue;
			}
			for (temp=polynomialTermPtr;temp;temp = temp->nextTermPtr) {

				if (temp->expo == ptr->expo) {
					if (temp->coef + ptr->coef == 0) {
						if (temp == polynomialTermPtr) {
							temp = temp->nextTermPtr;
							delete polynomialTermPtr;
							polynomialTermPtr = temp;
							break;
						}
						pre->nextTermPtr = temp->nextTermPtr;
						delete temp;
						break;
					}
					temp->coef += ptr->coef;
					break;
				}

				else if (ptr->expo > temp->expo) {
					newnode->coef = ptr->coef;
					newnode->expo = ptr->expo;
					newnode->nextTermPtr = temp;

					if (temp == polynomialTermPtr)
						polynomialTermPtr = newnode;
					else
						pre->nextTermPtr = newnode;
					break;
				}
				else if (!temp->nextTermPtr) {

					newnode->coef = ptr->coef;
					newnode->expo = ptr->expo;
					newnode->nextTermPtr = nullptr;
					temp->nextTermPtr = newnode;
					break;
				}
				pre = temp;
			}
		}*/