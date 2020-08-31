#include <iostream>
#include <vector>

using namespace std;

vector<int> izracunaj_z_niz(const string &s){
	int n = s.size();
	int l = 0;
	int d = 0;
	vector<int> niz(n);

	for (int i = 1; i < n; ++i)
	{
		//ako je trenutna pozicija unutar z-boxa, prepisujemo 
		if(i <= d)
			niz[i] = min(d-i+1, niz[i-l]);
		//ako se karakteri poklapaju, povecavamo duzinu podniske
		while(i+niz[i] < n && s[niz[i]] == s[i+niz[i]])
			niz[i]++;

		//izasli smo iz boxa, azuriramo mu krajeve
		if(i+niz[i]-1 > d){
			l = i;
			d = i+niz[i]-1;
		}
	}
	return niz;
}

int main(){
	string s;
	cin >> s;
	int k;
	cin >> k;
	int n = s.size();
	vector<int> Zniz = izracunaj_z_niz(s);

	for (int i = 0; i < n; ++i)
	{
		if(Zniz[i] == k)
			cout << i-k-1 << endl;
	}

	return 0;
}