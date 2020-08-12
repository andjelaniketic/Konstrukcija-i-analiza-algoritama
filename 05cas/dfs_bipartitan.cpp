#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> boja;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.boja.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren graf
	G.lista_susedstva[u].push_back(v);
	G.lista_susedstva[v].push_back(u);
}

bool DFS(Graph &G, int u, int boja){
	G.posecen[u] = true;
	//bojimo cvor u prosledjenu boju
	G.boja[u] = boja;
	
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	
	while(begin != end){
		//ako su susedi iste boje, graf nije bipartitan
		if(G.boja[*begin] == G.boja[u])
			return false;
		
		if(!G.posecen[*begin]){
			if(!DFS(G, *begin, !boja)) //prosledjujemo suprotnu boju
				return false;
			//ako rek poziv vrati false znaci da je u nekom podgrafu doslo do kontradikcije
		}
		begin++;
	}
	//bez problema smo obojili graf sa 2 boje, znaci jeste bipartitan
	return true;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);
	
	if(DFS(G, 0, 0))
		cout << "Graf je bipartitan\n";
	else
		cout << "Graf nije bipartitan\n";
	
	return 0;
}
