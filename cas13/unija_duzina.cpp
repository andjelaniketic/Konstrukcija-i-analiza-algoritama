#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct segment
{
	int l, d;
};

bool poredi(const segment &a, const segment &b){
	if(a.l == b.l)
		return a.d > b.d;
	return a.l < b.l;
}

int odredi_uniju(vector<segment> &niz, int n){
	int desni = niz[0].d;
	int suma = niz[0].d - niz[0].l;
	for(int i=1; i<n; i++){
		if(niz[i].d > desni){
			if(niz[i].l >= desni){ //trenutni nije povezan sa prethodnim
				suma += niz[i].d - niz[i].l;	//dodajemo njegovu celu duzinu
				desni = niz[i].d;
			}
			else{	//ili je pocetak od trenutnog == desnom kraju prethodnog, ili se seku
				suma += niz[i].d - desni; //dodajemo razliku duzina
				desni = niz[i].d;
			}
		}
	}
	return suma;
}
int main(){
	int n;
	cin >> n;
	vector<segment> niz(n);

	for(int i=0; i<n; i++)
		cin >> niz[i].l >> niz[i].d;

	sort(niz.begin(), niz.end(), poredi);
	cout << odredi_uniju(niz, n) << endl;
	return 0;
}