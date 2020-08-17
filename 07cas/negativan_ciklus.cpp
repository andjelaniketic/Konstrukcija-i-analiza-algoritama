#include <iostream>
#include <vector>

#define INF 9999

using namespace std;

struct Graph
{
	int V;
	int **matrica;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.matrica = (int**)malloc(V*sizeof(int*));
	for(int i=0; i<V; i++)
		G.matrica[i] = (int*)calloc(sizeof(int), V);

	for(int i=0; i<V; i++)
		for(int j=0; j<V; j++){
			if(i == j)
				G.matrica[i][j] = 0;
			else
				G.matrica[i][j] = INF;
		}
}

void dodaj_granu(Graph &G, int u, int v, int tezina){
	//usmeren
	G.matrica[u][v] = tezina;
}

void flojd_varsal(Graph &G){
	for(int k=0; k<G.V; k++){			//srednji
		for(int j=0; j<G.V; j++){		//pocetni
			for (int i = 0; i < G.V; i++){//krajnji
				//ako je udaljenost pocetnog do krajnjeg preko srednjeg manja od trenutne udaljenosti ta 2, idemo preko srednjeg i azurira se vrednost tog puta
				if (G.matrica[j][i] > G.matrica[j][k] + G.matrica[k][i]){
					G.matrica[j][i] = G.matrica[j][k] + G.matrica[k][i];
				}
			}
		}
	}
	//prodjemo kroz matricu udaljenosti i ispisemo ako je neki cvor udaljen od samog sebe za negativnu vrednost, to oznacava postojanje negativnog ciklusa
	for (int i = 0; i < G.V; i++)
	{
		if (G.matrica[i][i] < 0){
			cout << "postoji negativan ciklus iz cvora " << i << endl;
			return;
		}
	}
	cout << "ne postoji negativan ciklus" << endl;
}

int main(){
	Graph G;
	int V, E;
	cin >> V >> E;
	inicijalizacija(G, V);

	int u, v, tezina;
	for(int i=0; i<E; i++){
		cin >> u >> v >> tezina;
		dodaj_granu(G, u, v, tezina);
	}

	flojd_varsal(G);

	return 0;
}