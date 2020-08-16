#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#define INF INT_MAX

using namespace std;
//poredi duzine puteva i vraca kraci
struct cmp{
	bool operator()(const pair<int, int> &p1, const pair<int, int> &p2){
		return p1.second > p2.second;
	}
};

struct Graph{
	vector<vector<pair<int, int>>> lista_suseda;
	int V;
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

/*void razdvoji(const pair<int, int> p, int &cvor, int &tezina){
	cvor = p.first;
	tezina = p.second;
}
*/
void dajkstra(Graph &G, int u){
	//red sa prioritetom koji cuva parove, implementiran je kao vector parova i za poredjenje koristi funkciju cmp
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
	//udaljenost pocetnog cvora od samog sebe je uvek 0
	G.udaljenost[u] = 0;
	heap.push(make_pair(u, G.udaljenost[u]));

	pair<int, int> trenutni;
	while(!heap.empty()){
		trenutni = heap.top();
		heap.pop();
		//ako smo oznacili da je cvor posecen znaci da smo nasli najkraci put od pocetnog cvora do njega
		//ovo je zbog mogucnosti da se vise puta nadje isti cvor na heapu
		if (G.posecen[trenutni.first])
			continue;

		G.posecen[trenutni.first] = true;
		
		for(const pair<int, int> &sused : G.lista_suseda[trenutni.first]){
			if (G.udaljenost[trenutni.first] + sused.second < G.udaljenost[sused.first]){
				G.udaljenost[sused.first] = G.udaljenost[trenutni.first] + sused.second;
				heap.push(make_pair(sused.first, G.udaljenost[sused.first]));
			}
		}
		cout << u << "->" << trenutni.first << ": " << G.udaljenost[trenutni.first] << endl;
	}
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

	dajkstra(G, 0);

	return 0;
}