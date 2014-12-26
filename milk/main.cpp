/*
ID: webmast33
PROG: milk
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct farmer
{
  int p, a;
  bool operator<(const farmer& rhs) const
  {
    return p < rhs.p;
  }
};
vector<farmer> farmers;

int main()
{
  // input
  ifstream fin("milk.in");
  ofstream fout("milk.out");
  int n, total;
  fin >> total >> n;
  for (int i = 0; i < n; i ++)
  {
    farmer f;
    fin >> f.p >> f.a;
    farmers.push_back(f);
  }
  // sort farmers
  sort(farmers.begin(), farmers.end());
  // iterate through farmers
  // ask for milk :T
  int ans = 0;
  for (vector<farmer>::iterator it = farmers.begin(); it != farmers.end(); it++)
  {
    farmer f = *it;
    int consume = min(total, f.a);
    total -= consume;
    ans += consume * f.p;
  }

  // output
  fout << ans << endl;
  return 0;
}
