/*
ID: webmast33
PROG: palsquare
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
  int base;
  ifstream fin("palsquare.in");
  ofstream fout("palsquare.out");
  fin >> base;
  
  for (int i = 1; i <= 300; i ++)
  {
    string baserep = to_base(i * i, base);
    int k = 10;
    if (validate_pal(baserep))
      fout << to_base(i, base) << " " << to_base(i * i, base) << endl;
  }
  return 0;
}
