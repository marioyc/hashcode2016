#include <iostream>
#include <cstring>

using namespace std;

#define MAXP 10000
#define MAXW 10000
#define MAXC 10000
#define MAXD 1000

int rows,cols,D,turns,load,W,C;
int P,weight[MAXP];

struct warehouse{
	int r,c;
	int p[MAXP];
}ware[MAXW];

struct order{
	int r,c;
	int p[MAXP];
}ord[MAXC];

struct drone{
	int r,c;
	int p[MAXP];
}dr[MAXD];

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

		for(int j = 0;j < P;++j)
			cin >> ware[i].p[j];
	}

	cin >> C;
	//cout << C << endl;

	for(int i = 0;i < C;++i){
		cin >> ord[i].r >> ord[i].c;
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
		//memset(dr[i].p,0,sizeof dr[i].p);
	}

	return 0;
}
