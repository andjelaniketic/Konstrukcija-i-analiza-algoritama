#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_povezanosti;
	int V;
	vector<bool> posecen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.posecen.resize(V, false);
	G.lista_povezanosti.resize(V);
}

void dodaj_granu(Graph &G, int u, int v){
	G.lista_povezanosti[u].push_back(v);
}

void DFS(Graph &G, int u, int v, vector<int> rez){
	if(u == v){
		rez.push_back(v);
		int i;
		for(i=0; i<rez.size()-1; i++)
			cout << rez[i] << "->";
		cout << rez[i] << endl;
		
		return;
	}
	
	G.posecen[u] = true;
	rez.push_back(u);
	
	auto begin = G.lista_povezanosti[u].begin();
	auto end = G.lista_povezanosti[u].end();
	
	while(begin != end){
		if(!G.posecen[*begin])
			DFS(G, *begin, v, rez);
		
		begin++;
	}
	//kada zavrsimo sa trazenjem putanje kroz jedan cvor, oznacimo ga kao neposecen, jer mozda postoji druga putanja koja prolazi kroz taj cvor
	G.posecen[u] = false;
}

int main(){
	int u, v;
	cin >> u >> v;
	
	Graph G;
	inicijalizacija(G, 4);
	
	dodaj_granu(G, 0, 1);
	dodaj_granu(G, 0, 2);
	dodaj_granu(G, 0, 3);
	dodaj_granu(G, 2, 0);
	dodaj_granu(G, 2, 1);
	dodaj_granu(G, 1, 3);
	
	vector<int> rez;
	DFS(G, u, v, rez);
	
	return 0;
}
