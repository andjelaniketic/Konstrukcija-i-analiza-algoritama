#include <iostream>

using namespace std;

struct tacka
{
	int x, y;
};

void polozaj(tacka A, tacka B, tacka P){
	int s = (B.y - A.y)*P.x + (A.x - B.x)*P.y + (B.x*A.y - A.x*B.y);
	if(s < 0)
		cout << "Tacka je ispod prave\n";
	else if(s > 0)
		cout << "Tacka je iznad prave\n";
	else
		cout << "Tacka je na pravoj\n";
}
int main(){
	tacka A, B, C;

	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	polozaj(A, B, C);

	return 0;
}
