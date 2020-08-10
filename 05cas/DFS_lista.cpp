#include <iostream>
#include <vector>

using namespace std;

struct Graf{
	vector<vector<int>> lista_susedstva;
	int broj_cvorova;
	vector<bool> posecen;
};

//konstruktor
void inicijalizacija_grafa(Graf &G, int V){
	G.broj_cvorova = V;
	//alokacija memorije za V boolien mesta inicijalizovanih na false
	G.posecen.resize(V, false);
	//alokacija memorije za V vectora
	G.lista_susedstva.resize(V);
}

//dodaje granu koja ide iz cvora u u cvor v
void dodaj_granu(Graf &G, int u, int v){
	//dodajemo u listu susedstva cvora u, cvor v
	G.lista_susedstva[u].push_back(v);
}

//obilazak grafa u dubinu, u je cvor koji trenutno obradjujemo
void DFS(Graf &G, int u){
	//oznacavamo trenutni cvor kao posecen
	G.posecen[u] = true;
	cout << u << " ";
	
	//iteratori na pocetak i kraj kolekcije
	//obradjujemo sve susede trenutnog cvora
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	
	while(begin != end){
		//proveravamo da li je cvor posecen i pozivamo rekurzivno ako nije
		if (!G.posecen[*begin])
			DFS(G, *begin);
		//iteracija kroz kolekciju:
		begin++;
	}
}

int main(){
	int V;
	cin >> V;
	
	Graf G;
	
	inicijalizacija_grafa(G, V);
	
	dodaj_granu(G, 0, 1);  //0 -> 1
	dodaj_granu(G, 0, 2);  //0 -> 1, 2
	dodaj_granu(G, 1, 2);  //1 -> 2
	dodaj_granu(G, 2, 0);  //2 -> 0
	dodaj_granu(G, 2, 3);  //2 -> 3
	dodaj_granu(G, 3, 3);  //3 -> 3
	
	DFS(G, V);
	
	cout << "\n";
	return 0;
}
