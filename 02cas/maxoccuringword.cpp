#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Cvor{
	string rec;
	int br;
	unordered_map<char, Cvor*> potomci;
};

Cvor *napravi_cvor(){
	Cvor *novi = new Cvor();
	
	novi->rec = "";
	novi->br = 0;
	
	return novi;
}

void dodaj_rec(Cvor *koren, string &word , int i){
	//i je stiglo do kraja reci, znaci u trenutnom cvoru je rec
	if(i == (int)word.size()){
		koren->br++;
		koren->rec = word;
		return;
	}
	//it trazi trenutno slovo reci word
	auto it = koren->potomci.find(word[i]);
	//ako ga nema, dodaje ga u stablo
	if(it == koren->potomci.end())
		koren->potomci[word[i]] = napravi_cvor();
	//nastavljamo potragu za sledecim slovom
	dodaj_rec(koren, word, i+1);
}

void max_occuring(Cvor *koren, string &max_occuring_word, int &max){
	//vraticemo rec s najvise pojavljivanja kao i broj pojavljivanja
	if(koren->rec != ""){
		if(koren->br > max){
			max = koren->br;
			max_occuring_word = koren->rec;
		}
	}
	
	auto begin = koren->potomci.begin();
	auto end = koren->potomci.end();
	
	while(begin != end){
		max_occuring(begin->second, max_occuring_word, max);
		begin++;
	}
}

void oslobodi(Cvor *koren){
	if(koren == nullptr)
		return;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
}

int main (){
	vector<string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};
	
	Cvor *koren = napravi_cvor();
	
	for(string &s : words)
		dodaj_rec(koren, s, 0);
	
	string max_occuring_word = "";
	int max = 0;
	
	max_occuring(koren, max_occuring_word, max);
	cout << max_occuring_word << " " << max << endl;
	
	oslobodi(koren);
	return 0;
}
