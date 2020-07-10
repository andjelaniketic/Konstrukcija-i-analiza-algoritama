#include <iostream>
#include <vector>
#include <cstdlib>

#define CHAR_SIZE 128

using namespace std;

struct Cvor{
	bool kraj_reci;
	Cvor *potomak[CHAR_SIZE];
};

Cvor *napravi_cvor(){
	Cvor *novi = (Cvor*)malloc(sizeof(Cvor));
	novi->kraj_reci = false;
	
	//ni jedan cvor nema potomke na pocetku
	for(int i=0; i < CHAR_SIZE; i++)
		novi->potomak[i] = nullptr;
	
	return novi;
}

void dodaj_rec_u_stablo(Cvor *koren, const string &rec){
	int n = rec.length();
	
	//prolazimo kroz rec i proveravamo da li postoji
	//potomak u drvetu ka kome vodi grana sa oznakom
	//i-tog karaktera u niski rec
	/*ako takva grana ne postoji, ne postoji ni taj potomak
	 te dodajemo granu (cvor)*/
	for(int i=0; i<n; i++){
		if(koren->potomak[(int)rec[i]] == nullptr)
			koren->potomak[(int)rec[i]] = napravi_cvor();
	
		koren = koren->potomak[(int)rec[i]];
	}
	//dosli do kraja reci, tekuci cvor je list
	koren->kraj_reci = true;
}

bool nadji_rec(Cvor *koren, const string &rec){
	if(koren == nullptr)
		return false;
	
	int n = rec.length();
	
	for(int i=0; i<n; i++){
		koren = koren->potomak[(int)rec[i]];
		
		if(koren == nullptr)
			return false;
	}
	
	return koren->kraj_reci;
}

void oslobodi(Cvor *koren){
	if(koren == nullptr)
		return;
	//oslobadjamo podstabla
	for(auto &cvor : koren->potomak)
		oslobodi(cvor);
	//oslobadjamo koren
	free(koren);
}

int main(){
	
	vector<string> reci = {"cod", "coder", "coding", "codecs"};
	
	Cvor *koren = napravi_cvor();
	
	for(string &s : reci)
		dodaj_rec_u_stablo(koren, s);
	
	string s = "code";
	cout << nadji_rec(koren, s) << endl;
	
	oslobodi(koren);
	return 0;
}
