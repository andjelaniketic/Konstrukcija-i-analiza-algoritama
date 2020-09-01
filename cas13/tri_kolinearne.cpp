#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct tacka
{
	int x, y;
};

tacka p_0;

void swap(tacka &p1, tacka &p2){
	tacka tmp = p1;
	p1 = p2;
	p2 = tmp;
}

int orijentacija(tacka p, tacka q, tacka r){
	int vr = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
	if(vr == 0)
		return 0; //kolinearne
	return (vr > 0)? 1:2; //negativna ili pozitivna orijentacija

}
bool poredi(const tacka &p1, const tacka &p2){
	int orij = orijentacija(p_0, p1, p2);
	if(!orij){
		cout << "postoje 3 kolinearne tacke:\n";
		cout << "(" << p1.x << ", " << p1.y << "), (" << p2.x << ", " << p2.y << "), (" << p_0.x << ", " << p_0.y << ")\n"; 
		exit(EXIT_SUCCESS);
	}
	return orij==2;
}
void tri_kolinearne(std::vector<tacka> tacke, int n){
	for(int i=0; i<n; i++){
		swap(tacke[0], tacke[i]);
		p_0 = tacke[0];
		sort(tacke.begin() +1, tacke.end(), poredi);
	}
}
int main(){
	int n;
	cin >> n;
	std::vector<tacka> tacke(n);
	for(int i=0; i<n; i++)
		cin >> tacke[i].x >> tacke[i].y;

	tri_kolinearne(tacke, n);
	return 0;
}