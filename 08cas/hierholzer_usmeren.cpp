#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Graph
{
	int V;
	vector<vector<int>> lista_suseda;
	vector<int> ojlerov_put;
	stack<int> stek;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_suseda.resize(V);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_suseda[u].push_back(v);
}

void hierholzer(Graph &G){
	G.stek.push(0);

	int trenutni = 0;
	int tmp;
	while(!G.stek.empty()){
		if(G.lista_suseda[trenutni].size()){
			G.stek.push(trenutni);
			//pamtimo ka kom cvoru vodi grana, i uklanjamo je
			tmp = G.lista_suseda[trenutni].back();
			G.lista_suseda[trenutni].pop_back();
			//trenutni je sad tajcvor do kog je vodila grana
			trenutni = tmp;
		}
		else{
			//nema vise grana iz cvora, dodajemo ga u ojlerov ciklus
			G.ojlerov_put.push_back(trenutni);
			//vracamo se nazad u cvor iz koga smo dosli
			trenutni = G.stek.top();
			G.stek.pop();
		}
	}
	int i;
	//ispisujemo putanju koju smo nasli ali obrnuto
	//jer smo je tako pravili
	for(i = G.ojlerov_put.size()-1; i>=1; i--)
		cout << G.ojlerov_put[i] << " -> ";
	cout << G.ojlerov_put[i] << endl;
}

int main()
{
	Graph G;
	int V, E;
	cin >> V >> E;

	inicijalizacija(G, E);

	int u, v;
	for (int i = 0; i < E; ++i)
	{
		cin >> u >> v;
		dodaj_granu(G, u, v);
	}

	hierholzer(G);
	return 0;
}