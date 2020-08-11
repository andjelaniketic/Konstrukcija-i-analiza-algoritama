#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Graph{
	vector<vector<int>> lista_povezanosti;
	int V;
	vector<bool> posecen;
	
	int min_grana;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_povezanosti.resize(V);
	G.posecen.resize(V, false);
	
	G.min_grana = INT_MAX;
}

void dodaj_granu(Graph &G, int u, int v){
	G.lista_povezanosti[u].push_back(v);
}

void DFS(Graph &G, int u, int v, int trenutno_grana){
	if(u == v){
		if(trenutno_grana < G.min_grana)
			G.min_grana = trenutno_grana;
		return;
	}
	
	G.posecen[u] = true;
	
	auto begin = G.lista_povezanosti[u].begin();
	auto end = G.lista_povezanosti[u].end();
	
	while(begin != end){
		if(!G.posecen[*begin])
			DFS(G, *begin, v, trenutno_grana+1);
		begin++;
	}
	
	G.posecen[u] = false;
}

int main(){
	int u, v;
	cin >> u >> v;
	
	Graph G;
	inicijalizacija(G, 5);
	
	dodaj_granu(G, 0, 1);
	dodaj_granu(G, 1, 0);
	dodaj_granu(G, 0, 4);
	dodaj_granu(G, 1, 2);
	dodaj_granu(G, 2, 1);
	dodaj_granu(G, 2, 4);
	dodaj_granu(G, 4, 2);
	dodaj_granu(G, 2, 3);
	dodaj_granu(G, 3, 2);
	dodaj_granu(G, 3, 4);
	dodaj_granu(G, 4, 3);
	
	DFS(G, u, v, 0);
	
	cout << G.min_grana << endl;
	
	return 0;
}
