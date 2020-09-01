#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.1415926535
struct tacka
{
	int x, y;
};

int dist_sq(tacka A, tacka B){
	return (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
}

void nadji_uglove(tacka A, tacka B, tacka C){
	//kvadrati stranica
	int a2 = dist_sq(B, C);
	int b2 = dist_sq(A, C);
	int c2 = dist_sq(A, B);

	//stranice
	float a = sqrt(a2);
	float b = sqrt(b2);
	float c = sqrt(c2);

	float alfa = acos((b2 + c2 - a2)/(2*b*c));
	float beta = acos((a2 + c2 - b2)/(2*a*c));
	float gama = acos((a2 + b2 - c2)/(2*a*b));

	//prebacivanje u stepene
	alfa = alfa*180 / PI;
	beta = beta*180 /PI;
	gama = gama*180 / PI;
	cout << alfa << " " << beta << " " << gama << endl;
}

int main(){
	tacka A, B, C;
	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

	nadji_uglove(A, B, C);

	return 0;
}