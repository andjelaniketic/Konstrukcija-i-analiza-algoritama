#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

//u roditeljima cuvamo vece vrednosti od njihovih potomaka
void izgradi_stablo(vector<int> &niz, vector<int> &drvo, int k, int x, int y){
	if (x == y){
		drvo[k] = niz[x];
		return;
	}
	
	int s = (x + y) / 2;
	
	izgradi_stablo(niz, drvo, 2*k, x, s);
	izgradi_stablo(niz, drvo, 2*k+1, s+1, y);
	
	drvo[k] = max(drvo[2*k], drvo[2*k+1]);
}

int max_el_segmenta(vector<int> &drvo, int x, int y, int a, int b, int k){
	//ako nema preklapanja, vracamo INT_MIN jer zelimo da kazemo da
	//ovaj segment nije vazan za konacni rezultat
	if (x>b || y<a)
		return INT_MIN;
	
	//ako je [x, y] unutar [a, b], vracamo max el iz [x, y], a on je smesten u korenu
	if (x>=a && y<=b)
		return drvo[k];
	
	int s = (x + y) / 2;
	
	return max(max_el_segmenta(drvo, x, s, a, b, 2*k), max_el_segmenta(drvo, s+1, y, a, b, 2*k+1));
}

int main(){
	vector<int> niz = {1, 2, 3, 4, 5, 6, 7, 8};
	int n = niz.size();
	
	int visina = ceil(log2(n));
	int size = 2 * pow(2, visina);
	
	vector<int> drvo(size);
	
	izgradi_stablo(niz, drvo, 1, 0, n-1);
	
	for(int x : drvo)
		cout << x << " ";
	cout << "\n";
	int a, b;
	cin >> a >> b;
	
	cout << max_el_segmenta(drvo, 1, n-1, a, b, 1) << "\n";
	
	return 0;
}
