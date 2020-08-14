#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Graph{
	vector<vector<int>> lista_suseda;
	int V;
	vector<bool> posecen;

	vector<int> roditelj;
	vector<int> ulazna_num;
	vector<int> izlazna_num;
	set<int> artikulacione_tacke;
	int pocetna_num;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
	G.posecen.resize(V, false);

	G.roditelj.resize(V, -1);
	G.pocetna_num = 0;
	G.ulazna_num.resize(V, -1);
	G.izlazna_num.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren graf
	G.lista_suseda[u].push_back(v);
	G.lista_suseda[v].push_back(u);
}
//obilazak grafa u dubinu pocev od cvora u
void DFS(Graph &G, int u){
	G.posecen[u] = true;

	//postavljamo vremena obilaska trenutnog cvora
	G.ulazna_num[u] = G.izlazna_num[u] = G.pocetna_num;

	//povecavamo pocetnu num zbog narednog cvora
	G.pocetna_num++;

	int deca = 0;

	//obilazimo susede
	auto begin = G.lista_suseda[u].begin();
	auto end = G.lista_suseda[u].end();

	while(begin != end){
		if (!G.posecen[*begin]){
			//dodeljujemo mu roditelja i pozivamo rekurzivno
			G.roditelj[*begin] = u;
			DFS(G, *begin);

			deca++;
			//ako je izlazna numeracija suseda manja od trenutnog cvora, to znaci da postoji put koji preko tog suseda vodi nazad do trenutnog cvora
			G.izlazna_num[u] = min(G.izlazna_num[*begin], G.izlazna_num[u]);

			//ako je u, koreni cvor i ima bar 2 dece koja su nepovezana onda on jeste artikulaciona tacka
			if(G.roditelj[u] == -1 && deca > 1)
				G.artikulacione_tacke.insert(u);
			//ako cvor nije koreni, ali njegova ulazna num<= izlazna bilo kog od njegovih suseda, onda jeste art
			if(G.roditelj[u] != 1 && G.ulazna_num[u] <= G.izlazna_num[*begin])
				G.artikulacione_tacke.insert(u);
		}//ako je sused posecen vec i nije roditelj cvora u, proveravamo da li mu je ulazna num < od izlazne num cvora u i azuriramo izlaznu za u
		else if (*begin != G.roditelj[u])
			G.izlazna_num[u] = min(G.ulazna_num[*begin], G.izlazna_num[u]);

		begin++;
	}
}

void nadji_artikulacione_tacke(Graph &G, int u){
	DFS(G, u);
	for(int x : G.artikulacione_tacke)
		cout << x << " ";
	cout << endl;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	inicijalizacija(G, V);

	int w;
	cin >> w;

	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);

	nadji_artikulacione_tacke(G, w);

	return 0;
}