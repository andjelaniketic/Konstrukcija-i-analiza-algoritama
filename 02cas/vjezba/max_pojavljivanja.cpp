#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct cvor
{
	string rec;
	int brojac;
	unordered_map<char, cvor*> potomci;
};

cvor *napravi_cvor(){
	cvor *novi = new cvor();
	novi->rec = "";
	novi->brojac = 0;
	return novi;
}

void dodaj_rec(cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){
		koren->brojac++;
		koren->rec = rec;
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

void nadji_rec_najvise_pojavljivanja(cvor *koren, string &rijec, int &max){
	if(koren->rec != ""){
		if(koren->brojac > max){
			max = koren->brojac;
			rijec = koren->rec;
		}
	}
	for(auto &p : koren->potomci)
		nadji_rec_najvise_pojavljivanja(p.second, rijec, max);
}

int main(){
	int n;
	cin >> n;

	std::vector<string> v(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> v[i];
	}

	cvor *koren = napravi_cvor();
	for(string &p : v)
		dodaj_rec(koren, p, 0);

	int max = 0;
	string rijec = "";
	nadji_rec_najvise_pojavljivanja(koren, rijec, max);

	cout << rijec << " " << max << endl;

	oslobodi(koren);
	return 0;
}