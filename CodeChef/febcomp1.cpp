#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;


const int MAXS = 100001, MAXSTATE = 2;
const int UNCHANGED = 0, 
    CHANGED = 1;
int opt[MAXS][MAXSTATE] = { 0 };

void reset()
{
    memset(opt, 0, sizeof(opt));  
}

void solve()
{
    reset();
    string str;
    // input str
    cin >> str;
    int len = str.length();
    // init opt for str[0] (opt[0][changed] = opt[0][unchanged] = 0)
    opt[0][UNCHANGED] = 0;
    opt[0][CHANGED] = 1;
    // for str[i = 1 ..]
    for (int i = 1; i < len; i ++)
    {
        // if str[i] == str[i - 1]
        if (str[i] == str[i - 1])
        {
            // opt[i][changed] = opt[i-1][unchanged] + 1
            opt[i][CHANGED] = opt[i-1][UNCHANGED] + 1;
            // opt[i][unchanged] = opt[i-1][changed]
            opt[i][UNCHANGED] = opt[i-1][CHANGED];
        }   
        // else
        else
        {
            // opt[i][changed] = opt[i-1][changed] + 1
            opt[i][CHANGED] = opt[i-1][CHANGED] + 1;   
            // opt[i][unchanged] = opt[i-1][unchanged]
            opt[i][UNCHANGED] = opt[i-1][UNCHANGED];
        }
    }
    // answer = min(opt[len], unchanged/changed)
    int answer = min(opt[len-1][UNCHANGED], opt[len-1][CHANGED]);
    // output answer
    cout << answer << endl;
}

int main() {
    // input
    int T;
    cin >> T;
    // for each case, solve
    while (T--) solve();
	return 0;
}
