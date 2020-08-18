#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<bool> posecen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_suseda[u].push_back(v);
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;

	for(int sused : G.lista_suseda[u]){
		if(!G.posecen[sused])
			DFS(G, sused);
	}
}

int prebroj_naposecene(Graph &G){
	int neposeceni = 0;
	for(int i=0; i<G.V; i++)
		if(!G.posecen[i])
			neposeceni++;
	return neposeceni;
}

Graph obrni_grane(Graph &G){
	Graph obrnut_G;
	inicijalizacija(obrnut_G, G.V);

	for(int i=0; i<G.V; i++){
		for(int cvor : G.lista_suseda[i])
			//u G je grana i->cvor a mi dodajemo cvor->i
			dodaj_granu(obrnut_G, cvor, i);
	}
	return obrnut_G;
}

bool kosaraju(Graph &G){
	DFS(G, 0);
	//odma vracamo da graf nije jako povezan ako posle dfs ima neposecenih
	if(prebroj_naposecene(G) > 0)
		return false;

	Graph obrnut_G = obrni_grane(G);

	DFS(obrnut_G, 0);

	if(prebroj_naposecene(obrnut_G) > 0)
		return false;

	return true;
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
	
	if(kosaraju(G))
		cout << "Graf je jako povezan.\n";
	else
		cout << "Graf nije jako povezan.\n";

	return 0;
}