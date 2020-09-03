#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void izgradi(vector<int> &niz, vector<int> &drvo, int k, int x, int y)
{
	if(x == y){
		drvo[k] = niz[x];
		return;
	}

	int sredina = (x+y)/2;
	izgradi(niz, drvo, 2*k, x, sredina);
	izgradi(niz, drvo, 2*k+1, sredina+1, y);

	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int suma_segmenta(std::vector<int> &drvo, int x, int y, int a, int b, int k)
{
	if(y<a || x>b)
		return 0;
	if(x>=a && y<=b)
		return drvo[k];

	int s = (x+y)/2;

	return suma_segmenta(drvo, x, s, a, b, 2*k) + 
			suma_segmenta(drvo, s+1, y, a, b, 2*k+1);
}

int main(){
	int n;
	cin >> n;

	std::vector<int> v(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> v[i];
	}

	int visina = ceil(log2(n));
	int size = 2*pow(2, visina);
	std::vector<int> drvo(size);

	izgradi(v, drvo, 1, 0, n-1);

	int a, b;
	cout << "unesi granice segmenata: ";
	cin >> a >> b;

	cout << suma_segmenta(drvo, 0, n-1, a, b, 1) << endl;

	return 0;
}