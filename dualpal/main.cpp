/*
ID: webmast33
PROG: dualpal
LANG: C++
*/

#include <fstream>
#include <string>

using namespace std;

// get char digit
char chr_digit(int number)
{
  if (0 <= number && number <= 9) return (char)('0' + number);
  return (char)('A' + number - 10);
}

// make digit str in base b
string to_base(int base10rep, int base)
{
  string result = "";
  while (base10rep > 0)
  {
    result = chr_digit(base10rep % base) + result;
    base10rep /= base;
  }
  return result;
}

// judge if it is pal
bool validate_pal(string digits)
{
  int i = 0, j = digits.size() - 1;
  while (i <= j)
    if (digits[i++] != digits[j--]) return false;
  return true;
}

int main()
{
  int N, S;
  ifstream fin("dualpal.in");
  ofstream fout("dualpal.out");
  fin >> N >> S;
  
  int cnt_found = 0;
  for (int now = S + 1; cnt_found < N; now ++)
  {
    int now_pal_rep = 0;
    for (int base = 2; base <= 10 && now_pal_rep < 2; base ++)
    {
      string baserep = to_base(now, base);
      bool ispal = validate_pal(baserep);
      if (ispal)
      {
        now_pal_rep ++;
      }
    }
    if (now_pal_rep >= 2)
    {
      fout << now << endl;
      cnt_found ++;
    }
  }
  return 0;
}
