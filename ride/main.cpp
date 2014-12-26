/*
ID: webmast33
LANG: C++
PROG: ride
*/

#include <fstream>
#include <string>

using namespace std;

int compute(string a) {
  // init result
  int result = 1;
  // iterate through all chars
  for (unsigned int i = 0; i < a.length(); i ++) {
    // add result up
    char cur = a.at(i);
    int score = cur - 'A' + 1;
    result = ((result % 47) * (score % 47)) % 47;
  }
  // return result
  return result;
}

int main() {
  ifstream fin("ride.in");
  ofstream fout("ride.out");

  string ncomet, ngroup;
  fin >> ncomet >> ngroup;
  
  // compute 
  int score_comet = compute(ncomet);
  int score_group = compute(ngroup);
  

  // compare
  string result;
  result = score_comet == score_group ? "GO" : "STAY";
//  fout << score_comet << endl << score_group << endl;

  // output
  fout << result << endl;

  return 0;
}
