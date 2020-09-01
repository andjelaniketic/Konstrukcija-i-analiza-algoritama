#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct tacka
{
	int x, y;
};

tacka p0;

int nadji_extrem(vector<tacka> &tacke, int n){
	int max_x = tacke[0].x;
	int min_y = tacke[0].y;
	int index = 0;

	for(int i = 1; i < n; i++){
		if(tacke[i].x > max_x){
			max_x = tacke[i].x;
			min_y = tacke[i].y;
			index = i;
		}
		else if(tacke[i].x == max_x && tacke[i].y < min_y){
			min_y = tacke[i].y;
			index = i;
		}
	}
	return index;
}

void swap(tacka &p1, tacka &p2){
	tacka tmp = p1;
	p1 = p2;
	p2 = tmp;
}

int distance(const tacka &p1, const tacka &p2){
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

int orijentacija(const tacka &p, const tacka &q, const tacka &r){
	int vr;
	vr = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
	if(vr == 0)
		return 0;		//kolinearne
	return (vr > 0)? 1:2; //negativna ili pozitivna
}

bool poredi(const tacka &p1, const tacka &p2){
	int orient = orijentacija(p0, p1, p2);

	if(orient == 2)	//pozitivna orijentacija
		return true;
	else if(orient == 1) //negativna
		return false;
	//kolinearne su, vracamo koja je bliza
	return distance(p0, p1) < distance(p0, p2);
}

void graham(vector<tacka> &tacke, int n){
	int extremna = nadji_extrem(tacke, n);
	swap(tacke[0], tacke[extremna]);
	p0 = tacke[0];

	//sortiramo sve osim prve tacke, prema uglu koji zaklapaju
	sort(tacke.begin() +1, tacke.end(), poredi);
	vector<tacka> rez;
	rez.push_back(tacke[0]);
	rez.push_back(tacke[1]);

	int m = 1;//broj tacaka u omotacu
	for (int i = 2; i < n; i++)
	{
		//ako naidjemo na tacku t.d. ima negativnu orijentaciju sa prethodne 2 tacke, ne ubacujemo je i jos izbacujemo prethodnu tacku
		while(rez.size() >= 2 && orijentacija(rez[m-1], rez[m], tacke[i]) != 2){
			rez.pop_back();
			m--;
		}
		m++;
		rez.push_back(tacke[i]);
	}

	//ispis
	for(tacka &p : rez)
		cout << p.x << " " << p.y << endl;
}

int main(){
	int n;
	cin >> n;
	vector<tacka> tacke(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> tacke[i].x >> tacke[i].y;
	}

	graham(tacke, n);
	return 0;
}