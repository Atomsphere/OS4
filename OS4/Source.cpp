/*Lab 4
Write a program that takes a reference string and the number
of frames as inputs to simulate page replacement algorithms.
Suppose the maximum length of a reference string is 30 and
there are 5 diffent numbers of pages. Randomly enter a reference
string through the keyboard, e.g. 2 1 3 4 5 2 3 ..., and enter the
number of frames as inputs. Compare the number of page faults generated
by the Optimal and LRU algorithms.  If there is a tie, randomly choose
one to break the tie. Print out the page replacement process and
you can see how LRU differs from the optimal. */

#include<iostream>
#include<string>
#include<vector>
#include "stdlib.h"
#include<cmath>
#include<time.h>
using namespace std;

const int PGCOUNT = 5;

void printRefString(vector<int> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}
//********************************
//simulaes the least recently used algorithm as it would operate
//in a page/frame scheme
//*************************
void lru(int arr[], int size, vector<int> vec) {
	srand(time(NULL));

	cout << "Least recently used-\nFrames: " << size << "\nreference string: ";
	printRefString(vec);
	int * counter = new int[size];
	counter = { 0 };
	bool fault;
	for (int i = 0; i < vec.size(); i++) {
		fault = true;
		for (int j = 0; j < size; j++) {
			if (vec[i] == arr[j]) {
				fault = false;
				for (int k = 0; k < size; k++) {
					counter[k]++;
				}
				counter[j] = 0;
			}
		}

		if (fault) {
			int smallest = 40;
			int index = 0;
			for (int j = 0; i < size; i++) {
				if (counter[j] < smallest) {
					smallest = counter[j];
					index = j;
				}
				else if (counter[j] == smallest) {
					if (rand() % 2) {
						smallest = counter[j];
						index = j;
					}
				}
			}
			cout << "Page fault!- " << arr[j] << " is being replaced with " << vec[i]
				<< " at frame " << j;
			arr[j] = vec[i];
		}
	}
}

void optimal(int arr[], int size, vector<int> vec) {
	cout << "Optimal-\nFrames: " << size << "\nreference string: ";
	printRefString(vec);
	int * counter = new int [size];
}
int main() {
	int frames;
	string reference;
	vector<int> pages;
	int *lruFrames;
	int *optFrames;
	cout << "Input the reference string:\n";
	getline(cin, reference);
	cout << "How many frames?\n";
	cin >> frames;
	lruFrames = new int[frames];
	optFrames = new int[frames];
	lruFrames = { 0 };
	optFrames = { 0 };
	for (int i = 0; i < reference.size(); i++) {
		if (reference[i] != ' ') {
			pages.push_back(reference[i] - '0');
		}
	}

	lru(lruFrames, frames, pages);
	optimal(optFrames, frames, pages);

}