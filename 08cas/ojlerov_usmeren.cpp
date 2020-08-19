#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<bool> posecen;
	vector<int> ul_stepen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);
	G.ul_stepen.resize(V, 0);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_suseda[u].push_back(v);
	G.ul_stepen[v]++;
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	for(int sused : G.lista_suseda[u]){
		if(!G.posecen[sused])
			DFS(G, sused);
	}
}

Graph obrni_grane(Graph &G){
	Graph obrni_G;
	inicijalizacija(obrni_G, G.V);

	for(int i=0; i<G.V; i++){
		for(int sused : G.lista_suseda[i])
			dodaj_granu(obrni_G, sused, i);
	}
	return obrni_G;
}

int prebroj_neposecene(Graph &G){
	int brojac;
	for(int i=0; i<G.V; i++){
		if(!G.posecen[i])
			brojac++;
	}
	return brojac;
}

bool kosaraju(Graph &G){
	//pocetni cvor ne sme da bude izolovani cvor
	int pocetak;
	for(int i=0; i<G.V; i++){
		if(G.lista_suseda[i].size()){
			pocetak = i;
			break;
		}
	}

	DFS(G, pocetak);

	if(prebroj_neposecene(G) > 0)
		return false;

	Graph obrni_G = obrni_grane(G);

	DFS(obrni_G, pocetak);

	if(prebroj_neposecene(obrni_G) > 0)
		return false;

	return true;
}
//usmeren graf treba da bude jako povezan kako bi bio ojlerov
bool ojlerov(Graph &G){
	if(!kosaraju(G))
		return false;

	//kod usmerenog grafa, da bi imao ojlerov ciklus, ulazni i izlazni stepen svih cvorova mora biti jednak
	for(int i=0; i<G.V; i++)
		if(G.ul_stepen[i] != G.lista_suseda[i].size())
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

	if(ojlerov(G))
		cout << "graf je ojlerov\n";
	else
		cout << "graf nije ojlerov\n";

	return 0;
}