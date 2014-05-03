/**
    Facebook Hacker Cup 2014 - Qualification
    Square Detector
    (c) Duong Nguyen @moon
*/

#include<cstdio>
#include<iostream>
#include<string>
#include<cassert>

using namespace std;

int main(){
    freopen("square_detector.txt", "r", stdin);
    freopen("aout.txt", "w", stdout);

    int T, N;
    cin >> T;
    string line;
    for(int t = 1; t <= T; t++){
        cin >> N;
        int n_black = 0, top = N, bot = -1, le = N, ri = -1;
        for(int i = 0; i < N; i++){
            cin >> line;
            assert(static_cast<int>(line.length()) == N);
            bool has_black = false;
            for(int j = 0; j < N; j++){
                if(line[j] == '#'){
                    n_black++;
                    has_black = true;
                    le = min(le, j);
                    ri = max(ri, j);
                }
            }
            if(has_black){
                top = min(top, i);
                bot = max(bot, i);
            }
        }

        assert(le <= ri && top <= bot && n_black >= 1); // at least one black cell

        cout << "Case #" << t << ": ";
        if(bot-top+1 != ri-le+1){ // not square
            cout << "NO";
        } else{
            if((bot-top+1)*(ri-le+1) == n_black){
                cout << "YES";
            } else{ // not filled
                cout << "NO";
            }
        }

        if(t < T) cout << "\n";
    }

    return 0;
}
