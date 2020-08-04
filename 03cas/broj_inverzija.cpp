#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int prebroj_inverzije(vector<int> &drvo, int k, int x, int y, int a, int b){
	if(x>b || y<a)
		return 0;
	
	if(x<=a && y<=b)
		return drvo[k];
	
	int s = (x+y)/2;
	
	return prebroj_inverzije(drvo, 2*k, x, s, a, b) + prebroj_inverzije(drvo, 2*k+1, s+1, y, a, b);
	
}

void dodaj_el_u_drvo(vector<int> &drvo, int k, int x, int y, int index){
	if(x == y){
		drvo[k] = 1;
		return;
	}
	
	int s = (x+y)/2;
	
	if(index <= s)
		dodaj_el_u_drvo(drvo, 2*k, x, s, index);
	else
		dodaj_el_u_drvo(drvo, 2*k+1, s+1, y, index);
	
	drvo[k] = drvo[2*k] + drvo[2*k+1];
}

int main(){
	vector<int> niz = {8, 4, 2, 1};
	int n = niz.size();
	
	int max_el = *max_element(niz.begin(), niz.end());
	
	int visina = ceil(log2(max_el));
	int size = 2 * pow(2, visina);
	
	vector<int> drvo(size);
	
	//popunjava celu kolekciju odgovarajucim elementom
	fill(drvo.begin(), drvo.end(), 0);
	//smatramo kao da se ni jedan broj nije pojavio
	
	int rez = 0;
	
	for(int i=0; i<n; i++){
		rez += prebroj_inverzije(drvo, 1, 1, max_el, niz[i]+1, max_el);
		
		dodaj_el_u_drvo(drvo, 1, 1, max_el, niz[i]);
	}
	
	cout << rez << "\n";
	
	return 0;
}
