#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ofstream out;

string inputText(const string& pot) {
    ifstream input(pot, ios::binary);
    if (!input.is_open()) {
        return string();
    }

    string content((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();
    return content;
}

void izpisVDatoteko(const string& imeDatoteke, const string& text) {
    ofstream datoteka(imeDatoteke);
    if (!datoteka.is_open()) {
        cerr << "Napaka pri odpiranju datoteke za pisanje: " << imeDatoteke << endl;
        return;
    }
    datoteka << text;
    datoteka.close();
}

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

void playFairSifriranje(string& kljuc, string& text) {    
    //v male črke
	for(int i = 0; i < kljuc.length(); i++){
		if(kljuc[i] >= 'A' && kljuc[i] <= 'Z'){
			kljuc[i] += 32;
		}
	}
	for(int i = 0; i < text.length(); i++){
		if(text[i] >= 'A' && text[i] <= 'Z'){
			text[i] += 32;
		}
	}

    //sestavljanje matrike (step 1)
	char mozneCrke[25] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char matrikaKljucev[5][5];
	int vrstica = 0;
	int stolpec = 0;

	for(int i = 0; i < kljuc.length(); i++){
		if(kljuc[i] == 'j'){
			if(!jeZeNoter(matrikaKljucev, 'i')){
				matrikaKljucev[vrstica][stolpec] = 'i';
			}else{
				continue;
			}
		}

		if(!jeZeNoter(matrikaKljucev, kljuc[i])){
			matrikaKljucev[vrstica][stolpec] = kljuc[i];
		}else{
			continue;
		}

		stolpec++;
		if(stolpec == 5){
			stolpec = 0;
			vrstica++;
		}
	}

	int trenutniChar = 0;
	for(int i = (vrstica * 5) + stolpec; i < 25; i++){
		char crka = mozneCrke[trenutniChar];
		if(!jeZeNoter(matrikaKljucev, crka)){
			matrikaKljucev[vrstica][stolpec] = crka;
			trenutniChar++;
		}else{
			i--;
			trenutniChar++;
			continue;
		}
		stolpec++;
		if(stolpec == 5){
			stolpec = 0;
			vrstica++;
		}
	}
	izpisMatrike(matrikaKljucev);

    //preobdelava vhoda (step 2)

	text.erase(remove(text.begin(), text.end(), ' '), text.end());
	if(text.length() % 2 != 0){
		text += text[text.length()-1]; //dodamo znak x
	}

	for(int a = 0; a < text.length(); a+=2){
		char znak1 = text[a]; //pozicija v matriki (i,j)
		char znak2 = text[a+1]; //pozicija v matriki (k,f)

		if(znak1 == 'j'){
			znak1 = 'i';
		}
		if(znak2 == 'j'){
			znak2 = 'i';
		}

		if(znak1 == znak2){
			znak2 = 'x';
		}

		pair<int, int> znak1poz = pozicijaZnaka(znak1, matrikaKljucev);
		pair<int, int> znak2poz = pozicijaZnaka(znak2, matrikaKljucev);

		int i = znak1poz.first;
		int j = znak1poz.second;
		int k = znak2poz.first;
		int f = znak2poz.second;

		if(i != k && j != f){
			znak1 = matrikaKljucev[i][f]; //znak 1
			znak2 = matrikaKljucev[k][j]; // znak 2
		}else if(i == k){
			znak1 = matrikaKljucev[i][(j+1)%5]; //znak 1
			znak2 = matrikaKljucev[k][(f+1)%5]; //znak 2
		}else if(j == f){
			znak1 = matrikaKljucev[(i+1)%5][j]; //znak 1
			znak2 = matrikaKljucev[(k+1)%5][f]; //znak 2
		}

		text[a] = znak1;
		text[a+1] = znak2;

	}

}

void playFairDesifriranje(string& kljuc, string& text) {
	//step 1 isti
	for(int i = 0; i < kljuc.length(); i++){
		if(kljuc[i] >= 'A' && kljuc[i] <= 'Z'){
			kljuc[i] += 32;
		}
	}

	//sestavljanje matrike (step 1)
	char mozneCrke[25] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char matrikaKljucev[5][5];
	int vrstica = 0;
	int stolpec = 0;

	for(int i = 0; i < kljuc.length(); i++){
		bool isI = false;
		if(kljuc[i] == 'j'){
			if(!jeZeNoter(matrikaKljucev, 'i')){
				matrikaKljucev[vrstica][stolpec] = 'i';
			}else{
				continue;
			}
		}

		if(!jeZeNoter(matrikaKljucev, kljuc[i])){
			matrikaKljucev[vrstica][stolpec] = kljuc[i];
		}else{
			continue;
		}

		stolpec++;
		if(stolpec == 5){
			stolpec = 0;
			vrstica++;
		}
	}

	int trenutniChar = 0;
	for(int i = (vrstica * 5) + stolpec; i < 25; i++){
		char crka = mozneCrke[trenutniChar];
		if(!jeZeNoter(matrikaKljucev, crka)){
			matrikaKljucev[vrstica][stolpec] = crka;
			trenutniChar++;
		}else{
			i--;
			trenutniChar++;
			continue;
		}
		stolpec++;
		if(stolpec == 5){
			stolpec = 0;
			vrstica++;
		}
	}
	izpisMatrike(matrikaKljucev);
}