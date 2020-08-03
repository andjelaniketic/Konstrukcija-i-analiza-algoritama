#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void izgradi_stablo(vector<int> &niz, vector<int> &drvo, int k, int x, int y){
	if(x == y){
		drvo[k] = niz[x];
		return;
	}
	
	int s = (x+y)/2;
	izgradi_stablo(niz, drvo, 2*k, x, s);
	izgradi_stablo(niz, drvo, 2*k+1, s+1, y);
	
	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

//menja element na poziciji index i postavlja mu vrednost na nova_vr
void azuriraj_drvo(vector<int> &drvo, int k, int x, int y, int index, int nova_vr){
	//ako smo stigli do lista, to je trazeni element
	if(x == y){
		drvo[k] = nova_vr;
		return;
	}
	
	int s = (x+y)/2;
	
	if(index <= s){
		azuriraj_drvo(drvo, 2*k, x, s, index, nova_vr);
	}else{
		azuriraj_drvo(drvo, 2*k+1, s+1, y, index, nova_vr);
	}
	
	//azuriranje ostalih roditelja
	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int main(){
	vector<int> niz = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int n = niz.size();
	
	int visina = ceil(log2(n));
	int size = 2* pow(2, visina);
	
	vector<int> drvo(size);
	izgradi_stablo(niz, drvo, 1, 0, n-1);
	
	for(int x : drvo)
		cout << x << " ";
	cout << "\n";
	
	azuriraj_drvo(drvo, 1, 0, n-1, 2, 8);
	for(int x : drvo)
		cout << x << " ";
	cout << "\n";
	
	return 0;
}
