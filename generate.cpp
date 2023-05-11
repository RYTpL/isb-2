#include <iostream>
#include <time.h>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;


vector<int> get_bin_seq() {
	vector<int> result;
	int item = 1;
	srand(time(0));
	for (int i = 0; i < 128; ++i) {
		item = (rand() * item + rand()) % 2;
		result.push_back(item);
	}
	ofstream out;
	out.open("D:\\isb-2\\isb-2\\random sequence.txt");
	if (out.is_open()) {
		for (auto i : result) {
			out << i;
		}
	}
	out.close();
	return result;
}

int main() {
	string str;
	ifstream f("D:\\isb-2\\isb-2\\random sequence.txt");
	if (f.is_open()) {
		while (getline(f,str)) {
			cout << str;
		}
	}
	cout << endl;
	f.close();
}