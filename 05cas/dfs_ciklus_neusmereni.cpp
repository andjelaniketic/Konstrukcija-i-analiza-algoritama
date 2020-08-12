#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.posecen.resize(V, false);
	G.lista_susedstva.resize(V);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmereni graf
	G.lista_susedstva[u].push_back(v);
	G.lista_susedstva[v].push_back(u);
}

//trazi da li postoji ciklus pocev od cvora u, gde je 3. argument roditelj tog cvora
bool DFS(Graph &G, int u, int roditelj){
	G.posecen[u] = true;
	
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	
	while(begin != end){
		if (G.posecen[*begin]){
			//ako jeste == onda je to samo jedna ista grana izmedju 2 cvora, a to nije ciklus
			if(*begin != roditelj)
				return true;
		}else if (DFS(G, *begin, u)){
			//rekurzivni poziv za cvor iz liste suseda cvora u, u je sada roditelj
			//ako vrati true znaci da je nadjen ciklus u okviru podgrafa
			return true;
		}
		begin++;
	}
	//izasli smo iz petlje znaci nije nadjen ciklus
	return false;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);
	
	if (!DFS(G, 0, -1))
		cout << "Nije pronadjen ni jedan ciklus\n";
	else
		cout << "Pronadjen je ciklus\n";
	
	return 0;
}
