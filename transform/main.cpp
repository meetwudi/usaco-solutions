/*
ID: webmast33
PROG: transform
LANG: C++11
*/

#include <fstream>
#include <queue>
#include <functional>
#include <set>

using namespace std;

int N;
set<size_t> record;


const int OP_90 = 1,
      OP_180 = 2,
      OP_270 = 3,
      OP_REFLECT = 4,
      OP_COMB = 5,
      OP_NOCHANGE = 6,
      OP_FAIL = 7;

int answer = OP_FAIL;

struct state 
{
  state() : steps(0), last_operation(OP_NOCHANGE) 
  {
    for (int i = 0; i < 11; i ++)
      for (int j = 0; j < 11; j ++)
        matrix[i][j] = 0;
  }
  int steps; // count of steps used
  int last_operation; // last operation
  char matrix[11][11]; // N * N
  // compare equal overload == 
  bool operator==(const state& rhs) {
    for (int i = 0; i < N; i ++)
      for (int j = 0; j < N; j ++)
        if (matrix[i][j] != rhs.matrix[i][j])
          return false;
    return true;
  }
  // hash
  size_t hashval() const {
    string serial_matrix = "";
    for (int i = 0; i < N; i ++)
      for (int j = 0; j < N; j ++)
        serial_matrix += matrix[i][j];
    return hash<string>()(serial_matrix) + hash<int>()(steps);;
  }
  // compare <
  bool operator<(const state& rhs) {
    return hashval() < rhs.hashval(); 
  }
} initial_state, target_state;
typedef state* stateptr;
queue<state> states;




// helper: rotate 90
state rotate90(const state& state)
{
  struct state new_state;
  for (int i = 0; i < N; i ++)
    for (int j = 0; j < N; j ++)
      new_state.matrix[j][N - i - 1] = state.matrix[i][j];
  return new_state;
}

// helper: reflect
state reflect(const state& state)
{
  struct state new_state;
  for (int i = 0; i < N; i ++)
    for (int j = 0; j < N; j ++)
      new_state.matrix[i][N - j - 1] = state.matrix[i][j];
  return new_state;
}

// helper: transform
state transform(const state& state, int transform_type) 
{ 
  struct state new_state = state;
  // rotation
  if (transform_type >= OP_90 && transform_type <= OP_270)
    for (int i = OP_90; i <= transform_type; i ++)
      new_state = rotate90(new_state);

  // reflection
  if (transform_type == OP_REFLECT) {
      new_state = reflect(new_state);
  }
  // update steps & last_operation
  new_state.steps = state.steps + 1;
  new_state.last_operation = transform_type;
  return new_state;
}

void update_answer(int new_answer) {
  if (new_answer < answer) {
    answer = new_answer;
  }
}

int main() 
{
  // input, setup initial & target state
  ifstream fin("transform.in");
  ofstream fout("transform.out");
  fin >> N;
  for (int i = 0; i < N; i ++)
    fin >> initial_state.matrix[i];
  for (int i = 0; i < N; i ++)
    fin >> target_state.matrix[i];

  // push initial state into queue
  initial_state.last_operation = OP_NOCHANGE;
  states.push(initial_state);
  record.insert(initial_state.hashval());

  // this is stupid
  if (initial_state == target_state)
  {
    update_answer(OP_NOCHANGE);
  }

  // BFS
  while (states.size() > 0) {
    // get current state
    state current_state = states.front();
    states.pop();

    // check whether equal to target
    // if true, set success flag to true
    // and quit looping
    if (current_state == target_state && current_state.steps >= 1) {
      if (current_state.steps > 1) {
        update_answer(OP_COMB);
      }
      else {
        update_answer(current_state.last_operation);
      }
      break;
    }

    // derive several child  
    for (int transform_type = 1; transform_type <= 4; transform_type ++) { 
      // transform
      state next_state = transform(current_state, transform_type);
      // check if used
      if (record.find(next_state.hashval()) == record.end()) {
        // if not, enqueue
        record.insert(next_state.hashval());
      }
    }
  }
  // output
  fout << answer << endl;
  return 0;
}


