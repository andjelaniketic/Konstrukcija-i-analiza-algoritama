#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> ulazni_stepen;
	bool nadjen_ciklus;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.ulazni_stepen.resize(V, 0);
	G.nadjen_ciklus = false;
}

void dodaj_granu(Graph &G, int u, int v){
	//usmeren
	G.lista_susedstva[u].push_back(v);
	G.ulazni_stepen[v]++;
}

//u nizu rez cuvamo niz cvorova topolosko sortiranih
void topolosko(Graph &G, vector<int> &rez){
	queue<int> red_cvorova;
	
	//dodajemo sve cvorove ulaznog stepena 0
	for(int i=0; i<G.V; i++){
		if(G.ulazni_stepen[i] == 0)
			red_cvorova.push(i);
	}
	
	int trenutni;
	while(!red_cvorova.empty()){
		trenutni = red_cvorova.front();
		red_cvorova.pop();
		
		rez.push_back(trenutni);
		
		//prolazimo susede i smanjujemo im ulazne stepene
		for(int sused : G.lista_susedstva[trenutni]){
			G.ulazni_stepen[sused]--;
			
			if(G.ulazni_stepen[sused] == 0)
				red_cvorova.push(sused);
		}
	}
}

//u je trenutni cvor, a u niz rez cuvamo rezultujuci ciklus ako postoji
void DFS(Graph &G, int u, vector<int> &rez, int pocetni_cvor){
	//ako ulazimo u posecen cvor, proveravamo da li je on cvor iz kog smo krenuli, ako jeste, nasli smo ciklus
	if(G.posecen[u] && u==pocetni_cvor){
		rez.push_back(u);
		G.nadjen_ciklus = true;
		return;
	}
	//nije posecen
	
	G.posecen[u] = true;
	rez.push_back(u);
	//prolazimo susede
	auto begin = G.lista_susedstva[u].begin();
	auto end = G.lista_susedstva[u].end();
	
	while(begin != end){
		//pozivamo rekurzivno DFS za susede
		if(!G.posecen[*begin])
			DFS(G, *begin, rez, pocetni_cvor);
		begin++;
	}
}

void nadji(Graph &G){
	vector<int> rez_topolosko;
	topolosko(G, rez_topolosko);
	
	//top cuva da li ispisujemo topolosko ili ne
	bool top = true;
	
	//prolazimo sve cvorove i ako naidjemo na cvor ulaznog stepena !=0, ispisujemo ciklus
	for(int i=0; i<G.V; i++){
		if(G.ulazni_stepen[i] != 0)
			top = false;
	}
	
	if(top){
		cout << "topolosko sortiranje: ";
		for(int x : rez_topolosko)
			cout << x << " ";
		cout << endl;
		return;
	}
	
	cout << "Ciklus: ";
	//recikliramo niz za ispis ciklusa
	rez_topolosko.clear();
	
	//pozivamo DFS iz 1. cvora ciji je ulazni stepen >0
	for(int i=0; i<G.V; i++){
		if(G.ulazni_stepen[i] != 0){
			DFS(G, i, rez_topolosko, i);
			
			int j;
			for(j=0; j<rez_topolosko.size()-1; j++)
				cout << rez_topolosko[j] << " -> ";
			cout << rez_topolosko[j] << endl;
			
			return;
		}
	}
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);
	
	nadji(G);
	
	return 0;
}
