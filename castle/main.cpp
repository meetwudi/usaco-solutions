/*
ID: webmast33
PROG: castle
LANG: C++
*/
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

const int MAXN = 51, MAXM = MAXN;
const int MAXROOM = MAXN * MAXM;

enum 
{
  Dwest = 1,
  Dnorth = 2,
  Deast = 4,
  Dsouth = 8
};

struct Square
{
  Square() : room(-1) { }
  int wall;
  int room;
} map[MAXN][MAXN];

int n, m;
int nrooms = 0;
int capacity[MAXROOM] = { 0 }, max_capacity = 0;

void flood_fill(int room_number, int x, int y)
{
  if (map[x][y].room >= 0) return;
  map[x][y].room = room_number;
  capacity[room_number] ++;
  max_capacity = max(max_capacity, capacity[room_number]);
  if ((map[x][y].wall & Dwest) == 0) flood_fill(room_number, x, y - 1);
  if ((map[x][y].wall & Dnorth) == 0)flood_fill(room_number, x - 1, y);
  if ((map[x][y].wall & Deast) == 0) flood_fill(room_number, x, y + 1);
  if ((map[x][y].wall & Dsouth) == 0)flood_fill(room_number, x + 1, y);
}

int main()
{
  ifstream fin("castle.in");
  ofstream fout("castle.out");
  fin >> m >> n;
  for (int x = 0; x < n; x ++)
    for (int y = 0; y < m; y ++)
      fin >> map[x][y].wall;
  for (int x = 0; x < n; x ++)
    for (int y = 0; y < m; y ++)
      if (map[x][y].room < 0)
        flood_fill(++nrooms, x, y);
  // number of rooms
  fout << nrooms << endl << max_capacity << endl;;
  
  // removing walls
  int max_new_capacity = 0;
  int max_new_x, max_new_y;
  char max_new_dir;
  for (int y = 0; y < m; y ++)
    for (int x = n - 1; x >= 0; x --)
    {
      if (x > 0 && map[x - 1][y].room != map[x][y].room)
      {
        int new_capacity = capacity[map[x - 1][y].room] + capacity[map[x][y].room];
        if (new_capacity > max_new_capacity)
        {
          max_new_capacity = new_capacity;
          max_new_x = x;
          max_new_y = y;
          max_new_dir = 'N';
        }
      }
      if (y < m - 1 && map[x][y + 1].room != map[x][y].room)
      {
        int new_capacity = capacity[map[x][y + 1].room] + capacity[map[x][y].room];
        if (new_capacity > max_new_capacity)
        {
          max_new_capacity = new_capacity;
          max_new_x = x;
          max_new_y = y;
          max_new_dir = 'E';
        }
      }
    }
  fout << max_new_capacity << endl;
  fout << max_new_x + 1 << " " << max_new_y + 1 << " " << max_new_dir << endl;
  return 0;
}
