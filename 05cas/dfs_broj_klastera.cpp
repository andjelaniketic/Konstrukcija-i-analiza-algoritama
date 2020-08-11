#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_povezanosti;
	int V;
	vector<bool> posecen;
	
	int min_grana;
	int klasteri;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.posecen.resize(V, false);
	G.lista_povezanosti.resize(V);
	G.klasteri = 0;
}

void dodaj_granu(Graph &G, int u, int v){
	G.lista_povezanosti[v].push_back(u);
	G.lista_povezanosti[u].push_back(v);
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	
	auto begin = G.lista_povezanosti[u].begin();
	auto end = G.lista_povezanosti[u].end();
	
	while(begin != end){
		if(!G.posecen[*begin])
			DFS(G, *begin);
		begin++;
	}
	
}

int broj_komponenti(Graph &G){
	for(int i=0; i<G.V; i++)
		//ako nije posecen znaci pripada nekoj komponenti koju nismo obisli, pozivamo DFS opet za taj deo i povecavamo broj komponenti
		if(!G.posecen[i]){
			G.klasteri++;
			DFS(G, i);
		}
	return G.klasteri;
}

int main(){
	Graph G;
	inicijalizacija(G, 6);
	
	dodaj_granu(G, 0, 1);
	dodaj_granu(G, 0, 2);
	dodaj_granu(G, 1, 2);
	dodaj_granu(G, 2, 0);
	dodaj_granu(G, 2, 3);
	dodaj_granu(G, 3, 3);
	dodaj_granu(G, 4, 5);
	dodaj_granu(G, 4, 4);
	dodaj_granu(G, 5, 4);
	
	cout << broj_komponenti(G) << endl;
	
	return 0;
}
