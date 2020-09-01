#include <iostream>

using namespace std;
struct tacka
{
	int x;
	int y;
};

float povrsina(tacka A, tacka B, tacka C){
	return abs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y))/2.0);

}
void proveri(tacka A, tacka B, tacka C, tacka D, tacka P){
	float pravougaonik = povrsina(A, B, C) + povrsina(A, C, D);
	float PAB = povrsina(P, A, B);
	float PCD = povrsina(P, C, D);
	float PBC = povrsina(P, B, C);
	float PAD = povrsina(P, A, D);

	if(PAB + PBC + PCD + PAD == pravougaonik)
		cout << "Unutar pravougaonika\n";
	else
		cout << "Van pravougaonika\n";
}

int main(){
	tacka A, B, C, D, P;
	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y >> P.x >> P.y;

	proveri(A, B, C, D, P);

	return 0;
}