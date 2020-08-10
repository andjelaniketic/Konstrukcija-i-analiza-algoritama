#include <iostream>
#include <vector>

using namespace std;

class graph{
public:
	//konstruktor koji samo prima broj cvorova grafa
	graph(int V){
		this->V = V;
		matrix = (int**) malloc(V*sizeof(int*));
		
		for(int i=0; i<V; i++)
			matrix[i] = (int*) calloc(sizeof(int), V);
		//klasicna alokacija memorije za matricu VxV
		
		//alokacija za V bool-ova koje ce cuvati posecene cvorove
		visited.resize(V);
		fill(visited.begin(), visited.end(), false);
	}
	//destruktor za klasu graph
	//sluze za oslobadjanje resursa, poziva se uvek kada objekat prestaje da postoji
	~graph(){
		//oslobadjanje svake kolone matrice
		for(int i=0; i<V; i++)
			free(matrix[i]);
		//oslobadjanje vrsta
		free(matrix);
	}
	
	void dodaj_granu(int u, int v){
		matrix[u][v] = 1;
	}
	
	//obilazak u dubinu, argument je pocetni cvor
	void DFS(int v){
		visited[v] = true;
		//oznacili smo da je posecen, obradjujemo ga
		cout << v << " ";
		
		//rekurzivno obilazimo susede
		for(int i=0; i<V; i++){
			if(matrix[v][i] && !visited[i])
				DFS(i);
		}
	}
	
private:
	//broj cvorova
	int V;
	//matrica susedstva
	int **matrix;
	//lista posecenih cvorova
	vector<bool> visited;
};

int main(){
	int v;
	
	cin >> v;
	
	graph g(4);
	
	g.dodaj_granu(0, 1);
	g.dodaj_granu(0, 2);
	g.dodaj_granu(1, 2);
	g.dodaj_granu(2, 0);
	g.dodaj_granu(2, 3);
	g.dodaj_granu(3, 3);

	g.DFS(v);
	
	cout << endl;
	
	return 0;
}
