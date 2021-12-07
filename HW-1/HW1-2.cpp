#include "stdafx.h"
#include<stdlib.h>
#include <iostream>

using namespace std;
struct node {
	int item;
	struct node* next;
};
typedef struct node n;
n* input(n* ptr, int number) {
	n* newnode = (n*)malloc(sizeof(n));
	newnode->next = nullptr;
	newnode->item = number;
	if (ptr == nullptr) {
		ptr = newnode;
		return ptr;
	}

	n* run = ptr;
	n* pre = ptr;
	if (number < run->item) {
		newnode->next = ptr;
		return newnode;
	}
	else {

		while (run) {
			if (number< run->item) {
				break;
			}
			pre = run;
			run = run->next;
		}
		newnode->next = run;
		pre->next = newnode;
		return ptr;
	}
}
n* deletenum(n* ptr, int number) {
	if (!ptr) {
		cout << "error" << endl;
		return ptr;
	}

	int f = 0;
	int flag = 0;
	n* curr = nullptr;
	curr = ptr;
	n* pre = nullptr;
	pre = ptr;
	while (ptr->item == number) {
		if (ptr->next == nullptr) {
			f = 1;
			ptr = nullptr;
			break;
		}
		ptr = ptr->next;
	}
	if (f == 1) {
		return ptr;
	}
	/*while (ptr->item == number) {
	ptr = ptr->next;
	ff = 1;
	}
	if (ff==1) {
	return ptr;
	}*/
	curr = ptr;
	while (curr) {
		if (curr->item == number) {
			flag = 1;
			pre->next = curr->next;
			//free(curr);
			delete curr;
			curr = pre;
		}
		pre = curr;
		curr = curr->next;
	}
	if (flag == 0) {
		cout << "this number doesn't exist" << endl;
	}
	return ptr;
}
void printList(n* ptr) {
	if (!ptr) {
		cout << "nothing" << endl;
	}
	n* run;
	run = ptr;
	while (run != nullptr) {
		cout << run->item << " ";
		run = run->next;
	}
	cout << "\n";
}
int main()
{
	int jump = 0;
	n* head = nullptr;
	while (1) {
		char action;
		int num;
		cout << "Input or Delete?(J to Exit)";
		cin >> action;
		switch (action) {
		case 'I':
		case 'i':
			cout << "Input an integer:";
			cin >> num;
			head = input(head, num);
			break;
		case 'D':
		case 'd':
			cout << "Input an integer:";
			cin >> num;
			head = deletenum(head, num);
			break;
		case 'J':
		case 'j':
			jump = 1;
			break;
		default:
			cout << "ERROR\n";
			continue;
		}
		if (jump == 1)
			break;
		printList(head);

	}
}
