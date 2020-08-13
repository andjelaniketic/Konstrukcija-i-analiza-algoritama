#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

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

bool topolosko(Graph &G, vector<int> &rez){
	queue<int> red_cvorova;
	
	for(int i=0; i<G.V; i++)
		if(G.ulazni_stepen[i] == 0)
			red_cvorova.push(i);
	
	int trenutni;
	while(!red_cvorova.empty()){
		trenutni = red_cvorova.front();
		red_cvorova.pop();
		
		rez.push_back(trenutni);
		
		for(int sused : G.lista_susedstva[trenutni]){
			G.ulazni_stepen[sused]--;
			
			if(G.ulazni_stepen[sused] == 0)
				red_cvorova.push(sused);
		}
	}
	return accumulate(G.ulazni_stepen.begin(), G.ulazni_stepen.end(), 0) == 0; //vraca true ako su svi ispunjeni, ako ne onda false
}

int main(){
	Graph G;
	int n, k, x;
	
	//br profesora
	cin >> n;
	inicijalizacija(G, n);
	
	for(int i=0; i<n; i++){
		//br profesora ciji su potpisi potrebni
		cin >> k;
		
		//potrebni profesori, numeracija krece od 1
		for(int j=0; j<k; j++){
			cin >> x;
			dodaj_granu(G, x-1, i);
		}
	}
	
	vector<int> rez;
	
	if(topolosko(G, rez)){
		cout << "DA\n";
		
		for(int x : rez)
			cout << x << endl;
	}
	else
		cout << "NE\n";
	
	return 0;
}
