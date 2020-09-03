#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;
struct cvor
{
	bool kraj_reci;
	string rec;
	unordered_map<char, cvor*> potomci;
};

cvor *napravi_cvor(){
	cvor *novi = new cvor();
	novi->kraj_reci = false;
	novi->rec = "";
	return novi;
}

void dodaj_rec(cvor *koren, string &rec, int i){
	if(i == (int)rec.size()){
		koren->rec = rec;
		koren->kraj_reci = true;
		return;
	}
	auto it = koren->potomci.find(rec[i]);
	if(it == koren->potomci.end()){
		koren->potomci[rec[i]] = napravi_cvor();
	}
	dodaj_rec(koren->potomci[rec[i]], rec, i+1);
}

void oslobodi(cvor *koren){
	if(koren == nullptr)
		return;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
}

cvor *autocomplete(cvor *koren, string &prefiks, int i){
	if(i == prefiks.size())
		return koren;

	auto it = koren->potomci.find(prefiks[i]);
	if(it == koren->potomci.end())
		return nullptr;
	
	return autocomplete(koren->potomci[prefiks[i]], prefiks, i+1);
}

void ispisi(cvor *koren){
	if(koren->kraj_reci)
		cout << koren->rec << endl;

	for(auto &p : koren->potomci){
		ispisi(p.second);
	}
}

int main(){
	string prefiks;
	cout << "unesite prefiks: ";
	cin >> prefiks;

	int n;
	cout << "unesite broj reci: ";
	cin >> n;

	vector<string> v(n);
	cout << "unesite reci recnika: ";
	for(int i=0; i<n; i++)
		cin >> v[i];

	cvor *koren = napravi_cvor();
	for(string &p : v)
		dodaj_rec(koren, p, 0);

	cvor *tmp = autocomplete(koren, prefiks, 0);
	
	ispisi(tmp);
	
	oslobodi(koren);
	return 0;
}