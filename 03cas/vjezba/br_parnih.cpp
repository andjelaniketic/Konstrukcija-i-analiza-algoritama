#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void izgradi(vector<int> &niz, vector<int> &drvo, int x, int y, int k)
{
	if(x == y){
		//cuvacemo kao 1 i 0 pa posle samo vratiti sumu
		if(niz[x]%2 == 0)
			drvo[k] = 1;
		else
			drvo[k] = 0;
		return;
	}

	int s = (x+y)/2;

	izgradi(niz, drvo, x, s, 2*k);
	izgradi(niz, drvo, s+1, y, 2*k+1);

	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int prebroj_parne(vector<int> &drvo, int x, int y, int a, int b, int k)
{
	if(x>b || y<a)
		return 0;

	if(x>=a && y<=b)
		return drvo[k];

	int s = (x+y)/2;

	return prebroj_parne(drvo, x, s, a, b, 2*k) + 
			prebroj_parne(drvo, s+1, y, a, b, 2*k+1);
}

int main(){

	int n;
	cin >> n;
	int a, b;
	cin >> a >> b;

	vector<int> niz(n);
	for(int i=0; i<n; i++)
		cin >> niz[i];

	int visina = ceil(log2(n));
	int size = 2*pow(2, visina);

	vector<int> drvo(size);
	izgradi(niz, drvo, 0, n-1, 1);

	cout << prebroj_parne(drvo, 0, n-1, a, b, 1) << endl;


	return 0;
}