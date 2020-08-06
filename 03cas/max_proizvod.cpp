#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

//cvor prefiskog stabla gde cuvamo najvecu i drugu najvecu vrednost tog segmenta koji cvor pokriva
struct Node{
	int largest;
	int second_largest;
};

//gradimo stablo i usput dodajemo max vrednosti, cvorovi drveta su tipa Node
void izgradi_segmentno(vector<int> &niz, vector<Node> &drvo, int k, int x, int y){
	//dosli smo do jednoclanog niza(list)
	//u jednoclanom segmentu najveci je taj sam element
	//najmanji cemo staviti da je INT_MIN
	if(x == y){
		drvo[k].largest = niz[x];
		drvo[k].second_largest = INT_MIN;
		return;
	}
	
	int s = (x + y) / 2;
	
	izgradi_segmentno(niz, drvo, 2*k, x, s);
	izgradi_segmentno(niz, drvo, 2*k+1, s+1, y);
	
	/*najveca vrednost ce biti maksimum najvecih vrednosti levog i desnog deteta, a za second_largest bice minimum od sledeca 2:
	maksimum izmedju levog najveceh i desnog second_largest
	maksimum izmedju levog second_largest i desnog najveceg*/
	
	drvo[k].largest = max(drvo[2*k].largest, drvo[2*k+1].largest);
	drvo[k].second_largest = min(max(drvo[2*k].largest, drvo[2*k+1].second_largest), max(drvo[2*k].second_largest, drvo[2*k+1].largest));
	
}

//trazi najveci proizvod u intervalu [a, b]
//to radimo tako sto nadjemo 2 najveca elementa u tom intervalu sto je isto kao kad racunamo sumu elemenata u intervalu
Node nadji_max_proizvod(vector<Node> &drvo, int k, int x, int y, int a, int b){
	Node rez;
	rez.largest = INT_MIN;
	rez.second_largest = INT_MIN;
	
	//nema preklapanja dakle vracamo cvor gde su oba clana INT_MIN
	if(x>b || y<a)
		return rez;
	
	//jedan u drugom su znaci vracamo trenutni koren-cvor
	if(x >=a && y<=b)
		return drvo[k];
	
	int s = (x + y) /2;
	
	Node levi_max = nadji_max_proizvod(drvo, 2*k, x, s, a, b);
	Node desni_max = nadji_max_proizvod(drvo, 2*k+1, s+1, y, a, b);
	
	//azuriramo trenutne najvece vrednosti
	rez.largest = max(levi_max.largest, desni_max.largest);
	rez.second_largest = min(max(levi_max.largest, desni_max.second_largest), max(levi_max.second_largest, desni_max.largest));
	
	return rez;
}

int main(){
	int n;
	cin >> n;
	
	vector<int> niz(n);
	
	for(int i=0; i<n; i++)
		cin >> niz[i];
	
	int visina = ceil(log2(n));
	int size = 2* pow(2, visina);
	
	vector<Node> drvo(size);
	
	izgradi_segmentno(niz, drvo, 1, 0, n-1);
	
	int a, b;
	cin >> a >> b;
	
	Node rez = nadji_max_proizvod(drvo, 1, 0, n-1, a, b);
	cout << rez.largest * rez.second_largest << "\n";
	
	return 0;
}
