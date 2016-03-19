#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

#define MAXLA 324000
#define MINLA -324000
#define MAXLO 647999
#define MINLO 648000
#define MAXS 100
#define MAXT 604800
#define MAXW 200
#define MAXD 10000
#define MAXC 10000
#define MAXR 100
#define MAXL 100

int T,S,C;

struct Satellite{
  int id;
	int phi;
	int lambda;
  int v;
  int w;
  int d;
  //
  // bool operator < (warehouse X)const{
  //   return distance < X.distance;
  // }
}Sats[MAXS];

struct Image{
	int phi;
	int lambda;
	// bool operator < (order X)const{
	// 	return notzero < X.notzero;
	// 	//return sump < X.sump;
	// }
};

struct Range{
	int tstart;
	int tend;
	bool operator < (Range X)const{
		return tstart > X.tstart;
		//return have > X.have;
	}
};

struct Collection{
  int value;
  int L;
  int R;
  Image is[MAXL];
  Range rs[MAXR];
}Cols[MAXC];


double dist(int r1, int c1, int r2, int c2){
  return sqrt((r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2));
}

int main(){
	ios::sync_with_stdio(0);

	cin >> T;
	cin >> S;
	cout << S << endl;

	for(int i = 0;i < S;++i){
		cin >> Sats[i].phi >> Sats[i].lambda >> Sats[i].v >>Sats[i].w >> Sats[i].d;
    Sats[i].id = i ;
  }

	cin >> C;
	cout << C << endl;

	for(int i = 0;i < C;++i){
		cin >> Cols[i].value >> Cols[i].L >> Cols[i].R;

		for(int j = 0;j < Cols[i].L;++j){
      cin >> Cols[i].is[j].phi >> Cols[i].is[j].lambda;
    }
    for(int k = 0;k < Cols[i].R;++k){
      cin >> Cols[i].rs[k].tstart >> Cols[i].rs[k].tend;
    }
	}

  //
  //
	// for(int i = 0;i < C;++i){
	// 	cin >> ord[i].r >> ord[i].c;
	// 	ord[i].id = i;
	// 	//memset(ord[i].p,0,sizeof ord[i].p);
	// 	int size;
	// 	cin >> size;
	// 	ord[i].sump = size;
  //
	// 	for(int j = 0,aux;j < size;++j){
	// 		cin >> aux;
	// 		++ord[i].p[aux];
	// 	}
	// }
  //
	// for(int i = 0;i < D;++i){
	// 	dr[i].r = ware[0].r;
	// 	dr[i].c = ware[0].c;
	// 	dr[i].id = i;
	// 	dr[i].have = turns;
	// 	//memset(dr[i].p,0,sizeof dr[i].p);
	// }
  //
	// for(int i = 0;i < C;++i)
	// 	for(int j = 0;j < P;++j)
	// 		if(ord[i].p[j] > 0)
	// 			++ord[i].notzero;
  //
	// sort(ord,ord + C);
	// //random_shuffle(ord,ord + C);
  //
	// for(int i = 0;i < C;++i){
  //   int client = ord[i].id;
  //   //cout << "client = " << client << endl;
  //   int cur = 0;
  //   bool found = true;
  //
  //   while(ord[i].sump > 0 && found){
	// 		for(int j = 0;j < D;++j)
	// 			dr[j].score = dr[j].have - 2 * (int)ceil(dist(dr[j].r,dr[j].c,ord[i].r,ord[i].c));
  //
  //     sort(dr,dr + D);
  //
  //     // TODO: producto que mas necesitas
  //     while(ord[i].p[cur] == 0) ++cur;
  //
  //     found = false;
  //
  //     /*for(int k = 0;k < W;++k)
  //       ware[k].distance = (int)ceil(dist(ware[k].r,ware[k].c,ord[i].r,ord[i].c));
  //     sort(ware,ware + W);*/
  //
  // 		for(int j = 0;j < D && !found;++j){
  //       // TODO: combinar distancia y lo que transporta
  //       // TODO: ordenar warehouses por distancia
	// 			for(int k = 0;k < W;++k)
	// 				ware[k].distance = (int)ceil(dist(dr[j].r,dr[j].c,ware[k].r,ware[k].c)) + (int)ceil(dist(ware[k].r,ware[k].c,ord[i].r,ord[i].c));
	// 			sort(ware,ware + W);
  //
  // 			for(int k = 0;k < W && !found;++k){
  //         if(ware[k].p[cur] > 0){
  //           int d1 = (int)ceil(dist(dr[j].r,dr[j].c,ware[k].r,ware[k].c));
  //           int d2 = (int)ceil(dist(ware[k].r,ware[k].c,ord[i].r,ord[i].c));
  //
  //           if(d1 + d2 <= dr[j].have){
  //             dr[j].capacity = load;
  //             bool takes = false;
  //
  //             //load
  //             int nitems = 0;
  //             vector<int> v1,v2;
  //
  //             for(int id = cur;id < P && d1 + d2 + 2 * (nitems + 1) <= dr[j].have;++id){
  //               if(ord[i].p[id] > 0 && ware[k].p[id] > 0){
  //                 int take = dr[j].capacity / weight[id];
  //                 take = min(take,min(ord[i].p[id],ware[k].p[id]));
  //
  //                 if(take > 0){
  //                   takes = true;
  //                   dr[j].capacity -= weight[id] * take;
  //                   ord[i].p[id] -= take;
  //                   ware[k].p[id] -= take;
  //                   ord[i].sump -= take;
  //                   ++nitems;
  //                   cout << dr[j].id << " L " << ware[k].id << " " << id << " " << take << '\n';
  //                   v1.push_back(id);
  //                   v2.push_back(take);
	// 									//if(i < 10 && nitems == (notzero + D - 1) / D) break;
  //                 }
  //               }
  //             }
  //
  //             if(takes){
  //               found = true;
  //               dr[j].r = ord[i].r;
  //               dr[j].c = ord[i].c;
  //               found = true;
  //               dr[j].have -= d1 + d2 + 2 * nitems;
  //
  //               // unload
  //
  //               for(int pos = 0;pos < v1.size();++pos){
  //                 cout << dr[j].id << " D " << client << " " << v1[pos] << " " << v2[pos] << '\n';
  //               }
  //             }
  //           }
  //         }
  // 			}
  // 		}
  //   }
  //
  //   //cout << "done " << client << endl;
	// }
  //
	return 0;
}
