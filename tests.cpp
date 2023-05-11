#include <iostream>
#include <time.h>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

double freq_test(const vector<int>& seq) {
	double sum = 0;
	for (int i = 0; i < seq.size(); ++i) {
		if (seq[i] == 1) ++sum;
		else --sum;
	}
	sum = sum / sqrt(seq.size());
	double res = erfc(sum / sqrt(2));
	return res;
}

double ident_bits(const vector<int>& seq) {
	double psi = 0;
	int N = seq.size();
	for (auto i : seq) psi += i;
	psi /= N;
	if (!(abs(psi - 0.5) < (2 / sqrt(N)))) return 0;
	int v = 0;
	for (int i = 0; i < N - 1; ++i) {
		if (seq[i] != seq[i + 1]) ++v;
	}
	double chisl = abs(v - N * psi * (1 - psi) * 2);
	double znam = 2 * sqrt(2 * N) * psi * (1 - psi);
	double res = erfc(chisl / znam);
	return res;
}

double largest_ones(const vector<int>& seq) {
	int N = seq.size(), M = 8;
	int index = 0;
	vector<int> count_ones;
	while (index != 128) {
		vector<int> tmp;
		for (int i = index; i < index + 8; ++i) {
			tmp.push_back(seq[i]);
		}
		int len = 0, count = 0, max = 0;
		for (auto i : tmp) {
			if (i == 1) ++count;
			else {
				if (count > max) max = count;
				count = 0;
			}
		}
		len = max;
		count_ones.push_back(len);
		index += 8;
	}

	int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
	for (auto i : count_ones) {
		if (i <= 1) ++v1;
		if (i == 2) ++v2;
		if (i == 3) ++v3;
		if (i >= 4) ++v4;
	}
	vector<int> v = { v1, v2, v3, v4 };
	vector<double> p = { 0.2148, 0.3672, 0.2305, 0.1875 };
	double x2 = 0;
	for (int i = 0; i < 4; ++i) {
		x2 += (pow((v[i] - 16 * p[i]), 2) / (16 * p[i]));
	}
	return x2;
}

int main() {
    vector<int> bit_seq;
    string str;
	for (int i = 0; i < 128; ++i) {
		string s (1, str[i]);
		bit_seq.push_back(stoi(s));
	}
	for (auto i : bit_seq) cout << i;
	cout << endl << bit_seq.size() << endl;
	double first_test = freq_test(bit_seq);
	cout << "First test: " << first_test << endl;
	double second_test = ident_bits(bit_seq);
	cout << "Second test: " << second_test << endl;
	double x2 = largest_ones(bit_seq);
	cout << "Xu: " << x2 << endl;
	cout << "Third test: " << 0.66017007 << endl;
	return 0;
}