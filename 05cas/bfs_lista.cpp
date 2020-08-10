#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> poseceni;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	//nijedan cvor nije posecen, alokacija za V boolova
	G.poseceni.resize(V, false);
	//alokacija za V vectora
	G.lista_susedstva.resize(V);
}

void dodaj_granu(Graph &G, int u, int v){
	//dodajemo granu iz cvora u u cvor v
	//tj u lista_susedstva cvora u dodajemo cvor v
	G.lista_susedstva[u].push_back(v);
}

//obilazak u sirinu odnosno po nivoima
//obilaze se deca korena pa zatim redom njihova deca itd
//zato koristimo strukturu red u koju cemo cuvati decu svakog trenutnog cvora
void BFS(Graph &G, int u){
	//koristimo red za cuvanje cvorova grafa
	queue<int> cvorovi;
	//dodajemo pocetni
	cvorovi.push(u);
	
	int pom;
	
	G.poseceni[u] = true;
	
	while(!cvorovi.empty()){
		pom = cvorovi.front();
		cvorovi.pop();
		
		cout << pom << " ";
		
		auto begin = G.lista_susedstva[pom].begin();
		auto end = G.lista_susedstva[pom].end();
		
		while(begin != end){
			//dodajemo u red cvorove koji nisu obradjeni iz liste susedstva redom svih cvorova
			if(!G.poseceni[*begin]){
				G.poseceni[*begin] = true;
				cvorovi.push(*begin);
			}
			begin++;
		}
	}
	cout << endl;
}

int main(){
	int v;
	cin >> v;
	
	Graph G;
	inicijalizacija(G, 6);
	
	dodaj_granu(G, 0, 1);
	dodaj_granu(G, 0, 2);
	dodaj_granu(G, 1, 3);
	dodaj_granu(G, 1, 4);
	dodaj_granu(G, 2, 3);
	dodaj_granu(G, 4, 5);
	
	BFS(G, v);
	
	return 0;
}
