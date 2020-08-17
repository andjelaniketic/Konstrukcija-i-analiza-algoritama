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
	vector<vector<pair<int, int>>> lista_suseda;
	vector<bool> posecen;

	vector<int> udaljenost;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);

	G.udaljenost.resize(V, INF);
}

void dodaj_granu(Graph &G, int u, int v, int tezina){
	//neusmeren
	G.lista_suseda[u].push_back(make_pair(v, tezina));
	G.lista_suseda[v].push_back(make_pair(u, tezina));
}

void resetuj_graf(Graph &G){
	//vracamo sve udaljenosti na beskonacno i oznacavamo sve cvorove kao neposecene
	fill(G.udaljenost.begin(), G.udaljenost.end(), INF);
	fill(G.posecen.begin(), G.posecen.end(), false);
}

int dajkstra(Graph &G, int u, int v, int preskoci){
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
	G.udaljenost[u] = 0;

	heap.push(make_pair(u, G.udaljenost[u]));

	pair<int, int> trenutni;
	while(!heap.empty()){
		trenutni = heap.top();
		heap.pop();

		if(G.posecen[trenutni.first])
			continue;
		G.posecen[trenutni.first] = true;

		for(pair<int, int> sused : G.lista_suseda[trenutni.first])
		{
			if (sused.first == preskoci)
				continue;
			if (G.udaljenost[trenutni.first] + sused.second < G.udaljenost[sused.first]){
				G.udaljenost[sused.first] = G.udaljenost[trenutni.first] + sused.second;

				heap.push(make_pair(sused.first, G.udaljenost[sused.first]));
			}
		}
	}
	return G.udaljenost[v];
}

int najkraci_put_preko_cvora(Graph &G, int u, int v, int cvor){
	int rez = dajkstra(G, u, cvor, -1);
	resetuj_graf(G);
	return rez + dajkstra(G, cvor, v, -1);
}

int najkraci_put_preskoci(Graph &G, int u, int v, int preskoci){
	return dajkstra(G, u, v, preskoci);
}

int main(){
	Graph G;
	int V, E;
	cin >> V >> E;
	inicijalizacija(G, V);

	int u, v, tezina;
	for(int i=0; i<E; i++){
		cin >> u >> v >> tezina;
		dodaj_granu(G, u, v, tezina);
	}
	cout << "unesi pocetni i ciljni cvor: ";
	int start, end;
	cin >> start >> end;
	
	cout << "unesi koji treba da se preskoci: ";
	int preskoci;
	cin >> preskoci;
	cout << "unesi kojim mora da se ide: ";
	int cvor;
	cin >> cvor;

	if(preskoci == -1)
		cout << najkraci_put_preko_cvora(G, start, end, cvor) << endl;
	else
		cout << najkraci_put_preskoci(G, start, end, preskoci) << endl;

	return 0;
}