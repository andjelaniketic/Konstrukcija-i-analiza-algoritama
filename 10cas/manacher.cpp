#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void manacher(string &s){
	//dodavanje specijalnih karaktera
	string pom = "$";
	int n = s.size();

	for (int i = 0; i < n; i++)
	{
		pom += "#";
		pom += s[i];
	}
	pom += "#@";

	int centar = 1;
	int desni = 1;	//desni kraj trenutnog palindroma
	vector<int> duzine_palindroma(pom.size());
	int mirror;		//pozicija parnjaka trenutnog karaktera
	n = pom.size();

	for (int i = 1; i < n-1; i++)
	{
		mirror = 2*centar - i; //formula za odredjivanje parnjaka
		//u sustini on trazi karakter podjednako udaljen od centra kao trenutni ali sa drugr strane

		//ako smo unutar box-a, uzimamo minimum izmedju desni kraj - trenutna pozicija, i duzine palindorma koji odgovara parnjaku ovog elementa, ovime osiguravamo da je duzina validna
		if(i < desni)
			duzine_palindroma[i] = min(desni-i, duzine_palindroma[mirror]);

		//proveravamo da li mozemo da povecamo duzinu trenutnog palindroma tako sto poredimo elemente levo i desno od trenutnog, trnutni glumi centar palindroma
		while(pom[i + (duzine_palindroma[i] +1)] == 
			  pom[i - (duzine_palindroma[i] +1)])
			duzine_palindroma[i]++;

		//ako smo izasli van granica palindroma, azuriramo centar i desni kraj
		if(i + duzine_palindroma[i] > desni){
			centar = i;
			desni = i + duzine_palindroma[i];
		}
	}

	//ispis
	//vracamo indeks max elementa
	int max_pos = max_element(duzine_palindroma.begin(), duzine_palindroma.end()) - duzine_palindroma.begin();
	int max = duzine_palindroma[max_pos];

	int start = max_pos - max + 1;
	string rez = "";
	int end = start + 2*max;
	//uzimamo svaki 2. karakter zbog taraba
	for (int i = start; i < end; i += 2)
	{
		rez += pom[i];
	}
	cout << rez << endl;
}

int main(){
	string s;
	cin >> s;
	//ispisuje najduzu palindromsku podnisku
	manacher(s);

	return 0;
}