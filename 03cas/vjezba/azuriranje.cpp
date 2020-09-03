#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void izgradi(vector<int> &niz, vector<int> &drvo, int x, int y, int k)
{
	if(x == y){
		drvo[k] = niz[x];
		return;
	}

	int s = (x+y)/2;
	izgradi(niz, drvo, x, s, 2*k);
	izgradi(niz, drvo, s+1, y, 2*k+1);

	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

void ispisi(vector<int> &drvo)
{
	for(int x : drvo)
		cout << x << " ";
	cout << endl;
}

void azuriraj(vector<int> &drvo, int x, int y, int k, int index, int nova_vr)
{
	if(x == y){
		drvo[k] = nova_vr;
		return;
	}

	int s = (x+y)/2;

	if(index <= s)
		azuriraj(drvo, x, s, 2*k, index, nova_vr);
	else
		azuriraj(drvo, s+1, y, 2*k+1, index, nova_vr);

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
	izgradi(niz, drvo, 0, n-1, 1);

	cout << "unesi izmenu: ";
	int index, nova_vr;
	cin >> index >> nova_vr;

	azuriraj(drvo, 0, n-1, 1, index, nova_vr);
	ispisi(drvo);

	return 0;
}