#include "stdafx.h"
#include <iostream>
using namespace std;
#include <math.h>

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};                                                                          /////

class ArrayPolynomial {                                        /////
public:                                                                  /////
	PolynomialTerm terms[MAX_TERMS]; /////

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) /////
	{

		// add your code here
		int input_posi = 0;
		if (terms[0].coef == 0 && terms[0].expo == 0) {							//新增首項
			terms[0].coef = coef;
			terms[0].expo = expo;
			return;
		}
		else {
			while (expo < terms[input_posi].expo) {
				input_posi++;
			}
			if (terms[input_posi].coef == 0 && terms[input_posi].expo == 0) { // end
				terms[input_posi].coef = coef;
				terms[input_posi].expo = expo;
				return;
			}

			if (terms[input_posi].expo == expo) {
				/*for (int i = MAX_TERMS - 2; i >= input_posi; i--) {									//移動每個項以藤出空間 填入新的項
					terms[i + 1] = terms[i];
				}*/
				if (coef == 0) {
					for (int i = input_posi; i<MAX_TERMS-1; i++) {							//全部前移 補刪掉的空洞
						terms[i] = terms[i + 1];
					}
				}
				else {
					terms[input_posi] = { coef,expo };
				}
				return;
			}
			for (int i = MAX_TERMS - 2; i >= input_posi; i--) {									//移動每個項以藤出空間 填入新的項
				terms[i + 1] = terms[i];
			}
			terms[input_posi].coef = coef;
			terms[input_posi].expo = expo;
		}
		return;
	}

	void addArrayBasedPoly(ArrayPolynomial& a, ArrayPolynomial& b) /////
	{
		// add your code here
		int a_posi = 0;
		int b_posi = 0;
		int d_posi = 0;
		while (a.terms[a_posi].coef != 0 && b.terms[b_posi].coef != 0 && d_posi <= MAX_TERMS) {
			if (a.terms[a_posi].expo > b.terms[b_posi].expo) {
				terms[d_posi] = { a.terms[a_posi].coef,a.terms[a_posi].expo };
				a_posi++;
				d_posi++;
			}
			if (b.terms[a_posi].expo > a.terms[b_posi].expo) {
				terms[d_posi] = { b.terms[b_posi].coef,b.terms[b_posi].expo };
				b_posi++;
				d_posi++;
			}
			if (a.terms[a_posi].expo == b.terms[b_posi].expo) {
				if ((a.terms[a_posi].coef + b.terms[b_posi].coef) != 0) {
					terms[d_posi] = { a.terms[a_posi].coef + b.terms[b_posi].coef,a.terms[a_posi].expo };
					a_posi++;
					b_posi++;
					d_posi++;
				}
				else {
					a_posi++;
					b_posi++;
				}
			}
		}
		while (a.terms[a_posi].coef != 0 && d_posi <= MAX_TERMS) {
			terms[d_posi] = { a.terms[a_posi].coef,a.terms[a_posi].expo };
			a_posi++;
			d_posi++;
		}
		while (b.terms[b_posi].coef != 0 && d_posi <= MAX_TERMS) {
			terms[d_posi] = { b.terms[b_posi].coef,b.terms[b_posi].expo };
			b_posi++;
			d_posi++;
		}
		return;
	}

	void reverseArrayBasedPoly() /////
	{

		// add your code here
		int count = 0;
		PolynomialTerm tmp;
		while (terms[count].coef != 0) {
			count++;
		}
		for (int i = 0; i < (count / 2); i++) {
			tmp = terms[i];
			terms[i] = terms[count - 1 - i];
			terms[count - 1 - i] = tmp;
		}
		return;
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x)
	{
		// add your code here
		int total = 0;
		int count = 0;
		while (terms[count].coef != 0) {
			count++;
		}
		for (int i = 0; i < count; i++) {
			total += terms[i].coef * pow(x, terms[i].expo);
		}
		return total;
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm* nextTermPtr; /////
};                                                                  /////

class LinkPolynomial {                                /////
public:                                                          /////
	LinkedPolynomialTerm* polynomialTermPtr = nullptr; /////

	void clear() /////
	{
		LinkedPolynomialTerm* tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{
		LinkedPolynomialTerm* tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;


		// add your code here 		
		LinkedPolynomialTerm* pre_posi;
		LinkedPolynomialTerm* cur_posi;
		tmpPtr->nextTermPtr = nullptr;
		if (!polynomialTermPtr) {
			polynomialTermPtr = tmpPtr;
			if (polynomialTermPtr->coef == 0) {									//首相係數為零，移動首項，使其被刪除
				polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			}
			return;
		}
		pre_posi = polynomialTermPtr;

		while (pre_posi->nextTermPtr) {											//找位置
			if (expo >= pre_posi->nextTermPtr->expo) {
				break;
			}
			pre_posi = pre_posi->nextTermPtr;
		}
		if (!pre_posi->nextTermPtr && expo < pre_posi->expo) {											//若為末項直接填入
			pre_posi->nextTermPtr = tmpPtr;
			return;
		}
		if (pre_posi == polynomialTermPtr && expo >= pre_posi->expo) {									//若為首項，處理方法不同			
			if (pre_posi->expo == expo) {
				tmpPtr->nextTermPtr = pre_posi->nextTermPtr;
				polynomialTermPtr = tmpPtr;
				if (polynomialTermPtr->coef == 0) {											//首項係數為零，移動首項，使其被刪除				
					polynomialTermPtr = polynomialTermPtr->nextTermPtr;
					return;
				}
				else {
					return;
				}
			}
			if (pre_posi->coef == 0) {											//首項係數為零，移動首項，使其被刪除				
				polynomialTermPtr = polynomialTermPtr->nextTermPtr;
				return;
			}
			else {
				tmpPtr->nextTermPtr = polynomialTermPtr;
				polynomialTermPtr = tmpPtr;
				if (polynomialTermPtr->coef == 0) {											//首項係數為零，移動首項，使其被刪除				
					polynomialTermPtr = polynomialTermPtr->nextTermPtr;
					return;
				}
			}
			return;
		}

		if (expo == pre_posi->nextTermPtr->expo) {								//一般次方相等的情況												
			if (coef == 0) {													//次方相等又係數0的情況
				pre_posi->nextTermPtr = pre_posi->nextTermPtr->nextTermPtr;
				return;
			}
			else {																//以新輸入取代
				tmpPtr->nextTermPtr = pre_posi->nextTermPtr->nextTermPtr;
				pre_posi->nextTermPtr = tmpPtr;
				return;
			}
		}

		tmpPtr->nextTermPtr = pre_posi->nextTermPtr;               //若非以上特例時執行
		pre_posi->nextTermPtr = tmpPtr;
		return;
	}

	void addLinkBasedPoly(LinkPolynomial& aPol, LinkPolynomial& bPol) /////
	{
		/////
		// add your code here
		LinkedPolynomialTerm* pre_posi;
		LinkedPolynomialTerm* a_posi, *b_posi;
		a_posi = aPol.polynomialTermPtr;
		b_posi = bPol.polynomialTermPtr;
		pre_posi = polynomialTermPtr;
		while (a_posi && b_posi) {
			if (a_posi->expo > b_posi->expo) {
				if (!polynomialTermPtr) {
					polynomialTermPtr = pre_posi = new LinkedPolynomialTerm{ a_posi->coef,a_posi->expo };
					a_posi = a_posi->nextTermPtr;
				}
				else {
					pre_posi->nextTermPtr = new LinkedPolynomialTerm{ a_posi->coef,a_posi->expo };
					a_posi = a_posi->nextTermPtr;
					pre_posi = pre_posi->nextTermPtr;
				}
			}
			else if (b_posi->expo > a_posi->expo) {
				if (!polynomialTermPtr) {
					polynomialTermPtr = pre_posi = new LinkedPolynomialTerm{ b_posi->coef,b_posi->expo };
					b_posi = b_posi->nextTermPtr;
				}
				else {
					pre_posi->nextTermPtr = new LinkedPolynomialTerm{ b_posi->coef,b_posi->expo };
					b_posi = b_posi->nextTermPtr;
					pre_posi = pre_posi->nextTermPtr;
				}
			}
			else if (a_posi->expo == b_posi->expo) {
				if ((a_posi->coef + b_posi->coef) != 0) {
					if (!polynomialTermPtr) {
						polynomialTermPtr = pre_posi = new LinkedPolynomialTerm{ a_posi->coef + b_posi->coef,b_posi->expo };
						b_posi = b_posi->nextTermPtr;
						a_posi = a_posi->nextTermPtr;
					}
					else {
						pre_posi->nextTermPtr = new LinkedPolynomialTerm{ a_posi->coef + b_posi->coef,a_posi->expo };
						b_posi = b_posi->nextTermPtr;
						a_posi = a_posi->nextTermPtr;
						pre_posi = pre_posi->nextTermPtr;
					}
				}
				else {
					a_posi = a_posi->nextTermPtr;
					b_posi = b_posi->nextTermPtr;
				}

			}
		}
		while (a_posi) {
			if (!polynomialTermPtr) {
				polynomialTermPtr = pre_posi = new LinkedPolynomialTerm{ a_posi->coef,a_posi->expo };
				a_posi = a_posi->nextTermPtr;
			}
			else {
				pre_posi->nextTermPtr = new LinkedPolynomialTerm{ a_posi->coef,a_posi->expo };
				pre_posi = pre_posi->nextTermPtr;
				a_posi = a_posi->nextTermPtr;
			}
		}
		while (b_posi) {
			if (!polynomialTermPtr) {
				polynomialTermPtr = pre_posi = new LinkedPolynomialTerm{ b_posi->coef,b_posi->expo };
				b_posi = b_posi->nextTermPtr;
			}
			else {
				pre_posi->nextTermPtr = new LinkedPolynomialTerm{ b_posi->coef,b_posi->expo };
				pre_posi = pre_posi->nextTermPtr;
				b_posi = b_posi->nextTermPtr;
			}
		}

		return;
	}

	void reverseLinkBasedPoly() /////
	{
		/////


		// add your code here
		LinkedPolynomialTerm* pre_posi;
		LinkedPolynomialTerm* cur_posi;
		LinkedPolynomialTerm* next_posi;
		pre_posi = polynomialTermPtr;
		int first = 1;
		if (!polynomialTermPtr) {
			return;
		}
		if (polynomialTermPtr->nextTermPtr) {
			cur_posi = polynomialTermPtr->nextTermPtr;
		}
		else {
			return;
		}
		while (cur_posi) {
			if (first) {
				polynomialTermPtr->nextTermPtr = pre_posi->nextTermPtr = nullptr;
			}
			next_posi = cur_posi->nextTermPtr;
			cur_posi->nextTermPtr = pre_posi;
			polynomialTermPtr = cur_posi;
			pre_posi = cur_posi;
			cur_posi = next_posi;
			if (!next_posi) {
				break;
			}
			if (next_posi->nextTermPtr) {
				next_posi = next_posi->nextTermPtr;
			}
			first = 0;
		}
		return;
	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm* termPtr = polynomialTermPtr; /////

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

	int compute(int x)
	{



		// add your code here
		LinkedPolynomialTerm* posi;
		posi = polynomialTermPtr;
		int total = 0;
		while (posi) {
			total += (posi->coef) * pow(x, posi->expo);
			posi = posi->nextTermPtr;
		}

		return total;
	}
};

int main()
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;

	// aPtr = bPtr = dPtr = nullptr; /////

	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////
																			// aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////

		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}
