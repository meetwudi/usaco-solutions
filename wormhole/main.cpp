/*
ID: webmast33
PROG: wormhole
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;
int N;
struct point {
  point() : pairp(NULL) {}
  int x;
  int y;
  point *pairp;
  bool operator== (const point& rhs)
  {
    return x == rhs.x && y == rhs.y;
  }
} points[20];

void get_next_point(const point& point, struct point*& next)
{
  for (int i = 0; i < N; i ++)
  {
    if (points[i] == point || points[i].y != point.y) continue;
    if (!next && points[i].x > point.x)
      next = &points[i];
    if (next && points[i].x > point.x && points[i].x < next->x)
      next = &points[i];
  }
}
bool valid_answer()
{
  for (int i = 0; i < N; i ++)
  {
    // find point next to it
    point* nextp = NULL, *curp = NULL;
    get_next_point(points[i], nextp);
    // if no next point, sorry, false :(
    curp = &points[i];
    if (!nextp) continue;
    do
    {
      curp = nextp->pairp;
      nextp = NULL;
      get_next_point(*curp, nextp); 
      if (!nextp) break;
    } while (curp != &points[i]);
    if (curp == &points[i]) return true;
  }
  return false;
}

void pair_points(point& x, point& y)
{
  x.pairp = &y;
  y.pairp = &x;
}

void unpair_points(point& x, point& y)
{
  x.pairp = NULL;
  y.pairp = NULL;
}

void dfs(int& ans)
{
  // check whether all points were paired 
  bool all_paired = true;
  for (int i = 0; i < N; i ++)
    if (points[i].pairp == NULL)
      all_paired = false;

  // if all points are paired
  // check if it is valid
  // update answer and terminate dfs
  if (all_paired && valid_answer())
  {
    ans++;
    return;
  }

  // get first unpaired point _up1_
  int up1 = 0;
  while (points[up1].pairp != NULL) up1 ++;

  // for each unpaired point _up2_ other than the first one
  int up2 = up1 + 1;
  do
  {
    // find _up2_
    while (points[up2].pairp != NULL) up2 ++;
    if (up2 >= N) break;
    // pair _up1_ and _up2_
    pair_points(points[up1], points[up2]);
    // dfs
    dfs(ans);
    // unpair _up1_ and _up2_
    unpair_points(points[up1], points[up2]);    
    // update up2
    up2 ++;
  } while (up2 < N);
}

int main()
{
  // input
  ifstream fin("wormhole.in");
  ofstream fout("wormhole.out");
  fin >> N;
  for (int i = 0; i < N; i ++)
    fin >> points[i].x >> points[i].y;

  // dfs entry
  int ans = 0;
  dfs(ans);

  // output
  fout << ans << endl;
  return 0;
}

