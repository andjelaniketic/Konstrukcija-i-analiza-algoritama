#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Graph{
	vector<vector<int>> lista_susedstva;
	int V;
	vector<bool> posecen;
	
	vector<int> roditelj;
};

void inicijalizacija(Graph &G, int V){
	G.V = V;
	G.lista_susedstva.resize(V);
	G.posecen.resize(V, false);
	
	G.roditelj.resize(V, -1);
}

void dodaj_granu(Graph &G, int u, int v){
	//neusmeren
	G.lista_susedstva[u].push_back(v);
	G.lista_susedstva[v].push_back(u);
}

//trazi najkraci put od u do v
void BFS(Graph &G, int u, int v){
	queue<int> cvorovi;
	cvorovi.push(u);
	
	G.posecen[u] = true;
	
	int pom;
	while(!cvorovi.empty()){
		pom = cvorovi.front();
		cvorovi.pop();
		//dosli smo iz u do v, putanja je nadjena
		if(pom == v)
			return;
		
		//inace iteriramo kroz susede trenutnog cvora pom
		auto begin = G.lista_susedstva[pom].begin();
		auto end = G.lista_susedstva[pom].end();
		
		while(begin != end){
			//ako je cvor vec posecen idemo dalje
			//ako nije, posecujemo ga, dodeljujemo mu roditelja i stavljamo u red
			if(!G.posecen[*begin]){
				G.posecen[*begin] = true;
				G.roditelj[*begin] = pom;
				
				cvorovi.push(*begin);
			}
			begin++;
		}
	}
}

//funkcija za ispis putanje
void ispisi_putanju(Graph &G, int u, int v){
	stack<int> putanja;
	
	BFS(G, u, v); //bfs ce popuniti listu roditelja
	
	//ako se ispostavi da v nije u istoj komponenti povezanosti, roditelj mu je i dalje -1, i onda nemamo nikakvu putanju do njega
	if(G.roditelj[v] == -1){
		cout << "Putanja ne postoji\n";
		return;
	}
	//stavljamo ciljani cvor na stek, dakle poslednji ce biti ispisan
	putanja.push(v);
	
	while(G.roditelj[v] != -1){
		v = G.roditelj[v];  //v postaje svoj roditelj, rekonstruisemo put
		putanja.push(v);
	}
	
	int n = putanja.size();
	int x;
	while(n){
		x = putanja.top();
		putanja.pop();
		
		if(n > 1)
			cout << x << " -> ";
		else
			cout << x << endl;
		n--;
	}
}

int main(){
	Graph G;
	int V;
	cin >> V;
	
	inicijalizacija(G, V);
	
	int u, v;
	cin >> u >> v;
	
	int x, y;
	while(cin >> x >> y)
		dodaj_granu(G, x, y);
	
	ispisi_putanju(G, u, v);
	
	return 0;
}
