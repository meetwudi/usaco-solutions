/*
ID: webmast33
PROG: barn1
LANG: C++
*/
#include <fstream>
using namespace std;

int M, S, C, num_used = 0;
bool stall_occ[300] = { false }, stall_blocked[300] = { false };


bool can_remove(int idx)
{
  return !stall_occ[idx] && stall_blocked[idx];
}

int main()
{
  // input
  ifstream fin("barn1.in");
  ofstream fout("barn1.out");
  fin >> M >> S >> C;
  int start_occ = 1000000, end_occ = -1;
  for (int i = 0; i < C; i ++)
  {
    int stall_id;
    fin >> stall_id;
    stall_id --; // stall_id starts from one while the index starts from 0
    stall_occ[stall_id] = true;
    if (start_occ > stall_id) start_occ = stall_id;
    if (end_occ < stall_id)   end_occ = stall_id;
  }
  // cover from the first non-empty stall to the last one
  for (int i = start_occ; i <= end_occ; i ++)
  {
    stall_blocked[i] = true;
  }

  // minus 1 from count of boards available
  num_used ++;

  // for remaining boards
  while (num_used < M)
  {
    // if no empty stall is blocked, break
    bool should_stop = true;
    for (int i = 0; i < S; i ++)
    {
      if (can_remove(i))
      {
        should_stop = false;
        break;
      }
    }
    if (should_stop) break;

    // find longest segment of blocked empty stalls
    // and mark it as unblocked
    int begin = 0, end, ans_begin, ans_end, ans_len = 0;
    while (!can_remove(begin)) begin ++;
    do
    {
      end = begin;
      while (can_remove(end + 1) && end + 1 < S) end ++;
      // try to update answer
      if (end - begin + 1 > ans_len)
      {
        ans_len = end - begin + 1;
        ans_begin = begin;
        ans_end = end;
      }
      begin = end + 1;
      while (!can_remove(begin) && begin < S) begin ++;
    } while (begin < S);

    for (int i = ans_begin; i <= ans_end; i ++)
    {
      stall_blocked[i] = false; 
    }
    // minus 1 from count of boards available
    num_used++;
  } 
  // get number of stalls blocked
  int answer = 0;
  for (int i = 0; i < S; i ++)
    if (stall_blocked[i])
      answer ++;
  // output answer
  fout << answer << endl;
  return 0;
}
