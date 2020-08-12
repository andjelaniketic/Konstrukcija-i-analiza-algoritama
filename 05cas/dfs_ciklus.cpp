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
	//usmeren graf
	G.lista_povezanosti[u].push_back(v);
}

//u je pocetni cvor iz kog krecemo pretragu za ciklusom
bool DFS(Graph &G, int u){
	G.posecen[u] = true;
	
	auto begin = G.lista_povezanosti[u].begin();
	auto end = G.lista_povezanosti[u].end();
	
	while(begin != end){
		if(G.posecen[*begin])
			return true;
		else if (DFS(G, *begin)){
			//ako ovaj rek poziv vrati true znaci da smo u nekom podgrafu nasli ciklus te vracamo true
			return true;
		}
		begin++;
	}
	
	//presli smo sve susede trenutnog cvora i nismo nasli ciklus
	//znaci moramo da se vratimo u prethodni
	G.posecen[u] = false;
	return false;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int u, v;
	while(cin >> u >> v){
		dodaj_granu(G, u, v);
	}
	
	if(DFS(G, 0))
		cout << "Postoji ciklus\n";
	else
		cout << "Ne postoji ciklus\n";
	
	return 0;
}
