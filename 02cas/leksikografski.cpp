#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct cvor
{
	string rec;
	map<char, cvor*> potomci;
};

cvor *napravi_cvor(){
	cvor *novi = new cvor();
	novi->rec = "";
	return novi;
}

void dodaj_rec(cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){
		koren->rec = rec;
		return;
	}
	auto it = koren->potomci.find(rec[i]);
	if(it == koren->potomci.end())
		koren->potomci[rec[i]] = napravi_cvor();

	dodaj_rec(koren->potomci[rec[i]], rec, i+1);
}

void oslobodi(cvor *koren){
	if(koren == nullptr)
		return;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
}

void leksikografski(cvor* koren){
	if(koren->rec != "")
		cout << koren->rec << endl;

	for(auto &s : koren->potomci){
		leksikografski(s.second);
	}
}

int main(){
	int n;
	cin >> n;
	
	vector<string> reci(n);
	for(int i=0; i<n; i++)
		cin >> reci[i];

	cvor *koren = napravi_cvor();
	for(string &s : reci)
		dodaj_rec(koren, s, 0);

	leksikografski(koren);
	
	oslobodi(koren);

	return 0;
}