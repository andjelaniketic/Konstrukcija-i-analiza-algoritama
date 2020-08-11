#include <iostream>
#include <vector>

using namespace std;

struct Graph{
	vector<vector<int>> lista_povezanosti;
	int V;
	vector<bool> poseceni;
	
	//promenljiva koja govori da li smo dosli do ciljanog cvora
	bool nadjen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.poseceni.resize(V, false);
	G.lista_povezanosti.resize(V);
	
	G.nadjen = false;
}

void dodaj_granu(Graph &G, int u, int v){
	//dodajemo u listu povezanosti za cvor u, cvor v
	G.lista_povezanosti[u].push_back(v);
}

//pamticemo put kojim smo dosli do ciljanog cvora, u je pocetni a v ciljani, rez cuva putanju
bool DFS(Graph &G, int u, int v, vector<int> &rez){
	if(u == v){
		rez.push_back(v);
		G.nadjen = true;
		return true;
	}
	
	G.poseceni[u] = true;
	rez.push_back(u);
	
	//uzimamo vector suseda cvora u i iteriramo kroz njih
	auto begin = G.lista_povezanosti[u].begin();
	auto end = G.lista_povezanosti[u].end();
	
	while(begin != end){
		bool povratna_vr = false;
		
		//rekurzivni poziv
		if(!G.poseceni[*begin] && !G.nadjen)
			povratna_vr = DFS(G, *begin, v, rez);
		
		if(povratna_vr)
			return true;
		
		//ako smo dosli dovde, znaci da put iz trenutnog cvora ne vodi do ciljanog, dakle popujemo ga i idemo na sledeceg suseda
		rez.pop_back();
		begin++;
	}
	//ako smo dovde dosli znaci ne postoji put od u do v
	return false;
}

bool get_nadjen(const Graph &G){
	return G.nadjen;
}

int main(){
	int u, v;
	cin >> u >> v;
	
	Graph G;
	inicijalizacija(G, 5);
	
	dodaj_granu(G, 0, 1);
	dodaj_granu(G, 1, 2);
	dodaj_granu(G, 1, 3);
	dodaj_granu(G, 3, 4);

	vector<int> rez;
	
	if(DFS(G, u, v, rez)){
		int i;
		for(i=0; i<rez.size()-1; i++)
			cout << rez[i] << " ->";
		cout << rez[i] << endl;
	}else
		cout << "Nema puta\n";
	
	return 0;
}
