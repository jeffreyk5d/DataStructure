#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

#define MAX 5

struct Node
{
	int item;
	Node* next;
};

typedef Node* nodePtr;

Node* inputData(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;

	nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
	tmpPtr->item = num;
	tmpPtr->next = NULL;

	if (headPtr == NULL)
		return tmpPtr;
	else {
		while (currentPtr->next != NULL)
			currentPtr = currentPtr->next;

		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

void printArrayForward(int A[])
{
	int p = 0;
	while (p <MAX) {
		printf("%3d", A[p++]);
	}
	return;
}


void printArrayBackward(int A[], int i)
{
	if (i == MAX - 1) {
		printf("%3d", A[i]);
		return;
	}
	else {
		printArrayBackward(A, i + 1);
	}
	printf("%3d", A[i]);
	return;
}

void printListForward(nodePtr ptr)
{
	nodePtr run;
	run = ptr;
	while (run != NULL) {
		printf("%3d", run->item);
		run = run->next;
	}
	return;
}

void printListBackward(nodePtr ptr)
{
	nodePtr run;
	run = ptr;
	if (run->next == NULL) {
		printf("%3d", run->item);
		return;
	}
	else {
		printListBackward(run->next);
	}
	printf("%3d", run->item);
}

int main()
{
	int num;
	int A[MAX] = { 0 };
	nodePtr headPtr = NULL;

	printf("Input %d numbers: ", MAX);

	for (int i = 0; i < MAX; i++) {
		cin >> num;
		A[i] = num;
		headPtr = inputData(num, headPtr);
	}

	printf("\nArray Forward Iteratively:  ");
	printArrayForward(A);
	printf("\nArray Backward Recursively: ");
	printArrayBackward(A, 0);

	printf("\nList Forward Iteratively:  ");
	printListForward(headPtr);
	printf("\nList Backward Recursively: ");
	printListBackward(headPtr);

	printf("\n");
	system("PAUSE");
	return 0;
}