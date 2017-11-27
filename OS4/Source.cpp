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

void printState(vector<int> frames, vector<int> count) {
	for (int i = 0; i < frames.size(); ++i) {
		cout << "Frame " << i << ": page- " << frames[i] << " time last used- " << count[i] << endl;
	}
	cout << endl;
}
//********************************
//simulates the least recently used algorithm as it would operate
//in a page/frame scheme
//*************************
int lru(int size, vector<int> pages) {
	
	vector<int> frames;
	cout << "Least recently used-\nFrames: " << size << "\nreference string: ";
	printRefString(pages);
	vector<int> counter;
	bool fault;
	int index;
	int faultcount = 0;
	for (int i = 0; i < pages.size(); i++) {
		if (frames.size() < size) {
			frames.push_back(pages[i]);
			cout << "Frame " << i << " initialized with " << pages[i] << endl;
			counter.push_back(0);
			for (int j = 0; j < i; ++j) {
				counter[j]++;
			}
			cout << "current status: \n";
			printState(frames, counter);
		}else{
			fault = true;
			for (int j = 0; j < size; j++) {
				if (pages[i] == frames[j]) {
					fault = false;
					for (int k = 0; k < size; k++) {
						counter[k]++;
					}
					counter[j] = 0;
					cout << "Page " << pages[i] << " found at location " << j
						<< "\n current status: \n";
					printState(frames, counter);
				}
			}

			if (fault) {
				int lastUsed = -1;
				index = 0;
				for (int j = 0; j < size; ++j) {
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
				cout << "Page fault!- " << frames[index] << " is being replaced with " << pages[i]
					<< " at frame " << index << "\ncurrent status: \n";
				frames[index] = pages[i];
				for (int j = 0; j < size; ++j) {
					counter[j]++;
				}
				counter[index] = 0;
				printState(frames, counter);
				faultcount++;
			}
		}
	}
	return faultcount;
}

vector<int> mapping(vector<int> frames, vector<int> pages, int start) {
	vector<int> distance;
	for (int frameit = 0; frameit < frames.size(); ++frameit) {
		distance.push_back(4096);
		for (int i = start; i < pages.size(); ++i) {
			if (distance[frameit] == 4096 && frames[frameit] == pages[i]) {
				distance[frameit] = i - start;
			}
		}
	}
	return distance;
}

int optimal(int size, vector<int> pages) {
	cout << "Optimal-\nFrames: " << size << "\nreference string: ";
	printRefString(pages);
	int faultcount = 0;
	vector<int> frames;
	vector<int> distance;
	int furthest;
	int index;
	bool fault;
	for (int i = 0; i < pages.size(); i++) {
		if (frames.size() < size) {
			frames.push_back(pages[i]);
			cout << "Frame " << i << " initialized with " << pages[i] << endl;
		}
		else {
			fault = true;
			for (int j = 0; j < size; j++) {
				if (pages[i] == frames[j]) {
					fault = false;
					cout << "Page " << pages[i] << " found at frame " << j << endl;
				}
			}
			if (fault) {
				distance.clear();
				distance = mapping(frames, pages, i + 1);
				furthest = -1;
				index = i + 1;
				for (int distit = 0; distit < distance.size(); ++distit) {
					if (distance[distit] > furthest) {
						index = distit;
						furthest = distance[distit];
					}
					else if (distance[distit] == furthest) {
						if (rand() % 2) {
							index = distit;
							furthest = distance[distit];
						}
					}
				}
				cout << "Page fault!- " << frames[index] << " is being replaced at location "
					<< index << endl;
				faultcount++;
			}
		}
		
	}
	return faultcount;
}

int main() {
	srand(time(NULL));
	
	int frames;
	string reference;
	vector<int> pages;
	//vector<int> lruFrames;
	//vector<int> optFrames;
	cout << "Input the reference string:\n";
	getline(cin, reference);
	cout << "How many frames?\n";
	cin >> frames;
	
	for (int i = 0; i < reference.size(); i++) {
		if (reference[i] != ' ') {
			pages.push_back(reference[i] - '0');
		}
	}

	int lrucount = lru(frames, pages);
	cout << endl << endl;
	int optcount = optimal(frames, pages);

	cout << "\nLRU had " << lrucount << " page faults.\n";
	cout << "Optimal had " << optcount << " page faults.";
	return 0;
}