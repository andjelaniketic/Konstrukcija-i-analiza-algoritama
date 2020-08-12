#include <iostream>
#include <vector>
#include <queue>

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
	//neusmeren
	G.lista_susedstva[u].push_back(v);
	G.lista_susedstva[v].push_back(u);
}

bool BFS(Graph &G, int u){
	queue<int> cvorovi;
	cvorovi.push(u);
	
	G.posecen[u] = true;
	G.boja[u] = 0;
	
	int pom;
	while(!cvorovi.empty()){
		pom = cvorovi.front();
		cvorovi.pop();
		
		auto begin = G.lista_susedstva[pom].begin();
		auto end = G.lista_susedstva[pom].end();
		
		while(begin != end){
			if(G.boja[pom] == G.boja[*begin])
				return false;
			
			if(!G.posecen[*begin]){
				G.posecen[*begin] = true;
				G.boja[*begin] = !G.boja[pom];
				cvorovi.push(*begin);
			}
			begin++;
		}
	}
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
	
	if(BFS(G, 0))
		cout << "Graf je bipartitan\n";
	else
		cout << "Graf nije bipartitan\n";
	
	return 0;
}
