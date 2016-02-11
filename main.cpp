#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

#define MAXP 10000
#define MAXW 10000
#define MAXC 10000
#define MAXD 1000

int rows,cols,D,turns,load,W,C;
int P,weight[MAXP];

struct warehouse{
	int id;
	int r,c;
	int p[MAXP];
}ware[MAXW];

struct order{
	int id;
	int r,c;
	int p[MAXP];
}ord[MAXC];

struct drone{
	int id;
	int r,c,used;
	int p[MAXP];
}dr[MAXD];

// Euclidian distance Functions 
int dist( warehouse& w1, warehouse& w2){
	return ceil(sqrt( ((w1.r-w2.r) * (w1.r-w2.r) )+ ((w1.c-w2.c) * (w1.c-w2.c) ) )); 
}

int dist( drone& d, warehouse& w){
	return ceil(sqrt( ((d.r-w.r) * (d.r-w.r) )+ ((d.c-w.c) * (d.c-w.c) ) )); 
}

int dist( warehouse& w, drone& d){
	return dist(&d,&w); 
}

int dist( drone& d, order& o){
	return ceil(sqrt( ((d.r-o.r) * (d.r-o.r) )+ ((d.c-o.c) * (d.c-o.c) ) )); 
}

int dist( order& o,drone& d){
	return dist(&d,&o);
}

int main(){
	ios::sync_with_stdio(0);

	cin >> rows >> cols >> D >> turns >> load;

	cin >> P;
	//cout << P << endl;

	for(int i = 0;i < P;++i)
		cin >> weight[i];

	cin >> W;
	//cout << W << endl;

	for(int i = 0;i < W;++i){
		cin >> ware[i].r >> ware[i].c;
		ware[i].id = i;

		for(int j = 0;j < P;++j)
			cin >> ware[i].p[j];
	}

	cin >> C;
	//cout << C << endl;

	for(int i = 0;i < C;++i){
		cin >> ord[i].r >> ord[i].c;
		ord[i].id = i;
		//memset(ord[i].p,0,sizeof ord[i].p);
		int size;
		cin >> size;

		for(int j = 0,aux;j < size;++j){
			cin >> aux;
			++ord[i].p[aux];
		}
	}

	for(int i = 0;i < D;++i){
		dr[i].r = ware[0].r;
		dr[i].c = ware[0].c;
		dr[i].id = i;
		dr[i].used = 0;
		//memset(dr[i].p,0,sizeof dr[i].p);
	}

	return 0;
}
