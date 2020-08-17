#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#define INF INT_MAX

using namespace std;

struct cmp
{
	bool operator()(pair<int, int> &p1, pair<int, int> &p2){
		return p1.second > p2.second;
	}
};

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<bool> posecen;

	vector<int> udaljenost;
	vector<int> stanice;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);
	G.udaljenost.resize(V, INF);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
}

void dodaj_stanicu(Graph &G, int u){
	G.stanice.push_back(u);
}

void dajkstra(Graph &G){
	priority_queue<pair<int,int>, vector<pair<int, int>>, cmp> heap;
	for(int stanica : G.stanice){
		heap.push(make_pair(stanica, 0));
		G.udaljenost[stanica] = 0;
	}

	pair<int, int> trenutni;
	while(!heap.empty()){
		trenutni = heap.top();
		heap.pop();
		if (G.posecen[trenutni.first])
			continue;

		G.posecen[trenutni.first] = true;

		for(int sused : G.lista_suseda[trenutni.first]){
			if (G.udaljenost[trenutni.first] + 1 < G.udaljenost[sused]){
				G.udaljenost[sused] = G.udaljenost[trenutni.first]  + 1;
				heap.push(make_pair(sused, G.udaljenost[sused]));
			}
		}
	}

	for(int i=0; i<G.V; i++){
		cout << "Najbliza stanica od grada " << i << " je udaljena " << G.udaljenost[i] << " kilometara." << endl;
	}
}

int main(){
	Graph G;
	int V, E, stanice;
	cin >> V >> E >> stanice;

	inicijalizacija(G, V);
	int u, v;
	for(int i=0; i<E; i++){
		cin >> u >> v;
		dodaj_granu(G, u, v);
	}

	cout << "unesi koji gradovi imaju stanice: ";
	for(int i=0; i<stanice; i++){
		cin >> u;
		dodaj_stanicu(G, u);
	}

	dajkstra(G);

	return 0;
}