#include <string>
#include "stdafx.h"
#include <iostream>
using namespace std;

void input(string sMessage, string& sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;

	return;
}

void writeBackwardI(string s)
{
	int length = s.size();

	if (length == 0)  // base case 
		return;

	for (int i = length - 1; i >= 0; i--)
		cout << s[i];
}

void writeBackwardR1(string s)
{
	int length = s.size();

	if (length == 0)  // base case 
		return;

	cout << s[length - 1];
	writeBackwardR1(s.substr(0, length - 1));
}

void writeBackwardR2(string s)
{
	int length = s.size();

	if (length == 0)  // base case 
		return;

	writeBackwardR2(s.substr(1, length - 1));
	cout << s[0];
}


int countI(string s, char c)
{
	int length = s.size();
	int i = 0;
	int count = 0;
	while (i < length) {
		if (c == s[i]) {
			count++;
		}
		i++;
	}
	return count;
}

int countR(string s, char c)
{
	int length = s.size();
	int count = 0;
	if (length > 1) {
		count += countR(s.substr(1, length - 1), c);
	}
	if (c == s[0]) {
		count++;
	}
	return count;
}

unsigned char findI(string s)
{
	int length = s.size();
	int i = 0;
	while (i < length) {
		if (s[0] >= s[i]) {
			s[0] = s[i];
		}
		i++;
	}
	return s[0];
}

char findR(string s)
{
	int length = s.size();
	if (length == 0) {
		cout << "not a string";
		return 0;
	}
	else if (length == 1) {
		return s[0];
	}
	else if (length>1) {
		if (s[0] > s[length - 1]) {
			return findR(s.substr(1, length - 1));
		}
		else {
			return findR(s.substr(0, length - 1));
		}
	}
}

string removeI(string s)
{
	int length = s.size();
	int combine = 0;
	if (length == 0) {
		cout << "not a string!\n";
		return s;
	}
	else if (length == 1) {
		return s;
	}
	else if (length>1) {
		for (int i = 0; i < length - 1; i++) {
			if (s[i] == s[i + 1]) {
				for (int j = i; j < length - 1; j++) {
					s[j] = s[j + 1];
				}
				i--;
				length--;
			}
		}
		return s.substr(0, length);
	}
}

string removeR(string s)
{
	int length = s.size();
	string temp;
	if (length == 0) {
		cout << "not a string!!\n";
		return s;
	}
	else if (length == 1) {
		return s;
	}
	else if (length > 1) {
		temp = removeR(s.substr(1, length - 1));
		if (s[0] == s[1]) {
			return temp;
		}
	}
	temp = s[0] + temp;
	return temp;
}

int TI(int m, int n)
{
	int total = 0;
	if (m == 0 || n == 0) {
		total = 0;
	}
	else if (m > n) {
		for (int i = 0; i < n; i++) {
			total += m;
		}
	}
	else if (m <= n) {
		for (int i = 0; i < m; i++) {
			total += n;
		}
	}


	/*
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + ... + m (n times), if m > n
	T(m, n) =  n + ... + n (m times), otherwise
	*/

	return total;
}

int TR(int m, int n)
{
	int total = 0;
	if (m > n) {
		if (n == 0) {
			return total;
		}
		total = TR(m, n - 1) + m;
	}
	else {
		if (m == 0) {
			return total;
		}
		total = TR(m - 1, n) + n;
	}
	/*
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + T( m, n - 1 ), if m > n
	T(m, n) =  n + T( m - 1, n ), otherwise
	*/
	return total;
}

int main()
{
	string commandStr;
	string inputStr, appendStr;
	char inputChr;
	int m, n;

	while (1) {
		input("\nEnter command: "
			"\n I to input a string, A to append a string, B to write the string backward, "
			"\n C to count the given character , F to find the smallest character,"
			"\n R to remove the repeated characters, T to compute, and X to Exit", commandStr);

		if (commandStr == "I" || commandStr == "i") {
			cout << "\nInput the string: ";
			cin >> inputStr;
		}
		else if (commandStr == "A" || commandStr == "a") {
			cout << "\nInput the string: ";
			cin >> appendStr;
			inputStr += appendStr;
			cout << "\nThe new string: " << inputStr << endl;
		}
		else if (commandStr == "B" || commandStr == "b") {
			if (inputStr.length() > 0) {
				cout << endl;
				writeBackwardI(inputStr);
				cout << endl;
				writeBackwardR1(inputStr);
				cout << endl;
				writeBackwardR2(inputStr);
				cout << endl;
			}
		}
		else	if (commandStr == "C" || commandStr == "c") {
			if (inputStr != "") {
				cout << "\nInput the character: ";
				cin >> inputChr;
				cout << "\nCount of " << inputChr << ": " << countI(inputStr, inputChr);
				cout << "\nCount of " << inputChr << ": " << countR(inputStr, inputChr) << endl;
			}
		}
		else if (commandStr == "R" || commandStr == "r") {
			if (inputStr != "") {
				cout << endl << "Repeated characters removed: " << removeI(inputStr);
				cout << endl << "Repeated characters removed: " << removeR(inputStr) << endl;;
			}
		}
		else if (commandStr == "F" || commandStr == "f") {
			if (inputStr != "") {
				cout << endl << "Smallest character found: " << findI(inputStr);
				cout << endl << "Smallest character found: " << findR(inputStr) << endl;
			}
		}
		else  if (commandStr == "T" || commandStr == "t")
		{
			cout << "\nInput two values, m and n: ";
			cin >> m >> n;
			cout << endl << "The result is " << TI(m, n);
			cout << endl << "The result is " << TR(m, n) << endl;
		}
		else  if (commandStr == "X" || commandStr == "x")
			return 0;
		else
			cout << "\nUnknown command!";
	}
	return 0;
}