#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_suseda;
	int V;
	vector<bool> posecen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
}
//trazimo cvor koji se moze izbaciti tako da graf ostane povezan, takav cvor je list u dfs stablu
void DFS(Graph &G, int u){
	G.posecen[u] = true;
	bool is_leaf = true;

	auto begin = G.lista_suseda[u].begin();
	auto end = G.lista_suseda[u].end();
	while(begin != end){
		if(!G.posecen[*begin]){
			DFS(G, *begin);
			is_leaf = false; //ima suseda kog nismo posetili, znaci nije list
		}
		begin++;
	}
	if(is_leaf)
		cout << u << endl;
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

	DFS(G, 0);
	
	return 0;
}