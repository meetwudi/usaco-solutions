/*
ID: webmast33
PROG: pprime
LANG: C++11
*/
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
int answer = 0, a, b;

//
//make_pal
//
//middle = -1 if not presented
int make_pal(int num, int middle)
{
  //convert num to string
  string num_s = to_string(num), num_sr = num_s;
  reverse(num_sr.begin(), num_sr.end());
  //if middle, convert middle to string
  string middle_s = "";
  if (middle > -1)
  {
    middle_s = to_string(middle);
  }
  //num+middle?+num.reverse()
  string result = num_s + middle_s + num_sr;
  //return int
  return stoi(result);
}

//
// gen
//
// generate palindorms of given length
//
void gen_pal(int len, void (*callback)(int))
{
  // half_len = floor(len/2)
  int half_len = len / 2;
  bool is_odd = (len % 2) > 0;
  // generate & iterate integer of half_len
  // start from 10^half_len, end at 10^(half_len)-1
  if (half_len == 0)
  {
    // 1 digit
    for (int middle = 1; middle <= 9; middle ++) callback(middle);
    return;
  }
  for (int i = pow(10, half_len - 1); i < pow(10, half_len); i ++)
  {
    // call make_pal
    int pal;
    if (is_odd)
    {
      for (int middle = 0; middle <= 9; middle ++)
      {
        pal = make_pal(i, middle);
        callback(pal);
      }
    }
    else
    {
      pal = make_pal(i, -1);
      callback(pal);
    }
  }
}


ofstream fout("pprime.out");
void judge(int pal)
{
  // if not in [a, b] return
  if (pal < a || pal > b) return;
  // prime test
  int upperbound = (int)sqrt(pal);
  for (int i = 2; i <= upperbound; i ++)
    if (pal % i == 0) return;
  fout << pal << endl;
}

int main()
{
  // input a, b
  ifstream fin("pprime.in");
  fin >> a >> b;
  // for length 1 ~ 9 pal, gen and judge
  for (int len = 1; len <= 9; len ++)
  {
    gen_pal(len, judge);
  }
  return 0;
}
