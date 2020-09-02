#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct segment
{
	int l, d;
};

int poredi(const segment &a, const segment &b){
	if(a.l == b.l)
		return a.d > b.d;
	return a.l < b.l;
}

void nadji_sadrzane(vector<segment> &niz, int n){
	int max = niz[0].d; 
	for(int i=1; i<n; i++){
		if(niz[i].d <= max)
			cout << "[" << niz[i].l << ", " << niz[i].d << "]\n";
		else
			max = niz[i].d;
	}
}
int main(){
	int n;
	cin >> n;
	vector<segment> niz(n);
	for(int i=0; i<n; i++)
		cin >> niz[i].l >> niz[i].d;

	sort(niz.begin(), niz.end(), poredi);
	nadji_sadrzane(niz, n);

	return 0;
}