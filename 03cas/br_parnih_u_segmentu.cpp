#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void izgradi_segmentno(vector<int> &niz, vector<int> &drvo, int k, int x, int y){
	if(x == y){
		//ako je broj paran ubacujemo 1 kao indikator da je paran, inace 0
		if(niz[x] % 2 == 0)
			drvo[k] = 1;
		else
			drvo[k] = 0;
		return;
	}
	
	int s = (x+y)/2;
	
	izgradi_segmentno(niz, drvo, 2*k+1, x, s);
	izgradi_segmentno(niz, drvo, 2*k+2, s+1, y);
	
	//indeksiranje je od 0
	drvo[k] = drvo[2*k+1] + drvo[2*k+2];
}

int prebroj_parne(vector<int> &drvo, int x, int y, int a, int b, int k){
	
	if(x>b || y<a)
		return 0;
	if(x>=a && y<=b)
		return drvo[k];
	
	int s = (x+y)/2;
	
	return prebroj_parne(drvo, x, s, a , b, 2*k+1) + prebroj_parne(drvo, s+1, y, a, b, 2*k+2);
	
}

int main(){
	vector<int> niz = {1, 2, 3, 4, 5, 6, 7, 8};
	int n = niz.size();
	
	int visina = ceil(log2(n));
	int size = 2* pow(2, visina) -1;
	
	vector<int> drvo(size);
	izgradi_segmentno(niz, drvo, 0, 0, n-1);
	
	int a, b;
	cin >> a >> b;
	cout << prebroj_parne(drvo, 0, n-1, a, b, 0) << "\n";
	
	return 0;
}
