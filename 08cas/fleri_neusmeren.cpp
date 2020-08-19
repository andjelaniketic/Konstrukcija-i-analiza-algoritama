#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<bool> posecen;
	vector<int> stepen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);
	G.stepen.resize(V, 0);
}

void dodaj_granu(Graph &G, int u, int v){
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
	G.stepen[u]++;
	G.stepen[v]++;
}

int nadji_cvor_neparnog_stepena(Graph &G){
	for(int i=0; i<G.V; i++){
		if(G.stepen[i] % 2)
			return i;
	}
}

int nadji_cvor_parnog_stepena(Graph &G){
	for(int i=0; i<G.V; i++){
		//cvor parnog stepena ali da nije izolovani
		if((G.stepen[i] % 2 == 0) && (G.stepen[i] != 0))
			return i;
	}
}
int prebroj_neparnog_stepena(Graph &G){
	int brojac = 0;
	for(int i=0; i<G.V; i++){
		if(G.stepen[i] % 2)
			brojac++;
	}
	return brojac;
}

void obrisi_granu(Graph &G, int u, int v){
	G.lista_suseda[u].erase(find(G.lista_suseda[u].begin(), G.lista_suseda[u].end(), v));
	G.lista_suseda[v].erase(find(G.lista_suseda[v].begin(), G.lista_suseda[v].end(), u));
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	for(int sused : G.lista_suseda[u]){
		if(!G.posecen[sused])
			DFS(G, sused);
	}
}

bool validna_grana(Graph &G, int u, int v){
	if(G.lista_suseda[u].size() == 1)
		return true;

	obrisi_granu(G, u, v);
	
	fill(G.posecen.begin(), G.posecen.end(), false);

	DFS(G, u);

	dodaj_granu(G, u, v);
	
	if(!G.posecen[v])
		return false;

	return true;
}

void ispisi_ojlerov_put_ciklus(Graph &G, int u){
	for(int sused : G.lista_suseda[u]){
		if(validna_grana(G, u, sused)){
			cout << u << " -> " << sused << endl;
			obrisi_granu(G, u, sused);
			ispisi_ojlerov_put_ciklus(G, sused);
			break;
		}
	}
}

void fleri(Graph &G){
	int neparni = prebroj_neparnog_stepena(G);
	int pocetak;

	if(neparni == 0){
		pocetak = nadji_cvor_parnog_stepena(G);
		ispisi_ojlerov_put_ciklus(G, pocetak);
	}
	else if(neparni == 2){
		pocetak = nadji_cvor_neparnog_stepena(G);
		ispisi_ojlerov_put_ciklus(G, pocetak);
	}
}

int main(){
	Graph G;
	int V, E;
	cin >> V >> E;
	inicijalizacija(G, V);

	int u, v;
	for(int i=0; i<E; i++){
		cin >> u >> v;
		dodaj_granu(G, u, v);
	}

	fleri(G);

	return 0;
}