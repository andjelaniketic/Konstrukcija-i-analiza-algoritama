#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> ulazni_stepen;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.ulazni_stepen.resize(V, 0);
}

void dodaj_granu(Graph &G, int u, int v){
	//usmereni graf
	G.lista_susedstva[u].push_back(v);
	
	G.ulazni_stepen[v]++;
}

void topolosko_sortiranje(Graph &G){
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
		
		cout << trenutni << " ";
		//prolazimo sve susede trenutnog cvora i smanjujemo im ulazne stepene
		for(int sused : G.lista_susedstva[trenutni]){
			G.ulazni_stepen[sused]--;
			//ako je neki sused dobio sada ulazni stepen 0, mozemo da ga dodamo u red
			if(G.ulazni_stepen[sused] == 0)
				red_cvorova.push(sused);
		}
	}
	cout << endl;
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int u, v;
	while(cin >> u >> v)
		dodaj_granu(G, u, v);
	
	topolosko_sortiranje(G);
	
	return 0;
}
