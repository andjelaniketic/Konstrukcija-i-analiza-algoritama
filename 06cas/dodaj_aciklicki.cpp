#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> ulazni_stepen;
	vector<int> pozicija_top;
	vector<pair<int, int>> sve_grane;
	vector<pair<int, int>> dodate_grane;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.ulazni_stepen.resize(V, 0);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_susedstva[u].push_back(v);
	
	G.ulazni_stepen[v]++;
	
	pair<int, int> p(u, v);
	G.sve_grane.push_back(p);
}

void topolosko_sortiranje(Graph &G){
	queue<int> red_cvorova;
	//dodajemo sve cvorove ulaznog stepena 0 u red
	for(int i=0; i<G.V; i++){
		if(G.ulazni_stepen[i] == 0)
			red_cvorova.push(i);
	}

	//prolazimo kroz red i topoloski sortiramo i ispisujemo
	int trenutni;
	while(!red_cvorova.empty()){
		trenutni = red_cvorova.front();
		red_cvorova.pop();

		cout << trenutni << " ";
		G.pozicija_top.push_back(trenutni);

		for(int sused : G.lista_susedstva[trenutni]){
			G.ulazni_stepen[sused]--;

			if(G.ulazni_stepen[sused] == 0)
				red_cvorova.push(sused);
		}
	}
}

//proverava da li graf ima ciklus, pocinje pretragu iz cvora u
bool DFS_ima_ciklus(Graph &G, int u){
	//trenutni cvor koji obradjujemo oznacavamo kao posecen
	G.posecen[u] = true;

	//prolazimo kroz listu suseda
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	//ako naidjemo na cvor koji je vec posecen, imamo ciklus
	while(begin != end){
		if(G.posecen[*begin])
			return true;
		//ili ako je u podgrafu nadjen ciklus
		else if(DFS_ima_ciklus(G, *begin))
			return true;

		begin++;
	}
	//obavezno po izlasku iz petlje oznacavamo da u vise nije posecen kako bi bio dostupan pri drugim pozivima
	G.posecen[u] = false;
	//takodje ako smo dovde stigli, nema ciklusa
	return false;
}

void dodaj(Graph &G){
	//prvo sortiramo topoloski cvorove
	topolosko_sortiranje(G);

	//zatim prolazimo kroz cvorove u tom redosledu
	for(int i=0; i<G.V; i++){
		//prolazimo kroz susede cvora koji je na poziciji i u topoloskom sortiranju i oznacavamo kao posecene jer necemo dodavati nove grane ka njima iz ovog cvora
		for(int y : G.lista_susedstva[G.pozicija_top[i]])
			G.posecen[y] = true;

		//zatim prolazimo kroz sve cvorove koji su NAKON cvora na poziciji i u top sortiranju
		for(int j=i+1; j<G.V; j++){
			//ako nije posecen, dodajemo granu
			if(!G.posecen[G.pozicija_top[j]]){
				pair<int, int> p(G.pozicija_top[i], G.pozicija_top[j]);
				G.sve_grane.push_back(p);
				G.dodate_grane.push_back(p);
			}
			//vracamo na neposecene, gore objasnjeno
			G.posecen[G.pozicija_top[j]] = false;
		}
	}

	//konacno, proveravamo da li je narusena aciklicnost
	if(DFS_ima_ciklus(G, 0))
		cout << "Ima ciklus\n";
	else
		cout << "Nema ciklus\n";

	//ispisujemo sve grane
	cout << "Sve grane:\n";
	for(auto p : G.sve_grane)
		cout << p.first << " -> " << p.second << endl;

	//ispisujemo dodate grane
	cout << "Dodate grane:\n";
	for(auto p : G.dodate_grane)
		cout << p.first << " -> " << p.second << endl;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	inicijalizacija(G, V);

	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);

	dodaj(G);

	return 0;
}