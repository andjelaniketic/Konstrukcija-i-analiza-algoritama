#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//k pozicija cvora u nizu (indeks), x i y su krajevi intervala
//na pocetku je interval ceo niz, a kroz rek poziva se polovi
void izgradi_segmentno(vector<int> &niz, vector<int>&drvo, int k, int x, int y){
	//slucaj lista tj deteta dakle k je bas pozicija na koju on ide
	if(x == y){
		drvo[k] = niz[k];
		return;
	}
	
	int s = (x + y)/2;
	
	//rek pozivi za levi i desni potomak
	izgradi_segmentno(niz, drvo, 2*k, x, s);
	izgradi_segmentno(niz, drvo, 2*k+1, s+1, y);
	
	//najbitniji deo!!
	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int main(){
	int n;
	cin >> n;
	
	vector<int> niz(n);
	int x;
	
	for(int i=0; i<n; i++){
		cin >> x;
		niz.push_back(x);
	}
	
	int visina = ceil(log2(n));
	int size = 2* pow(2, visina);
	
	vector<int> drvo(size);
	
	izgradi_segmentno(niz, drvo, 1, 0, n-1);
	
	for(int x : drvo)
		cout << x << " ";
	cout << "\n";
	
	return 0;
}
