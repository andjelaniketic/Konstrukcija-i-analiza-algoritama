#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

class Graph{
public:
	//konstruktor
	Graph(int V){
		this->V = V;
		visited.resize(V);
		fill(visited.begin(), visited.end(), false);
		
		matrix = (int**) malloc(V * sizeof(int*));
		
		for(int i=0; i<V; i++)
			matrix[i] = (int*) calloc(sizeof(int), V);
	}
	//destruktor
	~Graph(){
		for(int i=0; i<V; i++)
			free(matrix[i]);
		free(matrix);
	}
	//funkcije
	void dodaj_granu(int u, int v){
		//stavljamo da postoji grana izmedju ova 2 cvora
		matrix[u][v] = 1;
	}
	
	void BFS(int u){
		queue<int> nodes;
		visited[u] = true;
		
		nodes.push(u);
		
		int pom;
		
		while(!nodes.empty()){
			pom = nodes.front();
			nodes.pop();
			cout << pom << " ";
			
			for(int i=0; i<V; i++){
				//ako nije posecen cvor i && ako postoji grana izmedju pom i i
				if(!visited[i] && matrix[pom][i]){
					visited[i] = true;
					nodes.push(i);
				}
			}
		}
		cout << endl;
	}
private:
	int V;
	int **matrix;
	vector<bool> visited;
};

int main(){
	int v;
	cin >> v;
	
	Graph g(4);
	
	g.dodaj_granu(0, 1);
	g.dodaj_granu(0, 2);
	g.dodaj_granu(1, 2);
	g.dodaj_granu(2, 0);
	g.dodaj_granu(2, 3);
	g.dodaj_granu(3, 3);
	
	g.BFS(v);
	
	return 0;
}
