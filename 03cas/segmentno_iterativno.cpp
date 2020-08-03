#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void izgradi_segmentno(vector<int> &niz, vector<int> &drvo, int n){
	//kopiramo sve elemente iz niza u drvo
	//ova funkcija kopira n elemenata iz jednog niza u drugi
	//argumenti su pocetak prvog niza/pozicija odakle krece, broj el
	//i pozicija odakle krece u 2. nizu
	copy_n(niz.begin(), n, drvo.begin() +n);
	
	//roditelj ima decu na pozicijama 2k i 2k+1
	//upisujemo njihove vrednosti
	//dakle gradimo stablo odozdo na gore
	for(int k = n-1; k>=1; k--)
		drvo[k] = drvo[2*k] + drvo[2*k+1];
	
}

int main() {
	
	vector<int> niz = {1, 2, 3, 4, 5, 6, 7, 8};
	int n = niz.size();
	
	int visina = ceil(log2(n));
	int size = 2* pow(2, visina);
	
	vector<int> drvo(size);
	
	izgradi_segmentno(niz, drvo, n);
	
	for(int x : drvo)
		cout << x << " ";
	cout << "\n";
	
	return 0;
}
