#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Cvor{
	bool kraj;
	unordered_map<char, Cvor*> potomci;
};

Cvor *napravi_cvor(){
	Cvor *novi = new Cvor();
	
	novi->kraj = false;
	return novi;
}

void dodaj_rec(Cvor *koren, const string &rec, int i){
	if(i == (int)rec.size()){
		koren->kraj = true;
		return;
	}
	auto it = koren->potomci.find(rec[i]);
	
	if(it == koren->potomci.end())
		koren->potomci[rec[i]] = napravi_cvor();
	
	dodaj_rec(koren->potomci[rec[i]], rec, i+1);
}

//u prefiks smestamo najduzi zajednicki prefiks
void najduzi_prefiks(Cvor *koren, string &prefiks){
	//spustamo se niz stablo sve dok ne dodjemo do prvog lista ili
	//dok god cvor ima samo 1 potomka
	while(koren && !koren->kraj && koren->potomci.size() == 1){
		auto element = koren->potomci.begin();
		
		prefiks += element->first;
		
		koren = element->second;
	}
}

void oslobodi(Cvor *koren){
	if(koren == nullptr)
		return ;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	
	delete koren;
}

int main(){
	vector<string> reci = {"ana", "anastasija", "anastasijin"};
	
	Cvor *koren = napravi_cvor();
	
	for(string s : reci)
		dodaj_rec(koren, s, 0);
	
	string LCP = "";
	
	najduzi_prefiks(koren, LCP);
	
	cout << LCP << endl;
	
	oslobodi(koren);
	return 0;
}
