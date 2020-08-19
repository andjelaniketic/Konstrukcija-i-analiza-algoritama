#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<bool> posecen;
	vector<int> stepen; //broj grana sa kojima je cvor susedan
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);
	G.stepen.resize(V, 0);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
	G.stepen[u]++;
	G.stepen[v]++;
}

int prebroj_cvorove_neparnog_stepena(Graph &G){
	int brojac = 0;
	for(int i=0; i<G.V; i++){
		if(G.stepen[i] % 2)
			brojac++;
	}
	return brojac;
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	for(int sused : G.lista_suseda[u]){
		if(!G.posecen[sused])
			DFS(G, sused);
	}
}

bool povezan(Graph &G){
	int pocetak;
	for(int i=0; i<G.V; i++){
		if(G.lista_suseda[i].size() > 0)
			pocetak = i;
	}

	DFS(G, pocetak);

	for(int i=0; i<G.V; i++){
		//ako cvor nije posecen i nije izolovani cvor, graf nije povezan
		if(!G.posecen[i] && G.stepen[i] > 0)
			return false;
	}
	return true;
}

int ojlerov(Graph &G){
	int neparni_stepen = prebroj_cvorove_neparnog_stepena(G);
	
	if(neparni_stepen > 2)
		return 0; //nije ojlerov

	if(!povezan(G))
		return 0; //ako nije povezan, nije ojlerov
	//ako ima 0 cvorova nep stepena, onda ima ciklus, u drugom slucaju ima put
	return neparni_stepen == 0 ? 2 : 1;
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

	int rez = ojlerov(G);
	if(rez == 0)
		cout << "graf nije ojlerov\n";
	else if(rez == 1)
		cout << "graf ima ojlerov put\n";
	else
		cout << "graf ima ojlerov ciklus\n";

	return 0;
}