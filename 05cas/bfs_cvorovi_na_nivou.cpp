#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> nivo;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.nivo.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_susedstva[u].push_back(v);
}

//odredjuje broj cvorova na nivou
void BFS(Graph &G, int u, int nivo){
	queue<int> cvorovi;
	cvorovi.push(u);
	
	G.posecen[u] = true;
	
	int trenutni_nivo = 0;
	G.nivo[u] = trenutni_nivo;
	
	int pom;
	while(!cvorovi.empty()){
		pom = cvorovi.front(); //trenutni roditelj
		cvorovi.pop();
		
		auto begin = G.lista_susedstva[pom].begin();
		auto end = G.lista_susedstva[pom].end();
		
		while(begin != end){
			if(!G.posecen[*begin]){
				G.posecen[*begin] = true;
				G.nivo[*begin] = G.nivo[pom] + 1;
				//^jer je potomak cvora na nivou trenutni_nivo
				cvorovi.push(*begin);
			}
			begin++;
		}
	}
	//broji samo one koji su na odgovarajucem nivou
	cout << count_if(G.nivo.begin(), G.nivo.end(), [&nivo](int x){ return x == nivo; }) << endl;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int nivo;
	cin >> nivo;
	
	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);
	
	BFS(G, 0, nivo);
	
	return 0;
}
