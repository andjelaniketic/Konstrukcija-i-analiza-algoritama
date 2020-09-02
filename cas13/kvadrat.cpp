#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct tacka
{
	int x, y;
};

bool poredi(const tacka &p1, const tacka &p2){
	if(p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.y;
}

void nadji_koordinate(const tacka &A, const tacka &B, tacka &C, tacka &C1, tacka &D, tacka &D1){
	int delta_x = B.x - A.x;
	int delta_y = B.y - A.y;

	C.x = B.x + delta_y; //iznad
	C.y = B.y - delta_x;

	C1.x = B.x - delta_y; //ispod
	C1.y = B.y + delta_x;

	D.x = A.x + delta_y; //iznad
	D.y = A.y - delta_x;

	D1.x = A.x - delta_y; //ispod
	D1.y = A.y + delta_x;
}

bool proveri(vector<tacka> &niz, const tacka &C, const tacka &C1, const tacka &D, const tacka &D1){
	//vracamo ako postoji ili par C, D ili par C1, D1
	return ((binary_search(niz.begin(), niz.end(), C, poredi) &&
			binary_search(niz.begin(), niz.end(), D, poredi)) ||
			(binary_search(niz.begin(), niz.end(), C1, poredi) &&
			binary_search(niz.begin(), niz.end(), D1, poredi)));
}

bool postoji_kvadrat(vector<tacka> &niz, int n){
	sort(niz.begin(), niz.end(), poredi);

	tacka C, C1, D, D1;

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j)
				continue;
			//trazimo koordinate potencijalnih temena
			nadji_koordinate(niz[i], niz[j], C, C1, D, D1);

			//proveravamo da li takve tacke postoje u nasem skupu i vracamo true ako da
			if(proveri(niz, C, C1, D, D1))
				return true;
		}
	}
	return false;
}
int main()
{
	int n;
	cin >> n;
	vector<tacka> niz(n);
	
	for (int i = 0; i < n; i++)
	{
		cin >> niz[i].x >> niz[i].y;
	}

	cout << boolalpha << postoji_kvadrat(niz, n) << endl;
	return 0;
}