#include <iostream>
#include <string>

using namespace std;

long long izracunaj_hes(const string &s){
	int p = 31; 	//prost broj veci od opsega karaktera
	int m = 1e9 + 9;	//mnogo velik prost broj
	long long hash = 0;

	int n = s.size();
	for (int i = n-1; i >= 0; i--)
	{
		hash = (hash * p + (s[i] - 'a' +1)) % m;
	}
	return hash;
}

int main(){
	string s;
	cin >> s;
	cout << izracunaj_hes(s) << endl;
	return 0;
}