#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void izgradi(std::vector<int> &niz, vector<int> &drvo, int k, int x, int y){
	if(x == y){
		drvo[k] = niz[x];
		return;
	}
	int sredina = (x+y)/2;
	izgradi(niz, drvo, 2*k, x, sredina);
	izgradi(niz, drvo, 2*k+1, sredina+1, y);

	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int main(){
	int n;
	cin >> n;

	vector<int> niz(n);
	for(int i=0; i<n; i++)
		cin >> niz[i];

	int visina = ceil(log2(n));
	int size = 2*pow(2, visina);

	vector<int> drvo(size);
	izgradi(niz, drvo, 1, 0, n-1);
	
	for(int x : drvo)
		cout << x << " ";
	cout << endl;

	return 0;
}