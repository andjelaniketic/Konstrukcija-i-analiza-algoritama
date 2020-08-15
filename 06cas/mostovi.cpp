#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;

	vector<int> roditelj;
	vector<int> ulazna_num;
	vector<int> izlazna_num;
	int pocetna_num;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);

	G.roditelj.resize(V, -1);
	G.ulazna_num.resize(V, -1);
	G.izlazna_num.resize(V, -1);
	G.pocetna_num = 0;
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_susedstva[u].push_back(v);
	G.lista_susedstva[v].push_back(u);
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	G.ulazna_num[u] = G.izlazna_num[u] = G.pocetna_num;

	G.pocetna_num++;
	int deca = 0;

	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	while(begin != end){
		if (!G.posecen[*begin]){
			G.roditelj[*begin] = u;
			DFS(G, *begin);

			deca++;
			G.izlazna_num[u] = min(G.izlazna_num[*begin], G.izlazna_num[u]);
			if (G.ulazna_num[u] < G.izlazna_num[*begin])
				cout << u << " -> " << *begin << endl;
		}
		else if (*begin != G.roditelj[u])
			G.izlazna_num[u] = min(G.izlazna_num[u], G.izlazna_num[*begin]);
		begin++;
	}
}

int main(){
	Graph G;
	int V;
	cin >> V;
	int w;
	cin >> w;
	inicijalizacija(G, V);

	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);

	DFS(G, w);

	return 0;
}