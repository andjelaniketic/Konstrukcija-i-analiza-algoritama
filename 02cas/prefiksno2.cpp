#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

//u mapi cuvamo potomke svakog cvora, kljuc u mapi
//je karakter koji vodi ka cvoru potomku, a vrednost
//je bas taj cvor

struct Cvor{
	bool kraj_reci;
	unordered_map<char, Cvor*> potomci;
};

Cvor *napravi_cvor(){
	Cvor *novi = new Cvor(); //zbog mape
	
	novi->kraj_reci = false;
	return novi;
}

// umeće sufiks reči rec od pozicije "i" u drvo na čiji koren ukazuje
// pokazivač trie
void dodaj_rec_u_stablo(Cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){		//stigli do kraja
		koren->kraj_reci = true;
		return;
	}
	//trazimo u mapi par ciji je kljuc i-to slovo reci
	//to radi metod find() i vraca pokazivac na odg element, inace 
	//pokazivac na kraj mape
	
	auto it = koren->potomci.find(rec[i]);
	//umesto da pisemo unordered_map<char, Cvor*> it
	
	if(it == koren->potomci.end()) //nije nadjen trenutni el
		//dodajemo ga
		koren->potomci[rec[i]] = napravi_cvor();
	
	//rekurzivno dodajemo naredno slovo iz reci
	//koren koji prosledjujemo je trenutni cvor
	dodaj_rec_u_stablo(koren->potomci[rec[i]], rec, i+1);
}

bool nadji_rec(Cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){
		return koren->kraj_reci;
	}
	
	auto it = koren->potomci.find(rec[i]);
	
	if(it == koren->potomci.end())
		return false;
	
	return nadji_rec(koren->potomci[rec[i]], rec, i+1);
}

void oslobodi(Cvor *koren){
	if (koren == nullptr)
		return;
	
	//koristili smo mapu, pa brisemo pokazivac ka cvoru(p.second)
	//i to sa delete
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	
	delete koren;
}

int main(){
	vector<string> reci = {"cod", "coder", "coding", "codecs"};
	Cvor *koren = napravi_cvor();
	
	for(string s : reci)
		dodaj_rec_u_stablo(koren, s, 0);
	
	string s = "code";
	
	cout << nadji_rec(koren , s, 0) << endl;
	cout << boolalpha << nadji_rec(koren, s, 0) << endl;
	oslobodi(koren);
	return 0;
}
