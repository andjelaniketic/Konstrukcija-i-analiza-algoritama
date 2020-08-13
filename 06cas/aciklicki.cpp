#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> ulazni_stepen;
	
	vector<int> pozicija_top;
	vector<pair<int, int>> grane;
	vector<pair<int, int>> neusmerene_grane;
	vector<pair<int, int>> dodate_grane;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	G.ulazni_stepen.resize(V, 0);
	
	G.pozicija_top.resize(V, -1);
}

void dodaj_usmerenu_granu(Graph &G, int u, int v){
	G.lista_susedstva[u].push_back(v);
	G.ulazni_stepen[v]++;
	
	pair<int, int> p(u, v);
	G.grane.push_back(p);
}

void dodaj_neusmerenu_granu(Graph &G, int u, int v){
	pair<int, int> p(u, v);
	
	G.neusmerene_grane.push_back(p);
}

void topolosko(Graph &G){
	queue<int> red_cvorova;
	
	for(int i=0; i<G.V; i++){
		if(G.ulazni_stepen[i] == 0)
			red_cvorova.push(i);
	}
	
	int trenutni;
	int pozicija = 0;
	
	while(!red_cvorova.empty()){
		trenutni = red_cvorova.front();
		red_cvorova.pop();
		
		G.pozicija_top[trenutni] = pozicija;
		pozicija++;
		
		for(int sused : G.lista_susedstva[trenutni]){
			G.ulazni_stepen[sused]--;
			if(G.ulazni_stepen[sused] == 0)
				red_cvorova.push(sused);
		}
	}
}
//modifikovan DFS koji proverava da li usmereni graf ima ciklus
bool DFS(Graph &G, int u){
	G.posecen[u] = true;
	
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	
	while(begin != end){
		if(G.posecen[*begin])
			return true;
		else if(DFS(G, *begin))
			return true;
		
		begin++;
	}
	G.posecen[u] = false;
	return false; // nema ciklusa na ovom putu
}

void dodeli_usmerenje(Graph &G){
	topolosko(G);
	
	//prolazimo kroz neusmerene_grane
	for(auto p : G.neusmerene_grane){ //p(u, v)
		//ako je u pre v u topoloskom sortiranju, dodajemo granu u->v
		if(G.pozicija_top[p.first] < G.pozicija_top[p.second]){
			dodaj_usmerenu_granu(G, p.first, p.second);
			
			pair<int, int> tmp(p.first, p.second);
			G.dodate_grane.push_back(tmp);
		}else {
			dodaj_usmerenu_granu(G, p.second, p.first);
			
			pair<int, int> tmp(p.second, p.first);
			G.dodate_grane.push_back(tmp);
		}
	}
	//da li ima ciklus nakon ovog dodavanja
	if(DFS(G, 0))
		cout << "Ima ciklus\n";
	else
		cout << "Nema ciklus\n";
	
	cout << "sve grane:\n";

	for(auto p : G.grane)
		cout << p.first << " -> " << p.second << endl;
	
	cout << "dodate:\n";
	for(auto p : G.dodate_grane)
		cout << p.first << " -> " << p.second << endl;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	inicijalizacija(G, V);
	
// 	dodaj_usmerenu_granu(G, 0, 1);
// 	dodaj_usmerenu_granu(G, 0, 5);
// 	dodaj_usmerenu_granu(G, 1, 2);
// 	dodaj_usmerenu_granu(G, 1, 3);
// 	dodaj_usmerenu_granu(G, 1, 4);
// 	dodaj_usmerenu_granu(G, 2, 4);
// 	dodaj_usmerenu_granu(G, 3, 4);
// 	dodaj_usmerenu_granu(G, 5, 1);
// 	dodaj_usmerenu_granu(G, 5, 2);
// 	
// 	dodaj_neusmerenu_granu(G, 0, 2);
// 	dodaj_neusmerenu_granu(G, 0, 3);
// 	dodaj_neusmerenu_granu(G, 4, 5);

	int n, m;
	cin >> n >> m;
	int u, v;
	
 	cout << "unesi usmerene grane\n";
 	
 	for(int i=0; i<n; i++){
 		cin >> u >> v;
 		dodaj_usmerenu_granu(G, u, v);
 	}
 	
 	cout << "unesi neusmerene grane\n";
 	
 	for(int i=0; i<m; i++){
 		cin >> u >> v;
 		dodaj_neusmerenu_granu(G, u, v);
 	}

	dodeli_usmerenje(G);
	return 0;
}
