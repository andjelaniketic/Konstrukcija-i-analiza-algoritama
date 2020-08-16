#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

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
	vector<vector<pair<int, int>>> lista_suseda;
	vector<bool> posecen;

	vector<int> udaljenost;
	vector<int> najkraci_put;
	vector<int> roditelj;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);

	G.udaljenost.resize(V, INF);
	G.najkraci_put.resize(V, INF);
	G.roditelj.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v, int tezina){
	G.lista_suseda[u].push_back(make_pair(v, tezina));
	G.lista_suseda[v].push_back(make_pair(u, tezina));
}

void dajkstra(Graph &G, int u, int v){
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
	//pocetni cvor
	G.udaljenost[u] = 0;
	G.najkraci_put[u] = 0;

	heap.push(make_pair(u, G.udaljenost[u]));

	pair<int, int> trenutni;
	while(!heap.empty()){
		trenutni = heap.top();
		heap.pop();

		if(G.posecen[trenutni.first])
			continue;

		G.posecen[trenutni.first] = true;

		for(pair<int, int> sused : G.lista_suseda[trenutni.first]){
			if((G.udaljenost[trenutni.first] + sused.second < G.udaljenost[sused.first]) || (G.udaljenost[sused.first] == G.udaljenost[trenutni.first] && G.najkraci_put[sused.first] > G.najkraci_put[trenutni.first] + 1)){
				G.najkraci_put[sused.first] = G.najkraci_put[trenutni.first] + 1;
				G.roditelj[sused.first] = trenutni.first;
				G.udaljenost[sused.first] = G.udaljenost[trenutni.first] + sused.second;

				heap.push(make_pair(sused.first, G.udaljenost[sused.second]));
			}
		}
	}

	stack<int> putanja;
	while(G.roditelj[v] != -1){
		putanja.push(v);
		v = G.roditelj[v];
	}

	putanja.push(v);
	int n = putanja.size();
	int cvor;
	while(n > 0){
		cvor = putanja.top();
		putanja.pop();
		n--;

		if (n > 0)
			cout << cvor << " -> ";
		else
			cout << cvor << endl;
	}
}

int main(){
	Graph G;
	int V, E;
	cin >> V >> E;

	inicijalizacija(G, V);

	int u, v, tezina;
	cout << "unesi grane i njihove tezine: \n";
	for(int i=0; i < E; i++){
		cin >> u >> v >> tezina; 
		dodaj_granu(G, u, v, tezina);
	}
	int start, end;
	cout << "unesi pocetni i ciljni cvor: ";
	cin >> start >> end;
	dajkstra(G, start, end);

	return 0;
}