#include <iostream>
#include <vector>
#include <algorithm>

struct Graph
{
	std::vector<std::vector<int>> lista_suseda;
	int V;
	std::vector<bool> posecen;

	int br_ciklusa;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);

	G.br_ciklusa = 0;
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
}

void DFS(Graph &G, int u, int start, int n){
	G.posecen[u] = true;

	//na putu smo koji je duzine n-1, dosli smo do cvora u i proveravamo da li iz njega postoji grana ka cvoru iz kog smo krenuli, ako da onda imamo ciklus
	if(n == 0){
		if(std::find(G.lista_suseda[u].begin(), G.lista_suseda[u].end(), start) != G.lista_suseda[u].end())
			G.br_ciklusa++;
		//ako ne, nemamo i obelezavamo svakako da je neposecen zbog narednih poziva
		G.posecen[u] = false;
		return;
	}

	//prolazimo susede
	auto begin = G.lista_suseda[u].begin();
	auto end = G.lista_suseda[u].end();

	while(begin != end){
		if(!G.posecen[*begin])
			DFS(G, *begin, start, n-1);
		begin++;
	}
	G.posecen[u] = false;
}

int broj_ciklusa(Graph &G, int n){
	for(int i=0; i<G.V - (n-1); i++){
		DFS(G, i, i, n-1);
		G.posecen[i] = true;
	}

	return G.br_ciklusa/2;
}

int main(){
	int n;
	std::cin >> n;
	Graph G;
	int V, E;
	std::cin >> V >> E;

	inicijalizacija(G, V);

	int u, v;

	for(int i=0; i<E; i++){
		std::cin >> u >> v;
		dodaj_granu(G, u, v);
	}

	std::cout << broj_ciklusa(G, n) << std::endl;
	return 0;
}