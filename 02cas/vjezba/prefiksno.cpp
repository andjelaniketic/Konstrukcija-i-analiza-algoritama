#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct cvor
{
	bool kraj_reci;
	unordered_map<char, cvor*> potomci;
};

cvor *napravi_cvor(){
	cvor *novi = new cvor();
	novi->kraj_reci = false;
	return novi;
}
//umece sufiks prosledjene reci od pozicije i
void dodaj_rec(cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){
		koren->kraj_reci = true;
		return;
	}
	//trazimo i-to slovo da bismo nadovezali ostatak
	auto it = koren->potomci.find(rec[i]);
	if(it == koren->potomci.end())
		koren->potomci[rec[i]] = napravi_cvor();

	dodaj_rec(koren->potomci[rec[i]], rec, i+1);
}

bool nadji_rec(cvor *koren, const string &trazena, int i){
	if(i == (int)trazena.size())
		return koren->kraj_reci;
	auto it = koren->potomci.find(trazena[i]);
	if(it == koren->potomci.end())
		return false;
	return nadji_rec(koren->potomci[trazena[i]], trazena, i+1);

}
void oslobodi(cvor *koren){
	if(koren == nullptr)
		return;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
}

int main(){
	int n;
	cin >> n;
	vector<string> niz(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> niz[i];
	}
	cvor *koren = napravi_cvor();
	for(string s : niz)
		dodaj_rec(koren, s, 0);

	cout << "unesi trazenu rec: \n";
	string s;
	cin >> s;

	cout << nadji_rec(koren, s, 0) << endl;

	oslobodi(koren);
	return
}