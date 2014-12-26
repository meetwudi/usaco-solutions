/*
LANG: C++
ID: webmast33
PROG: ariprog
*/
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct answer
{
  int a, d;
  bool operator<(const answer& rhs) const
  {
    if (d == rhs.d) return a < rhs.a;
    else return d < rhs.d;
  }
};
vector<answer> answers;
set<int> bisquares;
int intbis[70000],  intbis_cnt = 0;
bool is_bis[300000] = { 0 };

int main()
{
  int n, m;
  // input
  ifstream fin("ariprog.in");
  ofstream fout("ariprog.out");
  fin >> n >> m;

  // calculate S
  for (int i = 0; i <= m; i ++)
    for (int j = 0; j <= m; j ++)
      bisquares.insert(i*i + j*j);
  for (set<int>::iterator it = bisquares.begin(); it != bisquares.end(); it ++)
  {
    is_bis[*it] = true;
    intbis[intbis_cnt++] = *it;
  }
  // enumerate a1
  for (int a1idx = 0; a1idx < intbis_cnt; a1idx ++)
  {
    int a1 = intbis[a1idx];
    // enumerate a2
    for (int a2idx = a1idx + 1; a2idx < intbis_cnt; a2idx ++)
    {
    // calculate d
      int d = intbis[a2idx] - a1;
      bool success = true;
    // judge if the sequence exists
      for (int i = 1; i <= n - 1; i ++)
      {
        if (!is_bis[a1 + i * d]) 
        {
          success = false;
          break;
        }
      }
      if (success)
      {
      // update answer
        answer ans;
        ans.a = a1;
        ans.d = d;
        answers.push_back(ans);
      }
    }
  }

  // output
  sort(answers.begin(), answers.end());
  for (vector<answer>::iterator it = answers.begin(); it != answers.end(); it ++)
  {
    answer ans = *it;
    fout << ans.a << " " << ans.d << endl;
  }
  if (answers.size() == 0)
  {
    fout << "NONE" << endl;
  }
  return 0;
}
