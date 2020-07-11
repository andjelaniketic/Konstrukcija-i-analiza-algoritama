#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Cvor{
	//samo listovi ce imati punu rec, ostali cvorovi cuvaju njene delove
	string rec;
	//bitan nam je poredak pa koristimo obicnu mapu
	map<char, Cvor*> potomci;
};

Cvor *napravi_cvor(){
	Cvor *novi = new Cvor();
	
	novi->rec = "";
	//popunjavacemo rec dok dolazimo do lista
	return novi;
}

void dodaj_rec(Cvor *koren, string &rec, int i){
	if (i == (int)rec.size()){
		koren->rec = rec;
		return;
	}
	
	//trazimo da li postoji u stablu i-to slovo reci
	auto it = koren->potomci.find(rec[i]);
	
	//dodajemo ako ne postoji
	if(it == koren->potomci.end())
		koren->potomci[rec[i]] = napravi_cvor();
	
	dodaj_rec(koren->potomci[rec[i]], rec, i+1);

}

void leksikografski(Cvor *koren){
	//samo u listovima rec nije prazna niska
	if(koren->rec != "")
		cout << koren->rec << endl;
	
	auto pocetak = koren->potomci.begin();
	auto kraj = koren->potomci.end();
	
	while(pocetak != kraj){
		//rek poziv za drugi el para iz mape, tj odgovarajuci cvor
		leksikografski(pocetak->second);
		pocetak++;
	}
	
}

void oslobodi(Cvor *koren){
	if(koren == nullptr)
		return;
	
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
	
}

int main(){
	vector<string> reci;
	string ulaz;
	int n;
	cin >> n;
	
	for(int i=0; i<n; i++){
		cin >> ulaz;
		reci.push_back(ulaz);
	}
	
	Cvor *koren = napravi_cvor();
	
	for(string &s : reci)
		dodaj_rec(koren, s, 0);
	
	leksikografski(koren);
	
	oslobodi(koren);
	
	return 0;
}
