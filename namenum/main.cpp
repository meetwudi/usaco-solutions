/*
ID: webmast33
PROG: namenum
LANG: C++
*/
#include <fstream>
#include <string>
#include <map>

using namespace std;

//setup mapping
map<char, char> mp;


int main() {
  // init mapping
  mp['A'] = mp['B'] = mp['C'] = '2';
  mp['D'] = mp['E'] = mp['F'] = '3';
  mp['G'] = mp['H'] = mp['I'] = '4';
  mp['J'] = mp['K'] = mp['L'] = '5';
  mp['M'] = mp['N'] = mp['O'] = '6';
  mp['P'] = mp['R'] = mp['S'] = '7';
  mp['T'] = mp['U'] = mp['V'] = '8';
  mp['W'] = mp['X'] = mp['Y'] = '9';
  
  // input
  string digits;
  ifstream fin("namenum.in");
  ofstream fout("namenum.out");
  ifstream dictin("dict.txt");
  fin >> digits;

  string dictword;
  bool has_one_valid = false;
  // for each word in dict
  while (dictin >> dictword) 
  {
    if (dictword.size() != digits.size()) continue;
    // check if it is valid
    bool valid = true;
    for (int i = 0; i < dictword.size(); i ++)
      if (mp[dictword[i]] != digits[i])
      {
        valid = false;
        break;
      }
    if (valid) 
    {
      has_one_valid = true;
      fout << dictword << endl;
    }
  }

  // output answer
  if (!has_one_valid)
  {
    fout << "NONE" << endl;
  }
  return 0;
}
