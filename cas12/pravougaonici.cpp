#include <iostream>

using namespace std;

struct tacka
{
	int x, y;	
};

bool preklapaju(tacka l1, tacka r1, tacka l2, tacka r2){
	if(l2.x >= r1.x || l1.x >= r2.x)
		return false;
	if(l2.y <= r1.y || l1.y <= r2.y)
		return false;
	return true;
}

int main(){
	tacka l1, r1, l2, r2;

	cin >> l1.x >> l1.y >> r1.x >> r1.y >> l2.x >> l2.y >> r2.x >> r2.y;

	if(preklapaju(l1, r1, l2, r2))
		cout << "preklapaju se\n";
	else
		cout << "ne preklapaju se\n";
	return 0;
}