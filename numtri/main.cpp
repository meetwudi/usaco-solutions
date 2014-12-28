/*
ID: webmast33
PROG: numtri
LANG: C++
*/

#include <fstream>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
using namespace std;

int n, ans = INT_MIN, dp[1010] = { 0 }, input[1010] = { 0 };

int main()
{
  ifstream fin("numtri.in");
  ofstream fout("numtri.out");
  fin >> n;
  for (int len = 1; len <= n; len ++)
  {
    // input each line
    for (int i = 1; i <= len; i ++)
      fin >> input[i];
    // update input
    for (int i = 1; i <= len; i ++)
      input[i] = max(dp[i-1]+input[i],dp[i]+input[i]);
    // copy input to dp
    memcpy(dp, input, sizeof(input));
  }
  for (int i = 1; i <= n; i ++)
    ans = max(ans, dp[i]);
  fout << ans << endl;
  return 0;
}
