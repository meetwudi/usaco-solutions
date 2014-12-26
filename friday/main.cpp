/*
ID: webmast33
PROG: friday
LANG: C++
*/

#include <fstream>

using namespace std;

// Model: Move the niddle by month. Brute force.

bool is_leap(int year) {
  bool ans;
  // is century year?
  if (year % 100 == 0) {    
    // yes
      // divided by 400?
      if (year % 400 == 0) {
        ans = true;
      }
      else {
        ans = false;
      }
  }
  else {
    // no
      // divided by 4?
    if (year % 4 == 0) {
      ans = true;
    }
    else {
      ans = false;
    }
  }
  // return answer
  return ans;
}

typedef int cday; 
const int MONDAY = 0,
      TUESDAY = 1,
      WEDNESDAY = 2,
      THURSDAY = 3,
      FRIDAY = 4,
      SATURDAY = 5,
      SUNDAY = 6,
      COUNT_OF_DAYS = 7;

cday next_day(cday day) {
  return (day + 1) % COUNT_OF_DAYS;
}

cday day_after(cday day, int after_days) {
  return (day + after_days) % COUNT_OF_DAYS;
};

int main() {
  // input
  int N;
  ifstream fin("friday.in");
  ofstream fout("friday.out");
  fin >> N;
  // init answer 
  int answer[COUNT_OF_DAYS] = { 0 };
  // track the first day of the month
  cday fdmonth = MONDAY; 
  // for every year compute
  for (unsigned year = 1900; year < 1900 + N; year ++) {
    // check if it is leap year *
    bool is_leap_year = is_leap(year);
    // for every month compute
    for (unsigned month = 1; month <= 12; month ++) {
      // get day of the first day (known)
  
      // calculate day of the 13th
      cday day_of_13th = day_after(fdmonth, 12);
      answer[day_of_13th] ++;

      // get count of days in the month
      int tot_days;
      if (month == 2) {
        tot_days = is_leap_year ? 29 : 28;
      }
      else if (month == 4 || month == 6 || month == 9 || month == 11) {
        tot_days = 30;
      }
      else {
        tot_days = 31;
      }

      // calculate day of the last day of month
      // - cday day_of_ldom = day_after(fdmonth, tot_days - 1);
      // update day of first day in next month
      fdmonth = day_after(fdmonth, tot_days);
    }
  }
  // print answer
  fout << answer[SATURDAY] << " " << answer[SUNDAY];
  for (int i = MONDAY; i <= FRIDAY; i ++) {
    fout << " " << answer[i];
  }
  fout << endl;
  return 0;
}
