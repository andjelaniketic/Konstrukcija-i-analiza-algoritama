#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

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

void dodaj_rec(cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){
		koren->kraj_reci = true;
		return;
	}

	auto it = koren->potomci.find(rec[i]);
	if(it == koren->potomci.end())
		koren->potomci[rec[i]] = napravi_cvor();
	dodaj_rec(koren, rec, i+1);
}


void oslobodi(cvor *koren){
	if(koren == nullptr)
		return;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
}

void nadji_LCP(cvor *koren, string &LCP){
	while(koren && !koren->kraj_reci && koren->potomci.size() == 1){
		auto element = koren->potomci.begin();
		LCP += element->first;
		koren = element->second;
	}
}

int main(){
	int n;
	cin >> n;
	std::vector<string> reci(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> reci[i];
	}

	cvor *koren = napravi_cvor();
	for(string &s : reci)
		dodaj_rec(koren, s, 0);

	string LCP = "";
	nadji_LCP(koren, LCP);
	cout << LCP << endl;
	oslobodi(koren);
	return 0;
}