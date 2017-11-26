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
#include<array>
using namespace std;

const int PGCOUNT = 5;

void printRefString(vector<int> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

void printState(vector<int> arr, vector<int> count, int size) {
	for (int i = 0; i < size; ++i) {
		cout << "Frame " << i << ": " << arr[i] << " - " << count[i] << endl;
	}
}
//********************************
//simulaes the least recently used algorithm as it would operate
//in a page/frame scheme
//*************************
void lru(vector<int> frames, int size, vector<int> vec) {
	srand(time(NULL));

	cout << "Least recently used-\nFrames: " << size << "\nreference string: ";
	printRefString(vec);
	vector<int> counter;
	bool fault;
	int index;
	for (int i = 0; i < vec.size(); i++) {
		if (frames.size() < size) {
			frames.push_back(vec[i]);
			cout << "Frame " << i << " initialized with " << vec[i] << endl;
			counter.push_back(0);
			for (int j = 0; j < i; ++j) {
				counter[j]++;
			}
		}else{
			fault = true;
			for (int j = 0; j < size; j++) {
				if (vec[i] == frames[j]) {
					fault = false;
					for (int k = 0; k < size; k++) {
						counter[k]++;
					}
					counter[j] = 0;
					cout << "Page " << vec[i] << " found at location " << j
						<< "\n current status: \n";
					printState(frames, counter, size);
				}
			}

			if (fault) {
				int lastUsed = -1;
				index = 0;
				for (int j = 0; i < size; i++) {
					if (counter[j] > lastUsed) {
						lastUsed = counter[j];
						index = j;
					}
					else if (counter[j] == lastUsed) {
						if (rand() % 2) {
							lastUsed = counter[j];
							index = j;
						}
					}
				}
				cout << "Page fault!- " << frames[index] << " is being replaced with " << vec[i]
					<< " at frame " << index << "\ncurrent status: \n";
				frames[index] = vec[i];
				for (int j = 0; j < size; ++j) {
					counter[j]++;
				}
				counter[index] = 0;
				printState(frames, counter, size);
				cout << endl;
			}
		}
	}
}

void optimal(vector<int> frames, int size, vector<int> vec) {
	cout << "Optimal-\nFrames: " << size << "\nreference string: ";
	printRefString(vec);
	int * counter = new int [size];
}
int main() {
	int frames;
	string reference;
	vector<int> pages;
	vector<int> lruFrames;
	vector<int> optFrames;
	cout << "Input the reference string:\n";
	getline(cin, reference);
	cout << "How many frames?\n";
	cin >> frames;
	
	for (int i = 0; i < reference.size(); i++) {
		if (reference[i] != ' ') {
			pages.push_back(reference[i] - '0');
		}
	}

	lru(lruFrames, frames, pages);
	optimal(optFrames, frames, pages);

	return 0;
}