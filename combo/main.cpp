/*
ID: webmast33
PROG: combo
LANG: C++
*/
#include <fstream>
#include <cmath>
#include <iostream>

int m[2][3];
int n;
using namespace std;
bool subjudge(int pattr, int i)
{
  return abs(pattr-i)<=2||abs(pattr-(i+n))<=2||abs(pattr-(i-n))<=2;
}

bool judge(const int* pattr,int i, int j, int k)
{
  return subjudge(pattr[0], i) && subjudge(pattr[1], j) && subjudge(pattr[2], k);
}

int main()
{
  // input
  ifstream fin("combo.in");
  ofstream fout("combo.out");
  fin >> n;
  for (int i = 0; i < 2; i ++) 
    for (int j = 0; j < 3; j ++)
      fin >> m[i][j];
  
  // init answer
  int ans = 0;
  // enumerate all sets
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      for (int k = 0; k < n; k ++)
        if (judge(m[0],i,j,k) || judge(m[1],i,j,k)) ans ++;
  //output
  fout << ans << endl;
  return 0;
}
