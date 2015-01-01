#include <fstream>
#include <queue>
#include <utility>
#include <cmath>

using namespace std;

int map[60][60] = { 0 };
int n, m;
struct flood_fill_answer
{
  int nrooms;
  int size_largest_room;
};

#define safe_get(x,y) ((x>=0&&y>=0&&x<n&&y<m)?map[x][y]:-1)
#define valid(x,y) (x>=0&&y>=0&&x<n&&y<m)
#define offset(x) (1<<x)

bool wall_on_west(int x, int y)  { return map[x][y] & offset(0) > 0; }
bool wall_on_north(int x, int y) { return map[x][y] & offset(1) > 0; }
bool wall_on_east(int x, int y)  { return map[x][y] & offset(2) > 0; }
bool wall_on_south(int x, int y) { return map[x][y] & offset(3) > 0; }

int idxoffset[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

bool blocked(int x, int y, int k) 
{
  if (k == 0 && wall_on_east(x,y)) return true;
  if (k == 1 && wall_on_south(x,y)) return true;
  if (k == 2 && wall_on_west(x,y)) return true;
  if (k == 3 && wall_on_north(x,y)) return true;
  return false;
}

flood_fill_answer flood_fill()
{
  // color painting
  int visited[60][60] = { 0 };
  int color = 0;
  int max_color_count = 0;
  for (int x = 0; x < n; x ++)
    for (int y = 0; y < m; y ++)
      if (visited[x][y] == 0)
      {
        queue< pair<int,int> > tmp;
        visited[x][y] = ++color;
        int color_count = 1;
        tmp.push(make_pair(x,y));
        while (!tmp.empty())
        {
          pair<int, int> cur = tmp.front();
          tmp.pop();
          for (int i = 0; i < 4; i ++)
          {
            if (blocked(cur.first,cur.second,i)) continue;
            int next_x = cur.first + idxoffset[i][0];
            int next_y = cur.second+ idxoffset[i][1];
            if (valid(next_x, next_y) && visited[next_x][next_y] == 0)
            {
              color_count ++;
              visited[next_x][next_y] = color;
              tmp.push(make_pair(next_x, next_y));
            }
          }
        }
        // update max_color_count
        max_color_count = max(max_color_count, color_count);
      }
  flood_fill_answer ans;
  ans.nrooms = color;
  ans.size_largest_room = max_color_count; 
  return ans;
}

int main() 
{
  ifstream fin("castle.in");
  ofstream fout("castle.out");
  fin >> m >> n;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      fin >> map[i][j];
  // answer #1
  flood_fill_answer ans1 = flood_fill();
  fout << ans1.nrooms << endl;
  fout << ans1.size_largest_room << endl;
  // answer #2
  return 0;
}
