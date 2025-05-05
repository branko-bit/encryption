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

pair<int,int> pozicijaZnaka(char znak, char matrika[5][5]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(matrika[i][j] == znak){
				return {i,j};
			}
		}
	}
	return {-1,-1};
}

void izpisTexta(const string& text) {
	for (int i = 0; i < text.length(); i++) {
		cout << text[i];
	}
}