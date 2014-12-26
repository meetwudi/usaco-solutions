/*
ID: webmast33
PROG: skidesign
LANG: C++
*/
#include <fstream>
#include <climits>
#include <cmath>

int n, h[1100];
const int InTERVAL = 17; 

using namespace std;
int main()
{
  int ans = INT_MAX;
  // input
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");
  fin >> n;
  for (int i = 0; i < n; i ++) fin >> h[i];

  // enumerate lowerbound
  for (int lb = 0; lb <= 100; lb++)
  {
    // calculate upper bound
    int ub = lb + 17;
    // init cur_ans
    int cur_ans = 0;
    // for each hill calculate cost, add up to cur_ans
    for (int i = 0; i < n; i ++)
    {
      if (lb > h[i]) cur_ans += pow(lb - h[i], 2);
      if (ub < h[i]) cur_ans += pow(ub - h[i], 2);
    }
    // update ans
    ans = ans > cur_ans ? cur_ans : ans;
  }
  // output
  fout << ans << endl;
  return 0;
}
