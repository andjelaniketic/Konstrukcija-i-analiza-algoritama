#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Cvor{
	//konstruktor
	Cvor(){
		levo = desno = nullptr;
	}
	
	int vrednost;
	Cvor *levo;
	Cvor *desno;
};

void dodaj_cvor(Cvor **koren, int vrednost){
	if(*koren == nullptr){
		*koren = new Cvor();
		(*koren)->vrednost = vrednost;
		return;
	}
	
	if((*koren)->vrednost > vrednost)
		dodaj_cvor(&(*koren)->levo, vrednost);
	else
		dodaj_cvor(&(*koren)->desno, vrednost);
}

void oslobodi_stablo(Cvor *koren){
	if(koren == nullptr)
		return;
	oslobodi_stablo(koren->levo);
	oslobodi_stablo(koren->desno);
	
	//alokacija sa new, brisanje sa delete
	delete koren;
}

void BFS(Cvor *koren, vector<int> &nivo){
	queue<Cvor *> cvorovi;
	cvorovi.push(koren);
	
	nivo[koren->vrednost] = 0;
	int trenutni_nivo = 0;
	
	Cvor *pom;
	while(cvorovi.size()){
		pom = cvorovi.front();
		cvorovi.pop();
		
		if(pom->levo != nullptr){
			//nivo potomka je za 1 veci od nivoa roditelja
			nivo[pom->levo->vrednost] = nivo[pom->vrednost] + 1;
			cvorovi.push(pom->levo);
		}
		if(pom->desno != nullptr){
			nivo[pom->desno->vrednost] = nivo[pom->vrednost] + 1;
			cvorovi.push(pom->desno);
		}
		
		//ispis
		if(nivo[pom->vrednost] != trenutni_nivo){
			cout << endl;
			trenutni_nivo++;
		}
		cout << pom->vrednost << " ";
	}
}

int main(){
	Cvor *koren = nullptr;
	int x;
	vector<int> vrednosti;
	
	while(cin >> x)
		vrednosti.push_back(x);
	
	for(int a : vrednosti)
		dodaj_cvor(&koren, a);
	
	int n = *max_element(vrednosti.begin(), vrednosti.end());
	vector<int> nivo(n);
	
	BFS(koren, nivo);
	cout << endl;
	
	oslobodi_stablo(koren);
	
	return 0;
}
