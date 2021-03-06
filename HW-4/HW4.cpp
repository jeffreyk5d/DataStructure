// HW4.cpp : 定義主控台應用程式的進入點。
//

#include <stdio.h>
#include "memory.h"
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm* nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm*& polynomialTermPtr)
{
	linkedPolynomialTerm* tmpPtr;

	while (polynomialTermPtr != nullptr) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{
	for (int i = 0; i < MAX_TERMS; i++) {

		if (expo == terms[i].expo) {

			if (coef == 0) {
				for (int j = i; j < MAX_TERMS - 1; j++) {
					terms[j].expo = terms[j + 1].expo;
					terms[j].coef = terms[j + 1].coef;
				}
			}
			else {
				terms[i].expo = expo;
				terms[i].coef = coef;
				break;
			}
		}
		else if (expo > terms[i].expo) {
			if (coef == 0)return;
			for (int j = MAX_TERMS; j > i; j--) {
				terms[j].expo = terms[j - 1].expo;
				terms[j].coef = terms[j - 1].coef;
			}
			terms[i].expo = expo;
			terms[i].coef = coef;
			break;
		}

	}
	// add your code here

	return;
}

void inputLinkTerms(linkedPolynomialTerm*& polyPtr, int coef, int expo)
{

	int temp = 0;
	linkedPolynomialTerm* tmpPtr;
	linkedPolynomialTerm* firstptr;
	linkedPolynomialTerm* secptr;
	tmpPtr = new linkedPolynomialTerm;

	tmpPtr->coef = coef;
	tmpPtr->expo = expo;
	tmpPtr->nextTermPtr = nullptr;
	firstptr = nullptr;
	secptr = polyPtr;

	while (secptr != nullptr && secptr->expo >= expo) {

		/*if (coef == 0) {
		if (firstptr == nullptr) {
		polyPtr = secptr->nextTermPtr;
		temp = 1;
		}
		else {
		firstptr->nextTermPtr = secptr->nextTermPtr;
		delete secptr;
		secptr = firstptr;
		temp = 1;

		}
		}*/

		if (secptr->expo == expo) {

			if (coef == 0) {
				if (firstptr == nullptr) {
					firstptr = secptr->nextTermPtr;
					delete secptr;
					secptr = firstptr;
					polyPtr = secptr;
				}
				else {
					firstptr->nextTermPtr = secptr->nextTermPtr;
					delete secptr;
					secptr = firstptr;
					temp = 1;
				}
			}
			else {
				secptr->expo = tmpPtr->expo;
				secptr->coef = tmpPtr->coef;
				temp = 1;
				break;
			}
		}
		else {
			firstptr = secptr;
			secptr = secptr->nextTermPtr;
		}
	}
	if (temp == 0) {
		if (!polyPtr)
		{
			if (coef == 0)return;
			polyPtr = tmpPtr;
			tmpPtr->nextTermPtr = secptr;
		}
		else
		{
			if (coef == 0)return;
			if (firstptr == nullptr) {
				tmpPtr->nextTermPtr = secptr;
				polyPtr = tmpPtr;
			}
			else {
				firstptr->nextTermPtr = tmpPtr;
				tmpPtr->nextTermPtr = secptr;
			}
		}
	}
}


// add your code here 






void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	int ai = 0, bi = 0, di = 0;
	while (1) {
		if (a[ai].coef == 0 && b[bi].coef == 0 && a[ai].expo == 0 && b[bi].expo == 0)break;
		else {
			if (a[ai].expo == b[bi].expo) {
				if (a[ai].coef + b[bi].coef == 0) {
					ai++;
					bi++;
					continue;
				}
				else {
					if (a[ai].expo == 0)
						d[di].expo = b[ai].expo;
					else if (b[bi].expo == 0)
						d[di].expo = a[bi].expo;
					else d[di].expo = a[ai].expo;
					d[di].coef = a[ai].coef + b[bi].coef;
					ai++;
					bi++;
					di++;
				}
			}


			else if (a[ai].expo > b[bi].expo) {
				d[di].expo = a[ai].expo;
				d[di].coef = a[ai].coef;
				ai++;
				di++;
			}
			else if (a[ai].expo < b[bi].expo) {
				d[di].expo = b[bi].expo;
				d[di].coef = b[bi].coef;
				bi++;
				di++;
			}
		}
	}
	// add your code here

	return;
}

linkedPolynomialTerm* addLinkBasedPoly(linkedPolynomialTerm* aPtr, linkedPolynomialTerm* bPtr)
{
	linkedPolynomialTerm* dPtr;
	linkedPolynomialTerm* check = nullptr;
	linkedPolynomialTerm* save;
	save = new linkedPolynomialTerm;
	save->nextTermPtr = nullptr;
	dPtr = nullptr;


	while (1) {
		if (aPtr == nullptr || bPtr == nullptr)break;
		else {
			if (aPtr->expo == bPtr->expo) {
				if (aPtr->coef + bPtr->coef == 0) {
					aPtr = aPtr->nextTermPtr;
					bPtr = bPtr->nextTermPtr;
					//cout << 123;
					continue;
				}
				else {
					if (aPtr->expo == 0)
						save->expo = bPtr->expo;
					else if (bPtr->expo == 0)
						save->expo = aPtr->expo;
					else save->expo = aPtr->expo;
					save->coef = aPtr->coef + bPtr->coef;
					aPtr = aPtr->nextTermPtr;
					bPtr = bPtr->nextTermPtr;
				}
			}
			else if (aPtr->expo > bPtr->expo) {
				save->expo = aPtr->expo;
				save->coef = aPtr->coef;
				aPtr = aPtr->nextTermPtr;
			}

			else if (aPtr->expo < bPtr->expo) {
				save->expo = bPtr->expo;
				save->coef = bPtr->coef;
				bPtr = bPtr->nextTermPtr;
			}
		}
		if (!dPtr) {
			dPtr = check = save;
		}
		else {
			check->nextTermPtr = save;
			check = check->nextTermPtr;
		}

		//check = save;
		save = new linkedPolynomialTerm;
		save->nextTermPtr = nullptr;

	}

	while (aPtr) {
		save = new linkedPolynomialTerm;
		save->expo = aPtr->expo;
		save->coef = aPtr->coef;
		save->nextTermPtr = nullptr;
		aPtr = aPtr->nextTermPtr;
		if (!dPtr) {
			dPtr = check = save;
		}
		else {
			check->nextTermPtr = save;
			check = check->nextTermPtr;
		}
	}
	while (bPtr) {
		save = new linkedPolynomialTerm;
		save->expo = bPtr->expo;
		save->coef = bPtr->coef;
		save->nextTermPtr = nullptr;
		bPtr = bPtr->nextTermPtr;
		if (!dPtr) {
			dPtr = check = save;
		}
		else {
			check->nextTermPtr = save;
			check = check->nextTermPtr;
		}
		//check = save;
	}
	//dPtr->nextTermPtr = check;


	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
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
}

void printLinkBasedPoly(linkedPolynomialTerm* polyPtr)
{
	linkedPolynomialTerm* termPtr = polyPtr;

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
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm* aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear(a); clear(b); clear(d);
		clear(aPtr); clear(bPtr); clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}
