#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ofstream out;

bool jeZeNoter(char matrikaKljucev[5][5], int znak) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (matrikaKljucev[i][j] == znak) {
				return true;
			}
		}
	}
	return false;
}

void izpisMatrike(char matrikaKljucev[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << matrikaKljucev[i][j] << " ";
		}
		cout << endl;
	}
}
