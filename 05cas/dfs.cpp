#include <iostream>
#include <vector>

using namespace std;

struct graf
{
	vector<vector<int>> lista_suseda;
	int V;
	vector<bool> posecen;
};

void dodaj_granu(graf &G, int u, int v){
	//usmeren
	G.lista_suseda[u].push_back(v);
	/*neusmeren
	G.lista_suseda[v].push_back(u);*/
}

void inicijalizacija(graf &g, int V){
	g.V = V;
	g.lista_suseda.resize(V);
	g.posecen.resize(V, false);
}

void DFS(graf &G, int u){
	G.posecen[u] = true;
	cout << u << " ";

	for(auto &sused : G.lista_suseda[u]){
		if(!G.posecen[sused])
			DFS(G, sused);
	}

}

int main(){
	int V, E;
	cin >> V >> E;
	graf G;
	inicijalizacija(G, V);

	int u, v;
	for(int i=0; i<E; i++){
		cin >> u >> v;
		dodaj_granu(G, u, v);
	}

	DFS(G, 0);
	cout << endl;
	return 0;
}