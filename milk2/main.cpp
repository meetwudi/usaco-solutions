/*
ID: webmast33
PROG: milk2
LANG: C++
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int POINT_TYPE_START = 0,
      POINT_TYPE_END = 1;
struct point {
  int type; 
  int cord;
  bool operator<(const point& rhs) const {
    if (this->cord != rhs.cord) {
      return this->cord < rhs.cord;
    }
    else {
      return this->type < rhs.type;
    }
  }
};

vector<point> points;

int main() {
  ifstream fin("milk2.in");
  ofstream fout("milk2.out");
  // input
  int N;
  fin >> N;
  int cur_type = POINT_TYPE_START;
  for (int i = 0; i < 2 * N; i ++) {
    point cur_point;
    cur_point.type = cur_type;
    cur_type = cur_type ^ 1;
    fin >> cur_point.cord;
    points.push_back(cur_point);
  }
  // sort
  sort(points.begin(), points.end());
  // init answer
  int t_milk = 0, t_idle = 0;
  int t_milk_last_start = -1, t_idle_last_start = -1;
  // compute 
  // setup flag
  int cur_segment = 0;
  // iterate & update flag
  for (vector<point>::iterator it = points.begin(); it != points.end(); it ++) {     
      point now = *it;
      //update flag
      if (now.type == POINT_TYPE_START) {
        cur_segment ++;
      }
      else {
        cur_segment --;
      }
      //when first start point
      if (cur_segment == 1 && now.type == POINT_TYPE_START) {
        // idle stop
        if (t_idle_last_start > -1)
        {
          t_idle = max(t_idle, now.cord - t_idle_last_start);
        }
        // milk start
        t_milk_last_start = now.cord;
      }
      //when last end point
      else if (cur_segment == 0 && now.type == POINT_TYPE_END) {
        // idle start
        t_idle_last_start = now.cord;
        // milk end
        if (t_milk_last_start > -1)
        {
          t_milk = max(t_milk, now.cord - t_milk_last_start);
        }
      }
  }

  // output
  fout << t_milk << " " << t_idle << endl;
  return 0;
}
