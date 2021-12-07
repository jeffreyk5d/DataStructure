//#include "stdafx.h"
#include <iostream>
#include<math.h>
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
		//  add your code here
		if (terms[0].coef == 0 && terms[0].expo== 0) {
			terms[0].coef = coef;
			terms[0].expo = expo;
			return;
		}
		int inputPosi = 0;
		for (inputPosi = 0; inputPosi < MAX_TERMS && terms[inputPosi].coef != 0 && expo < terms[inputPosi].expo; inputPosi++);//¨ìterms[i].coef==0³B°±¤î
		

		
		if (expo == terms[inputPosi].expo) {
			if (coef == 0) {
				for (int i = inputPosi; i < MAX_TERMS - 1; i++) {//¸É¬}
					terms[i] = terms[i + 1];
				}
			}
			else {
				terms[inputPosi].coef = terms[inputPosi].coef + coef;
				if (terms[inputPosi].coef == 0) {
					for (int i = inputPosi; i < MAX_TERMS - 1; i++) {//¸É¬}
						terms[i] = terms[i + 1];
					}
				}
			}			
			return;
		}
		
		for (int i = MAX_TERMS - 1; i > inputPosi; i--) {//«á²¾
			terms[i] = terms[i - 1];
		}
		terms[inputPosi].coef = coef;
		terms[inputPosi].expo = expo;
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
			if (terms[i].expo==0) {
				cout << " + " << terms[i].coef;
			}
			else {
				cout << " + " << terms[i].coef << "X^" << terms[i].expo;
			}
			
		}
		printArrayBasedPolyRecursively(i + 1);
		return;
	}


	int computeRecursively(int x)
	{
		return computeRecursively(x, 0);
	}

	int computeRecursively(int x, int i)
	{ 
		//add your code here
		if (terms[i].coef == 0) {
			return 0;
		}
		else {
			return terms[i].coef*(int)pow(x,terms[i].expo)+computeRecursively(x, i + 1);
		}
	}

	void copy(ArrayPolynomial& poly)
	{


		// add yor code here




	}
};

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
		//add your code here
		LinkedPolynomialTerm* tmpPtr;
		tmpPtr= new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;
		if (polynomialTermPtr == nullptr) {
			polynomialTermPtr = tmpPtr;
			return;
		}
		LinkedPolynomialTerm* currPtr = polynomialTermPtr;
		LinkedPolynomialTerm* prePtr = nullptr;
		while (currPtr != nullptr && expo < currPtr->expo) {
			prePtr = currPtr;
			currPtr = currPtr->nextTermPtr;
		}
		if (currPtr == nullptr) {
			prePtr->nextTermPtr = tmpPtr;
			return;
		}
		if (expo == currPtr->expo) {
			if (coef == 0) {
				if (prePtr == nullptr) {
					polynomialTermPtr = polynomialTermPtr->nextTermPtr;
				}
				else {					
					currPtr = currPtr->nextTermPtr;
					prePtr->nextTermPtr = currPtr;
				}
				return;
			}

			else {

				currPtr->coef=coef + currPtr->coef;
				if (currPtr->coef == 0) {
					if (prePtr == nullptr) {
						polynomialTermPtr = polynomialTermPtr->nextTermPtr;
					}
					else {
						currPtr = currPtr->nextTermPtr;
						prePtr->nextTermPtr = currPtr;
					}
				}
				return;
			}
		}
		tmpPtr->nextTermPtr = currPtr;
		if (prePtr == nullptr) {			
			polynomialTermPtr = tmpPtr;
		}
		else {
			prePtr->nextTermPtr = tmpPtr;
		}
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
		if (currPtr==nullptr) {
			return;
		}
		else {
			if (currPtr->expo==0) {
				cout << " + " << currPtr->coef;
			}
			else {
				cout << " + " << currPtr->coef << "X^" << currPtr->expo;
			}
			
			printLinkBasedPolyRecursively(currPtr->nextTermPtr);
		}
		
	}

	int computeRecursively(int x)
	{
		return computeRecursively(x, polynomialTermPtr);
	}

	int computeRecursively(int x, LinkedPolynomialTerm* currPtr)
	{
		//add your code here
		if (currPtr == nullptr) {
			return 0;
		}
		else {
			return currPtr->coef * pow(x, currPtr->expo) + computeRecursively(x, currPtr->nextTermPtr);
		}		
	}

	void copy(LinkedPolynomial& poly)
	{


		// add yor code here


	}
};

/*
void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0, j = 0, size = 0;
		if (!terms[i].coef) {
			terms[i].coef = coef;
			terms[i].expo = expo;
			return;
		}

		for (;j < MAX_TERMS;j++)
			if (terms[j].coef != 0)
				size++;

		for (;i <= size; i++) {
			if (expo == terms[i].expo) {

				if (coef + terms[i].coef == 0)
					for (j = i;j < size;j++)
						terms[j] = terms[j + 1];

				else
					terms[i].coef += coef;

				return;
			}
			else if (expo > terms[i].expo) {

				for (j = size;j > i;j--)
					terms[j] = terms[j - 1];

				terms[i].coef = coef;
				terms[i].expo = expo;
				return;
			}
			else if (!terms[i].coef) {

				terms[i].coef = coef;
				terms[i].expo = expo;
				return;
			}
		}
		return;
	}
*/
/*
void inputTerms(int coef, int expo)
	{
		LinkedPolynomialTerm* tmpPtr = new LinkedPolynomialTerm;
		LinkedPolynomialTerm* head=polynomialTermPtr;
		LinkedPolynomialTerm* couptr=nullptr;

		tmpPtr->coef = coef;
		tmpPtr->expo = expo;

		if (!polynomialTermPtr) {
			tmpPtr->nextTermPtr = nullptr;
			polynomialTermPtr = tmpPtr;
			return;
		}
		else if (expo > polynomialTermPtr->expo) {
			tmpPtr->nextTermPtr = polynomialTermPtr;
			polynomialTermPtr = tmpPtr;
			return;
		}

		for (;head;head = head->nextTermPtr) {
			if (expo == head->expo) {
				if (coef + head->coef == 0) {
					if ( (!head->nextTermPtr || !head->nextTermPtr->nextTermPtr) && head==polynomialTermPtr)
						polynomialTermPtr = polynomialTermPtr->nextTermPtr;

					else
						for (couptr = polynomialTermPtr;couptr;couptr = couptr->nextTermPtr)
							if (couptr->nextTermPtr == head) {
								head = head->nextTermPtr;
								couptr->nextTermPtr = head;
							}
				}
				else
					head->coef += coef;

				return;
			}
			else if (!head->nextTermPtr ||expo > head->nextTermPtr->expo ) {
				tmpPtr->nextTermPtr = head->nextTermPtr;
				head->nextTermPtr = tmpPtr;
				return;
			}
		}

		return;
	}*/
/*
void printArrayBasedPolyRecursively(int i)
	{
		if (terms[i].coef==0)
			return;
		if (terms[i].expo == 0)
			cout << " + " << terms[i].coef;
		else
			cout << " + " << terms[i].coef << "X^" << terms[i].expo;

		printArrayBasedPolyRecursively(i + 1);
		}*/
/*
void printLinkBasedPolyRecursively(LinkedPolynomialTerm* currPtr)
	{
		if (currPtr) {
			cout << " + ";
			if (currPtr->expo == 0)
				cout << currPtr->coef;
			else
				cout << currPtr->coef << "X^" << currPtr->expo;
			printLinkBasedPolyRecursively(currPtr->nextTermPtr);
		}
	}*/
/*
int computeRecursively(int x, int i)
	{

		if (terms[i].coef == 0)
			return 0;

		return (terms[i].coef * (int)pow(x,terms[i].expo)) + computeRecursively(x, i + 1);

	}*/
/*
int computeRecursively(int x, LinkedPolynomialTerm* currPtr)
	{
		if (!currPtr)
			return 0;

		return (currPtr->coef * (int)pow(x,currPtr->expo)) + computeRecursively(x,currPtr->nextTermPtr);
	}*/