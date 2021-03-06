#include <cstdio>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

#define MAXS 40
#define MAXC 2048

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
  bool used;
  int free_turns;

  satellite(){
    dx = dy = 0;
    free_turns = 0;
  }
}sat[MAXS];

struct location{
  point p;
  bool done;

  location(point _p):
    p(_p), done(false){}
};

struct collection{
  int value,nl,nr;
  vector<location> l;
  vector< pair<int, int> > r;
  int cur_r;
  int cont_done;

  collection(){
    cur_r = 0;
    cont_done = 0;
  }

  /*bool operator < (collection X)const{
    return cont_done > X.cont_done;
  }*/
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

struct aux_triple{
  int id_col;
  int id_l;
  int cont_done;

  aux_triple(int _id_col, int _id_l, int _cont_done):
    id_col(_id_col), id_l(_id_l), cont_done(_cont_done){}

  bool operator < (aux_triple X)const{
    return cont_done > X.cont_done;
  }
};

void fix_y(int &y){
  if(y < -648000) y += 1296000;
  if(y > 647999) y -= 1296000;
}

point add(point p, int dx, int dy){
  p.x += dx;
  p.y += dy;

  if(p.x > 324000){
    p.x = 648000 - p.x;
    p.y = -648000 + p.y;
  }else if(p.x < -324000){
    p.x = - 648000 - p.x;
    p.y = -648000 + p.y;
  }

  fix_y(p.y);

  //assert(p.x <= 90 * 3600);
  //assert(p.x >= -90 * 3600);
  //assert(p.y >= -648000);
  //assert(p.y <= 647999);

  return p;
}

void update_sat(satellite &s){
  s.p.x += s.v;
  s.p.y -= 15;

  if(s.p.x > 324000){
    s.p.x = 648000 - s.p.x;
    s.p.y = -648000 + s.p.y;
    s.v = -s.v;
  }else if(s.p.x < -324000){
    s.p.x = - 648000 - s.p.x;
    s.p.y = -648000 + s.p.y;
    s.v = -s.v;
  }

  fix_y(s.p.y);

  if(s.used) s.free_turns = 0;
  else ++s.free_turns;

  //assert(s.p.x <= 90 * 3600);
  //assert(s.p.x >= -90 * 3600);
  //assert(s.p.y >= -648000);
  //assert(s.p.y <= 647999);
}

bool check_turn(collection &c, int turn){
  /*for(int i = 0;i < c.nr;++i){
    if(turn >= c.r[i].first && turn <= c.r[i].second){
      //printf("found\n");
      return true;
    }
  }*/
  if(c.cur_r == c.nr) return false;
  if(turn > c.r[c.cur_r].second) ++c.cur_r;
  if(turn >= c.r[c.cur_r].first && turn <= c.r[c.cur_r].second) return true;
  return false;
}

bool can_reach(satellite &s, point &p, int &dx, int &dy){
  point cur = add(s.p,s.dx,s.dy);

  int lx = s.p.x - s.d;
  int rx = s.p.x + s.d;
  int ly = s.p.y - s.d;
  int ry = s.p.y + s.d;

  bool ok1 = false,ok2 = false;

  if(p.x >= lx && p.x <= rx){
    if(p.y >= ly && p.y <= ry){
      ok1 = true;
    }
    if(p.y - 1296000 >= ly && p.y - 1296000 <= ry){
      ok1 = true;
    }
    if(p.y + 1296000 >= ly && p.y + 1296000 <= ry){
      ok1 = true;
    }
  }

  if(ok1){
    int w;

    if(s.w * s.free_turns >= s.d) w = s.d;
    else w = s.w * s.free_turns;

    lx = cur.x - w;
    rx = cur.x + w;
    ly = cur.y - w;
    ry = cur.y + w;

    if(p.x >= lx && p.x <= rx){
      dx = p.x - cur.x;

      if(p.y >= ly && p.y <= ry){
        dy = p.y - cur.y;
        ok2 = true;
      }
      if(p.y - 1296000 >= ly && p.y - 1296000 <= ry){
        dy = p.y - 1296000 - cur.y;
        ok2 = true;
      }
      if(p.y + 1296000 >= ly && p.y + 1296000 <= ry){
        dy = p.y + 1296000 - cur.y;
        ok2 = true;
      }
    }

    if(ok2){
      //assert(dx >= -w);
      //assert(dx <= w);
      //assert(dy >= -w);

      /*if(dy > s.w){
        printf("s.p = (%d, %d); (dx, dy) = (%d, %d); cur = (%d, %d); p = (%d, %d); s.d = %d; s.w = %d; (dx, dy) = (%d, %d)\n",s.p.x,s.p.y,s.dx,s.dy,cur.x,cur.y,p.x,p.y,s.d,s.w,dx,dy);
      }*/

      //assert(dy <= w);

      s.dx += dx;
      s.dy += dy;

      //assert(s.dx >= -s.d);
      //assert(s.dx <= s.d);
      //assert(s.dy >= -s.d);
      //assert(s.dy <= s.d);

      return true;
    }
  }

  return false;
}

int find_location(collection &c, satellite &s){
  for(int i = 0,dx,dy;i < c.nl;++i){
    //if(c.l[i].x == s.p.x && c.l[i].y == s.p.y)
    if(!c.l[i].done && can_reach(s,c.l[i].p,dx,dy)){
      // update dx,dy
      c.l[i].done = true;
      c.cont_done++;
      return i;
    }
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
      col[i].l.push_back(location(point(x,y)));
    }

    for(int j = 0,s,e;j < col[i].nr;++j){
      scanf("%d %d",&s,&e);
      col[i].r.push_back(make_pair(s,e));
    }
  }

  // Turn-loop
  //bool used_sat[MAXS];
  vector<aux_triple> ok[MAXS];

  for(int t = 0;t < T;++t){
    // Choose
    //memset(used_sat,false,sizeof used_sat);
    for(int i = 0;i < S;++i){
      sat[i].used = false;
      ok[i].clear();
    }

    //sort(col,col + C);

    for(int j = 0;j < C;++j){
      if(check_turn(col[j],t)){
        for(int i = 0;i < S;++i){
          if(!sat[i].used){
            int ret = find_location(col[j],sat[i]);
            if(ret != -1){
              ok[i].push_back(aux_triple(j,ret,col[j].cont_done));
              //sat[i].used = true;
              //vphotos.push_back(photo(col[j].l[ret].p,i,t));
            }
          }
        }
      }
    }

    for(int i = 0;i < S;++i){
      sort(ok[i].begin(),ok[i].end());
      if(!ok[i].empty()){
        sat[i].used = true;
        vphotos.push_back(photo(col[ ok[i][0].id_col ].l[ ok[i][0].id_l ].p,i,t));
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
