//#include "stdafx.h"
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

	void inputArrayBasedTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int inputSpot = 0;
		if (coef == 0) {
			return;
		}
		if (terms[0].coef == 0 && terms[0].expo == 0) {
			terms[inputSpot].coef = coef;
			terms[inputSpot].expo = expo;
			return;
		}
		for (; terms[inputSpot].coef != 0 && inputSpot< MAX_TERMS&& expo>=terms[inputSpot].expo; inputSpot++);
		// add your code here 		
		if(terms[inputSpot].coef!=0){
			for (int i = MAX_TERMS - 1; i > inputSpot; i--) {
				terms[i] = terms[i-1];
			}
		}
		terms[inputSpot].coef = coef;
		terms[inputSpot].expo = expo;
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


		// add yor code here
		if (terms[i].coef == 0) {
			return;
		}
		if (terms[i].expo==0) {
			cout << " + " << terms[i].coef;
		}
		else {
			cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}
		
		printArrayBasedPolyRecursively(i+1);
	}

	void ArrayBasedReverse()
	{


		// add yor code here
		int length = 0;
		while (terms[length].coef != 0) {
			length++;
		}					
		int tempCoef=0,tempExpo=0;
		for (int i = 0; i < length / 2; i++) {
			tempCoef = terms[i].coef;
			tempExpo=terms[i].expo ;
			
			terms[i].coef = terms[length - 1 - i].coef;
			terms[i].expo = terms[length - 1 - i].expo;
			
			terms[length - 1 - i].coef=tempCoef;
			terms[length - 1 - i].expo=tempExpo;
		}

	}

	void ArrayBasedIncPower(int expo)
	{


		// add yor code here		

		int length = 0;
		while (terms[length].coef != 0) {
			length++;
		}
		for (int i = 1; i < length; i++) {
			int flag = 0;
			if (terms[i - 1].expo == terms[i].expo) {
				terms[i - 1].coef = terms[i - 1].coef + terms[i].coef;
				if (terms[i - 1].coef == 0) {					
					flag = 1;
				}
				for (int j = i + 1; j <= length; j++) {
					terms[j - 1] = terms[j];
				}
				if (flag == 1) {
					for (int j = i ; j <= length; j++) {
						terms[j - 1] = terms[j];
					}
					length--;
				}
				i--;
				length--;
			}

		}
		for (int i = 0; i < length; i++) {
			if (expo == terms[i].expo) {
				terms[i].expo++;
				break;
			}
		}
		for (int i = 1; i < length; i++) {
			int flag = 0;
			if (terms[i - 1].expo == terms[i].expo) {
				terms[i - 1].coef = terms[i - 1].coef + terms[i].coef;
				if (terms[i - 1].coef == 0) {
					i--;
					flag = 1;
				}
				for (int j = i + 1; j <= length; j++) {
					terms[j - 1] = terms[j];
				}
				if (flag == 1) {
					length--;
				}
				i--;
				length--;
			}

		}

	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkBasedTerms(int coef, int expo)
	{
		LinkedPolynomialTerm *tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;
		if (coef == 0) {
			return;
		}
		if (!polynomialTermPtr) {
			polynomialTermPtr = tmpPtr;
			return;
		}
		// add your code here 
		LinkedPolynomialTerm* currPtr = polynomialTermPtr;
		LinkedPolynomialTerm *prePtr= nullptr;				
		while (expo >= (currPtr->expo)&&currPtr!=nullptr) {			
			prePtr = currPtr;
			currPtr = currPtr->nextTermPtr;
			if (currPtr == nullptr) {
				break;
			}
		}
		tmpPtr->nextTermPtr = currPtr;
		if (prePtr == nullptr) {
			polynomialTermPtr=tmpPtr;
		}
		else {
			prePtr->nextTermPtr = tmpPtr;
		}

		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr;

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

	void printLinkBasedPolyRecursively(LinkedPolynomialTerm *currPtr)
	{


		// add yor code here
		
		if (currPtr == nullptr|| currPtr->coef == 0) {
			return;
		}
		if (currPtr->nextTermPtr == nullptr) {//basecase
			if (currPtr->expo == 0) {
				cout << " + " << currPtr->coef;
			}
			else {
				cout << " + " << currPtr->coef << "X^" << currPtr->expo;
			}
			return;
		}
		if (currPtr->expo == 0) {
			cout << " + " << currPtr->coef ;
		}
		else {
			cout << " + " << currPtr->coef << "X^" << currPtr->expo ;
		}
		
		printLinkBasedPolyRecursively(currPtr->nextTermPtr);

	}

	void LinkBasedReverse()
	{


		// add yor code here
		if (polynomialTermPtr == nullptr|| polynomialTermPtr->nextTermPtr == nullptr) {
			return;
		}		
		LinkedPolynomialTerm* currPtr = polynomialTermPtr;
		LinkedPolynomialTerm* nextPtr = polynomialTermPtr->nextTermPtr;
		LinkedPolynomialTerm* prePtr = nullptr;
		while (nextPtr!=nullptr) {
			nextPtr = currPtr->nextTermPtr;
			currPtr->nextTermPtr = prePtr;
			polynomialTermPtr = currPtr;
			prePtr = currPtr;
			currPtr = nextPtr;
		}		
	}

	void LinkBasedIncPower(int expo)
	{


		// add yor code here
		LinkedPolynomialTerm* currPtr=polynomialTermPtr;
		LinkedPolynomialTerm* prePtr=nullptr;		
		LinkedPolynomialTerm* nextPtr = nullptr;

		//¥ý¦X¨Ö		
		while (currPtr!=nullptr) {
			nextPtr = currPtr->nextTermPtr;
			if (nextPtr != nullptr) {
				while(currPtr->expo == nextPtr->expo) {					
					currPtr->coef = currPtr->coef + nextPtr->coef;
					nextPtr = nextPtr->nextTermPtr;
					currPtr->nextTermPtr = nextPtr;					
					if (currPtr->coef == 0) {
						if (prePtr == nullptr) {
							polynomialTermPtr = nullptr;
							return;
						}
						else {
							currPtr = nextPtr;
							prePtr->nextTermPtr = currPtr;
							if (currPtr != nullptr) {
								nextPtr = nextPtr->nextTermPtr;
							}
							else {
								break;
							}
							if (nextPtr == nullptr) {
								break;
							}
							
						}
						
					}
					if (nextPtr == nullptr) {
						break;
					}
				}
			}
			if (currPtr == nullptr) {
				break;
			}
			prePtr = currPtr;
			currPtr = currPtr->nextTermPtr;
		}
		currPtr = polynomialTermPtr;
		while (currPtr!=nullptr&&expo!=currPtr->expo) {
			currPtr = currPtr->nextTermPtr;
		}
		if (currPtr == nullptr) {
			return;
		}
		currPtr->expo = currPtr->expo +1;
		while (currPtr != nullptr) {
			nextPtr = currPtr->nextTermPtr;
			if (nextPtr != nullptr) {
				while (currPtr->expo == nextPtr->expo) {
					currPtr->coef = currPtr->coef + nextPtr->coef;
					nextPtr = nextPtr->nextTermPtr;
					currPtr->nextTermPtr = nextPtr;
					if (currPtr->coef == 0) {
						if (prePtr == nullptr) {
							polynomialTermPtr = nullptr;
							return;
						}
						else {
							currPtr = nextPtr;
							prePtr->nextTermPtr = currPtr;


							if (currPtr != nullptr) {
								nextPtr = nextPtr->nextTermPtr;
							}
							else {
								break;
							}
							if (nextPtr == nullptr) {
								break;
							}

						}

					}
					if (nextPtr == nullptr) {
						break;
					}
				}
			}
			if (currPtr == nullptr) {
				break;
			}
			prePtr = currPtr;
			currPtr = currPtr->nextTermPtr;
		}

	}
};
