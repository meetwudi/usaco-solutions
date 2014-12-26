/*
ID: webmast33
PROG: beads
LANG: C++
*/
#include <fstream>

using namespace std;

int main() {
  ifstream fin("beads.in");
  ofstream fout("beads.out");
  // input
  int N;
  string beads;
  fin >> N >> beads; 
  // init answer
  int ans = 0;
  // tripple length
  beads = beads + beads + beads; 
  // enumerate, find break point
  for (int start = N; start < 2 * N; start ++) {
    // cut before start
    // calculate answer
    if (beads[start] == beads[start - 1]) continue;
    int forward = start - 1, forwardchr = beads[forward];
    while (beads[forward - 1] == forwardchr || beads[forward - 1] == 'w' ||
        forwardchr == 'w') { 
      forward --;
      if (forwardchr == 'w') {
        forwardchr = beads[forward];
      }
    }
    int backward = start, backwardchr = beads[backward];
    while (beads[backward + 1] == backwardchr || beads[backward + 1] == 'w'
        || backwardchr == '#') {
      backward ++;
      if (backwardchr == '#') {
        backwardchr = beads[backward];
      }
    }
    ans = max(ans, backward - forward + 1);
  }
  ans = ans == 0 || ans > N ? N : ans;
  // output
  fout << ans << endl;
  return 0;
}
