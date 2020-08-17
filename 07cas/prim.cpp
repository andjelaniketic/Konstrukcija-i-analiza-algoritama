#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

using namespace std;

struct Graph
{
	int V;
	vector<vector<pair<int, int>>> lista_suseda;
	vector<bool> ukljucen_cvor;
	vector<int> roditelj;
	vector<int> vrednost_grane;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.ukljucen_cvor.resize(V, false);
	G.roditelj.resize(V, -1);
	G.vrednost_grane.resize(V, INF);
}

void dodaj_granu(Graph &G, int u, int v, int tezina){
	G.lista_suseda[u].push_back(make_pair(v, tezina));
	G.lista_suseda[v].push_back(make_pair(u, tezina));
}

int nadji_min_granu_neukljucenu(Graph &G){
	int min = INF;
	int min_index = -1;

	for(int i=0; i<G.V; i++){
		if (!G.ukljucen_cvor[i] && G.vrednost_grane[i] < min){
			min_index = i;
			min = G.vrednost_grane[i];
		}
	}
	//vracamo index cvora koji treba obraditi
	//tj to je cvor ka kome vodi minimalna grana u min raz stablu
	return min_index;
}

void prim(Graph &G, int u){
	//tezina grane koja vodi do pocetnog cvora je 0 (ne postoji)
	G.vrednost_grane[u] = 0;

	int cvor;
	for(int i=0; i<G.V-1; i++){
		cvor = nadji_min_granu_neukljucenu(G);
		//ubacujemo cvor u min stablo
		G.ukljucen_cvor[cvor] = true;
		//prolazimo sve susede cvora cvor, i azuriramo vrednosti grana koje vode ka njima, ukliko je vrednost grane manja od trenutno min grane koja vodi do suseda
		for(pair<int, int> sused : G.lista_suseda[cvor]){
			if (!G.ukljucen_cvor[sused.first] && sused.second < G.vrednost_grane[sused.first]){
				G.vrednost_grane[sused.first] = sused.second;
				G.roditelj[sused.first] = cvor;
			}
		}
	}

	int tezina_stabla = 0;
	for(int i=0; i<G.V; i++){
		if (i != u){
			tezina_stabla += G.vrednost_grane[i];
			cout << G.roditelj[i] << " -> " << i << endl;
		}
	}

	cout << tezina_stabla << endl;
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

	prim(G, 0);

	return 0;
}