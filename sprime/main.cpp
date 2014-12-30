/*
LANG: C++11
PROG: sprime
ID: webmast33
*/

#include <fstream>
#include <queue>
#include <set>
#include <cmath>
#include <iostream>

using namespace std;

set<int> answers;
queue<int> q;
int n;

/*
 * length of decimal integer
 */
int nlen(int num)
{
  return floor(log10(num)) + 1;
}

bool is_prime(int num)
{
  int upperbound = (int)sqrt(num)+1;
  for (int i = 2; i < upperbound; i ++)
    if (num % i == 0)
      return false;
  return true;
}

/*
 * add one digit to num
 */
void expand(int num)
{
  // for i = 0 to 9
  for (int i = 0; i <= 9; i ++)
  {
    // add i to the right of num, as new_num
    int new_num = num*10+i;      
    // is prime?
    if (is_prime(new_num))
    {
      // add new_num to q
      q.push(new_num);
    }
  }
}

int main()
{
  // input
  ifstream fin("sprime.in");
  ofstream fout("sprime.out");
  fin >> n;

  // init q with 2, 3, 5, 7
  q.push(2);
  q.push(3);
  q.push(5);
  q.push(7);

  // while q is not empty
  while (!q.empty())
  {
    // cur = q.first, q.pop
    int cur = q.front();
    q.pop();
    // if length of cur is n
    if (nlen(cur) == n)
    {
      // add cur to answer
      answers.insert(cur);
    }
    // else
    else
    {
      // expand cur
      expand(cur);
    }
  }

  // output
  for (set<int>::iterator it = answers.begin(); it != answers.end(); it ++)
  {
    fout << *it << endl;
  }
  return 0;
}
