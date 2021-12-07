// HW3.cpp : 定義主控台應用程式的進入點。
//

//#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAX_TERMS 10

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if (t[0].coef == 0)
		return;

	if (t[0].expo == 0)
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for (int i = 1; i < MAX_TERMS; i++) {
		if (t[i].coef == 0)
			return;

		if (t[i].expo == 0)
			cout << " + " << t[i].coef;
		else
			cout << " + " << t[i].coef << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo)
{
	if (t[0].coef == 0) {
		t[0].coef = coef;
		t[0].expo = expo;
	}
	else {
		for (int i = 0; i < MAX_TERMS; i++) {	//整個t陣列
			if (expo == t[i].expo) {				//同expo後input的取代前input
				t[i].coef = coef;
				t[i].expo = expo;
				break;
			}
			else if (expo > t[i].expo) {
				for (int j = MAX_TERMS - 1; j >= i; j--) { //全部往後移
					t[j + 1].coef = t[j].coef;
					t[j + 1].expo = t[j].expo;
				}
				t[i].coef = coef;
				t[i].expo = expo;
				break;
			}
			else if (expo < t[i].expo && t[i + 1].coef == 0) {
				t[i + 1].coef = coef;
				t[i + 1].expo = expo;
				break;
			}

		}

	}
	return;
}

void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])//將a和b加起來放入d
{
	int a_posi = 0;																  //紀錄a已放入d資料的位置
	int b_posi = 0;																  //紀錄b已放入d資料的位置
	int d_posi = 0;																  //紀錄d已被放入的位置
	while (a[a_posi].coef != 0 || a[a_posi].expo != 0 || b[b_posi].coef != 0 || b[b_posi].expo != 0) {
		if (a[a_posi].expo == b[b_posi].expo) {
			if ((a[a_posi].coef + b[b_posi].coef) != 0) {
				d[d_posi].coef = a[a_posi].coef + b[b_posi].coef;
				d[d_posi].expo = a[a_posi].expo;
				d_posi++;
				b_posi++;
				a_posi++;
			}
			else {
				b_posi++;
				a_posi++;
			}
		}
		else if (a[a_posi].expo>b[b_posi].expo) {
			d[d_posi].coef = a[a_posi].coef;
			d[d_posi].expo = a[a_posi].expo;
			d_posi++;
			a_posi++;
		}
		else if (a[a_posi].expo < b[b_posi].expo) {
			d[d_posi].coef = b[b_posi].coef;
			d[d_posi].expo = b[b_posi].expo;
			d_posi++;
			b_posi++;
		}
		if (a[a_posi].coef == 0 && a[a_posi].expo == 0) {
			while (b[b_posi].coef != 0 || b[b_posi].expo != 0) {
				d[d_posi].coef = b[b_posi].coef;
				d[d_posi].expo = b[b_posi].expo;
				d_posi++;
				b_posi++;
			}
		}
		if (b[b_posi].coef == 0 && b[b_posi].expo == 0) {
			while (a[a_posi].coef != 0 || a[a_posi].expo != 0) {
				d[d_posi].coef = a[a_posi].coef;
				d[d_posi].expo = a[a_posi].expo;
				d_posi++;
				a_posi++;
			}
		}
	}




	return;
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear(a); clear(b); clear(d);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(a, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(b, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);
		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);
		cout << "\n";
	}

	return 0;
}