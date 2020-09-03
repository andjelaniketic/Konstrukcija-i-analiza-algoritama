#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

struct cvor
{
	string rec;
	int broj;
	unordered_map<char, cvor*> potomci;
};

cvor *napravi_cvor(){
	cvor *novi = new cvor();
	novi->rec = "";
	novi->broj = 0;
	return novi;
}

void dodaj_rec(cvor *koren, string &rec, int i){
	if(i == (int)rec.size()){
		koren->rec = rec;
		koren->broj++;
		return;
	}
	for(auto &p : koren->potomci)
		dodaj_rec(koren->potomci[rec[i]], rec, i+1);
}

void oslobodi(cvor *koren){
	if(koren == nullptr)
		return;
	for(auto &p : koren->potomci)
		oslobodi(p.second);
	delete koren;
}

struct comparator
{	//porede se prema broju pojavljivanja
	bool operator()(cvor *n1, cvor *n2){
		return n1->broj < n2->broj;
	}
};

//sve bacamo na heap
void sve_baci_na_heap(cvor *koren, auto &heap){
	if(koren->rec != ""){
		heap.push(koren->rec);
	}
	for(auto &p : koren->potomci)
		sve_baci_na_heap(p.second, heap);
}
int main(){
	int n;
	cin >> n;

	vector<string> v(n);
	for(int i=0; i<n; i++)
		cin >> v[i];

	cvor *koren = napravi_cvor();
	for(string &p : v)
		dodaj_rec(koren, p, 0);

	int k;
	cin >> k;

	priority_queue<cvor*, vector<cvor*>, comparator> heap;
	sve_baci_na_heap(koren, heap);

	cvor *tmp;
	while(k && heap.size()){
		tmp = heap.top();
		heap.pop();

		cout << tmp->rec << ": " << tmp->broj << endl;
		k--;
	}

	oslobodi(koren);

	return 0;
}