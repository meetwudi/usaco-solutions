/*
ID: webmast33
PROG: gift1
LANG: C++
*/
#include <fstream>
#include <list>
#include <map>
#include <iostream>

using namespace std;


int N;
map<string, int> result;
list<string> names;

int main() {
  // input N, name and init map
  // note: record name input order for further use
  ifstream fin("gift1.in");
  ofstream fout("gift1.out");
  fin >> N;
  for (unsigned i = 0; i < N; i ++) {
    string name;
    fin >> name;
    result[name] = 0;
    names.push_back(name);
  }

  // for each person's record
  for (unsigned i = 0; i < N; i ++) {
    // input name total money and number of friends
    string name;
    int totmn, totfr;
    fin >> name >> totmn >> totfr;
    //skip non-proceesables
    if (totmn * totfr == 0) {
      string tmpname; 
      for (unsigned j = 0; j < totfr; j ++) fin >> tmpname;
      continue;
    }
    // substract gives from the person
    int gives = totmn - totmn % totfr;
    result[name] = result[name] - gives; 
  
    // add receive for the friends
    int receive = totmn / totfr;
    for (unsigned j = 0; j < totfr; j ++) {
      string namefr;
      fin >> namefr;
      result[namefr] += receive;
    }
  }
  // output in the same order as input line 2
  for (list<string>::iterator it=names.begin();it!=names.end();it++) {
    string name = *it;
    fout << name << " " << result[name] << endl;
  }
  return 0;
}
