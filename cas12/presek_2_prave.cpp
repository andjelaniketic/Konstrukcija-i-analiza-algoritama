#include <iostream>
#include <cfloat>

using namespace std;

struct tacke
{
	double x, y;
};

tacke nadji_presek(tacke A, tacke B, tacke C, tacke D){
	//prava AB
	double a1 = B.y - A.y;
	double b1 = A.x - B.x;
	double c1 = a1*(A.x) + b1*(A.y);
	//prava CD
	double a2 = D.y - C.y;
	double b2 = C.x - D.x;
	double c2 = a2*(C.x) + b2*(C.y);

	double determinanta = a1*b2 - a2*b1;

	if(determinanta == 0){
		tacke presek;
		presek.x = presek.y = FLT_MAX;
		return presek;
	}else{
		tacke presek;
		presek.x = (b2*c1 - b1*c2)/determinanta;
		presek.y = (c2*a1 - c1*a2)/determinanta;
		return presek;
	}
}

int main(){
	tacke A, B, C, D;
	cin >> A.x >> A.y >> B.x >> B.y
		>> C.x >> C.y >> D.x >> D.y;

	tacke presek = nadji_presek(A, B, C, D);

	if(presek.x == FLT_MAX && presek.y == FLT_MAX)
		cout << "Prave su paralelne\n";
	else 
		cout << "(" << presek.x << ", " << presek.y << ")\n";

	return 0;
}