#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Graph
{
	vector<vector<int>> lista_suseda;
	int V;
	vector<bool> posecen;

	vector<int> roditelj;
	vector<int> ulazna;
	vector<int> izlazna;
	vector<int> artikulacione;
	int pocetna_num;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);

	G.roditelj.resize(V, -1);
	G.pocetna_num = 0;
	G.ulazna.resize(V, -1);
	G.izlazna.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
}

void DFS(Graph &G, int u){
	G.posecen[u] = true;
	G.ulazna[u] = G.izlazna[u] = G.pocetna_num;

	G.pocetna_num++;
	int deca = 0;

	auto begin = G.lista_suseda[u].begin();
	auto end = G.lista_suseda[u].end();
	while(begin != end){
		if(!G.posecen[*begin]){
			G.roditelj[*begin] = u;
			DFS(G, *begin);
			
			deca++;
			//ako sused cvora u, ima nizu izlaznu vrednost, znaci da se do njega moze daci najranije od cvora cija je ulazna num ista kao izlazna num tog cvora, azuriramo na nizu vrednost jer je onda cvor sto raniji
			G.izlazna[u] = min(G.izlazna[u], G.izlazna[*begin]);
			//u je art ako je koreni cvor i ima bar 2 dece koja nisu medjusobno povezana
			if(G.roditelj[u] == -1 && deca > 1)
				G.artikulacione.push_back(u);
			//ali ako cvor nije koreni i ulazna num mu je manja ili jednaka izlaznoj num svog suseda, on je art tacka
			if(G.roditelj[u]!=-1 && G.ulazna[u] <= G.izlazna[*begin])
				G.artikulacione.push_back(u);
		}
		//dosli smo do cvora koji je vec posecen a nije roditelj trenutnog, tom cvoru onda azuriramo izlaznu num na manju medju izlaznim num njega i tog suseda
		else if (*begin != G.roditelj[u]){
			G.izlazna[u] = min(G.izlazna[u], G.izlazna[*begin]);
		}
		begin++;
	}

}
void is_biconected(Graph &G){
	DFS(G, 0);

	//ako graf ima art tacke ili postoje neposeceni cvorovi onda nije bipovezan
	if(G.artikulacione.size()>0 || count_if(G.posecen.begin(), G.posecen.end(), [](bool is_visited){return is_visited == false; }) > 0){
		cout << "NO\n";
	}
	else
		cout << "YES\n";
}

int main(){
	int V, E;
	cin >> V >> E;
	Graph G;

	inicijalizacija(G, V);

	int u, v;
	for(int i=0; i<E; i++){
		cin >> u >> v;
		dodaj_granu(G, u, v);
	}

	is_biconected(G);

	return 0;
}