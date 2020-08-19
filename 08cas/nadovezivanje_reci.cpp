#include <iostream>
#include <vector>

using namespace std;

#define MAX 26

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
	G.lista_suseda[u].push_back(v);
	G.ul_stepen[v]++;
}

void dodaj_reci(Graph &G, vector<string> &reci){
	for(string &rec : reci){
		dodaj_granu(G, rec[0] - 'a', rec[rec.size()-1] - 'a');
	}
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	for(int sused : G.lista_suseda[u]){
		if(!G.posecen[sused])
			DFS(G, sused);
	}
}

int prebroj_neposecene(Graph &G){
	int brojac = 0;
	for(int i=0; i<G.V; i++){
		if(!G.posecen[i] && G.lista_suseda[i] .size() > 0)
			brojac++;
	}
	return brojac;
}

Graph obrni_grane(Graph &G){
	Graph obrnut;
	inicijalizacija(obrnut, G.V);

	for(int i=0; i<G.V; i++){
		for(int v : G.lista_suseda[i])
			dodaj_granu(obrnut, v, i);
	}
	return obrnut;
}

bool kosaraju(Graph &G, int u){
	DFS(G, u);

	if(prebroj_neposecene(G) > 0)
		return false;

	Graph obrni_G = obrni_grane(G);

	DFS(obrni_G, u);

	if(prebroj_neposecene(obrni_G) > 0)
		return false;

	return true;
}

bool ojlerov(Graph &G, int u){
	//mora biti jako povezan
	if(!kosaraju(G, u))
		return false;
	//moraju imati jednak ul i izlazni stepen
	for(int i=0; i<G.V; i++){
		if(G.ul_stepen[i] != G.lista_suseda[i].size())
			return false;
	}
	return true;
}

int main(){
	Graph G;
	inicijalizacija(G, MAX);
	int n;
	cin >> n;
	vector<string> words(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> words[i];
	}
	dodaj_reci(G, words);

	cout << (ojlerov(G, words[0][0] - 'a') ? "Words can be chained!\n" : "Words can't be chained!\n");

	return 0;
}