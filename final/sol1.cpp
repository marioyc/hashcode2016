#include <cstdio>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

#define MAXS 100
#define MAXC 10000

struct point{
  int x,y;

  point(){}
  point(int _x, int _y):
    x(_x), y(_y){}
};

struct satellite{
  point p;
  int v,w,d;
  int dx,dy;

  satellite(){}
}sat[MAXS];

struct collection{
  int value,nl,nr;
  vector<point> l;
  vector< pair<int, int> > r;

  collection(){}
}col[MAXC];

struct photo{
  point p;
  int id_sat,t;

  photo(point _p, int _id_sat, int _t):
    p(_p), id_sat(_id_sat), t(_t){}

  void print(){
    printf("%d %d %d %d\n",p.x,p.y,t,id_sat);
  }
};

void fix_y(int &y){
  if(y < -648000) y += 1296000;
  if(y > 647999) y -= 1296000;
}

point add(point p, int dx, int dy){
  p.x += dx;
  p.y += dy;

  if(p.x > 90 * 3600){
    p.x = 180 * 3600 - p.x;
    p.y = -180 * 3600 + p.y;
  }else if(p.x < -90 * 3600){
    p.x = - 180 * 3600 - p.x;
    p.y = -180 * 3600 + p.y;
  }

  fix_y(p.y);

  assert(p.x <= 90 * 3600);
  assert(p.x >= -90 * 3600);
  assert(p.y >= -648000);
  assert(p.y <= 647999);

  return p;
}

void update_sat(satellite &s){
  s.p.x += s.v;
  s.p.y -= 15;

  if(s.p.x > 90 * 3600){
    s.p.x = 180 * 3600 - s.p.x;
    s.p.y = -180 * 3600 + s.p.y;
    s.v = -s.v;
  }else if(s.p.x < -90 * 3600){
    s.p.x = - 180 * 3600 - s.p.x;
    s.p.y = -180 * 3600 + s.p.y;
    s.v = -s.v;
  }

  fix_y(s.p.y);

  assert(s.p.x <= 90 * 3600);
  assert(s.p.x >= -90 * 3600);
  assert(s.p.y >= -648000);
  assert(s.p.y <= 647999);
}

bool check_turn(collection &c, int turn){
  for(int i = 0;i < c.nr;++i){
    if(turn >= c.r[i].first && turn <= c.r[i].second)
      return true;
  }

  return false;
}

int find_location(collection &c, satellite &s){
  for(int i = 0;i < c.nl;++i){
    if(c.l[i].x == s.p.x && c.l[i].y == s.p.y)
      return i;
  }

  return -1;
}

vector<photo> vphotos;

int main(){
  // Read input
  int T,S,C;

  scanf("%d %d",&T,&S);

  for(int i = 0;i < S;++i){
    scanf("%d %d %d %d %d",&sat[i].p.x,&sat[i].p.y,&sat[i].v,&sat[i].w,&sat[i].d);
  }

  scanf("%d",&C);

  for(int i = 0;i < C;++i){
    scanf("%d %d %d",&col[i].value,&col[i].nl,&col[i].nr);

    for(int j = 0,x,y;j < col[i].nl;++j){
      scanf("%d %d",&x,&y);
      col[i].l.push_back(point(x,y));
    }

    for(int j = 0,s,e;j < col[i].nr;++j){
      scanf("%d %d",&s,&e);
      col[i].r.push_back(make_pair(s,e));
    }
  }

  // Turn-loop

  for(int t = 0;t < T;++t){
    // Choose
    for(int i = 0;i < S;++i){
      bool found = false;

      for(int j = 0;j < C && !found;++j){
        if(check_turn(col[j],t)){
          int ret = find_location(col[j],sat[i]);
          if(ret != -1){
            vphotos.push_back(photo(sat[i].p,i,t));
          }
        }
      }
    }

    // Update for next turn
    for(int i = 0;i < S;++i)
      update_sat(sat[i]);
  }

  printf("%d\n",(int)vphotos.size());

  for(int i = 0;i < vphotos.size();++i)
    vphotos[i].print();

  return 0;
}
