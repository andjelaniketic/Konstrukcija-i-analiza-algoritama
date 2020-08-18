#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<int> times;
	vector<int> low_times;
	stack<int> stek;
	vector<bool> na_steku;
	int pocetni_times;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.times.resize(V, -1);
	G.low_times.resize(V, -1);
	G.pocetni_times = 0;
	G.na_steku.resize(V, false);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_suseda[u].push_back(v);
}

void DFS_tarjan(Graph &G, int u){
	//postavljamo times da trenutne vrednosti;
	G.times[u] = G.low_times[u] = G.pocetni_times;
	G.pocetni_times++;
	//stavljamo na stek
	G.stek.push(u);
	G.na_steku[u] = true;
	//obilazak suseda
	for(int sused : G.lista_suseda[u]){
		if(G.times[sused] == -1){
			///ovo znaci da cvor jos nije posecen
			DFS_tarjan(G, sused);
			//po povratku iz rekurzije, proveravamo da li se do trenutnog cvora moze doci preko suseda ranije u stablu
			G.low_times[u] = min(G.low_times[sused], G.low_times[u]);
		}
		//sused je vec posecen, pitamo se da li je na steku
		else if(G.na_steku[sused]){
			//proveravamo da li se preko suseda moze doci do u, tj da li se on nalazi ranije od njega u stablu
			G.low_times[u] = min(G.low_times[u], G.times[sused]);
		}
	}
	//koren komponente jake povezanosti ima jednake times
	if(G.times[u] == G.low_times[u]){
		//na steku ce biti naslagane sve komponente vezane za taj cvor, s tim da je on ispod svih njih
		while(1){
			int v = G.stek.top();
			G.stek.pop();
			G.na_steku[v] = false;
			cout << v << " ";
			//ako smo dosli do njega, prekidamo petlju
			if(v == u){
				cout << endl;
				break;
			}
		}
	}
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

	DFS_tarjan(G, 0);

	return 0;
}