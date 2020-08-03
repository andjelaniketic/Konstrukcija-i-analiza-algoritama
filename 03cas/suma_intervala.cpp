#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

//implementacija drveta
void izgradi_segmentno(vector<int> &niz, vector<int> &drvo, int k, int x, int y){
	if(x == y){
		drvo[k] = niz[x];
		return;
	}
	
	int s = (x+y)/2;
	
	izgradi_segmentno(niz, drvo, 2*k, x, s);
	izgradi_segmentno(niz, drvo, 2*k+1, s+1, y);
	
	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

//suma el u intervalu [a, b], x i y krajevi pocetnog niza
//k je pozicija cvora u nizu, drvo[k] je suma elemenata koje cuva
/*imamo 3 opcije:
1. [x, y] i trazeni [a, b] se ne preklapaju -> el iz ovog dela nisu relevantni za trazenu sumu, vracamo 0
2. [x, y] je unutar [a, b] -> vracamo drvo[k] jer je to bas onaj koji trazimo
3. segmenti se preklapaju -> delimo [x, y] na dva dela i idemo rek
*/
int suma_segmenta(vector<int> &drvo, int x, int y, int a, int b, int k){
	//segmenti se ne preklapaju
	if(x > b || y < a)
		return 0;
	//poklapaju se
	if(x >= a && y <= b)
		return drvo[k];
	//preklapaju se
	int s = (x+y)/2;
	return suma_segmenta(drvo, x, s, a, b, 2*k) + suma_segmenta(drvo, s+1, y, a, b, 2*k+1);
}

void ispisi(vector<int> &drvo){
	for(int x : drvo)
		cout << x << " ";
	cout << "\n";
}

int main(){
	vector<int> niz = {1, 2, 3, 4, 5, 6, 7, 8};
	int n = niz.size();
	cout << n << "\n";
	
	int visina = ceil(log2(n));
	int size = 2* pow(2, visina);
	
	vector<int> drvo(size);
	
	izgradi_segmentno(niz, drvo, 1, 0, n-1);
	
	ispisi(drvo);
	
	cout << suma_segmenta(drvo, 0, n-1, 0, 2, 1) << "\n";
	return 0;
}
