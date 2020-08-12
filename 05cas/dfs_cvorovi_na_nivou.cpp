#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	int cvorova_na_nivou;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.cvorova_na_nivou = 0;
}

void dodaj_granu(Graph &G, int u, int v){
	G.lista_susedstva[u].push_back(v);
}

void DFS(Graph &G, int u, int nivo, int trenutni_nivo){
	G.posecen[u] = true;
	
	if(trenutni_nivo == nivo)
		G.cvorova_na_nivou++; //ovde je rez
	
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	
	while(begin != end){
		if(!G.posecen[*begin])
			DFS(G, *begin, nivo, trenutni_nivo + 1);
			//kad pozovemo za suseda trenutnog cvora, silazimo za nivo nize
		begin++;
	}
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	int nivo;
	cin >> nivo;
	
	inicijalizacija(G, V);
	
	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);
	
	DFS(G, 0, nivo, 0);
	
	cout << G.cvorova_na_nivou << endl;
	
	return 0;
}
