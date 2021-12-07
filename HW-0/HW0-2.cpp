using namespace std;
#define MAX 50
#include <iostream>
int main() {
	int A[MAX] = { 0 };
	int place = 0;
	//char tag[MAX] = { 0 };
	while (1) {
		char command;
		int jump = 0;
		int p = 0;
		int number = 0;
		int flag = 0;
		cout << "Input or Delete?(J to End)";
		cin >> command;
		switch (command) {
		case 'I':
			cout << "Input an integer? ";
			cin >> number;
			if (place == 0) {
				A[0] = number;

			}
			else {
				if (number <= A[0]) {
					p = 0;
				}
				else {
					for (int i = 0; i < place; i++) {

						if (number > A[i]) {
							p = i;
						}
					}
					p++;
				}

				for (int i = place + 1; i > p; i--)
					A[i] = A[i - 1];

				A[p] = number;
			}
			place++;
			break;
		case'D':
			cout << "Delete which integer ";
			cin >> number;
			for (int i = 0; i < place; i++) {
				if (number == A[i]) {
					p = i;
					flag = 1;					
				}
				if (flag == 1) {
					for (int i = p; i < place; i++) {
						A[i] = A[i + 1];
					}
					place--;
					i--;
					flag = 0;
				}

			}
			
			break;
		case 'J':
			jump = 1;
			break;
		}
		for (int i = 0; i < place; i++) {
			cout << "  " << A[i];
		}
		cout << "\n";
		if (jump == 1) {
			break;
		}
	}
}