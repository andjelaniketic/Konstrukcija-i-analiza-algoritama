#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> roditelj;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.roditelj.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v){
	//neumseren
	G.lista_susedstva[u].push_back(v);
	G.lista_susedstva[v].push_back(u);
}

bool BFS(Graph &G, int u){
	//red za cuvanje cvorova
	queue<int> cvorovi;
	cvorovi.push(u);

	G.posecen[u] = true;
	
	int pom;
	while(!cvorovi.empty()){
		pom = cvorovi.front();
		cvorovi.pop();
		
		auto begin = G.lista_susedstva[pom].begin();
		auto end = G.lista_susedstva[pom].end();
		
		while(begin != end){
			if(!G.posecen[*begin]){
				G.posecen[*begin] = true;
				G.roditelj[*begin] = pom;
				cvorovi.push(*begin);
			}else if(G.roditelj[pom] != *begin)
				return true;
			
			begin++;
		}
	}
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
	
	if(BFS(G, 0))
		cout << "Graf ima ciklus\n";
	else
		cout << "Graf nema ciklus\n";
	
	return 0;
}
