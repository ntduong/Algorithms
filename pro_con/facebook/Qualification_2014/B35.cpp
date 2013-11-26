/**
    Facebook Hacker Cup 2014 - Qualification
    Basketball Game
    (c) Duong Nguyen @moon
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<cassert>

using namespace std;

typedef pair<int,int> ii;

int main(){
    freopen("basketball_game.txt", "r", stdin);
    freopen("bout_sub.txt", "w", stdout);

    int T, N, M, P;
    string name;
    int sh, he;
    cin >> T;
    for(int t = 1; t <= T; ++t){
        cin >> N >> M >> P;
        map<ii, string> pm;
        for(int i = 0; i < N; ++i){
            cin >> name >> sh >> he;
            pm[make_pair(sh,he)] = name;
        }

        vector<string> names; // names[i] := i-th player sorted decreasingly by (shot, height)
        map<ii, string>::reverse_iterator rit;
        for(rit = pm.rbegin(); rit != pm.rend(); rit++){
            names.push_back(rit->second);
        }

        vector<ii> in1, o1, in2, o2; // pair<time, draft-number>
        int cnt1 = 0, cnt2 = 0;
        for(int i = 0; i < N; i += 2){
            cnt1++;
            if(cnt1 > P) o1.push_back(make_pair(0,i));
            else in1.push_back(make_pair(0,i));
        }
        for(int i = 1; i < N; i += 2){
            cnt2++;
            if(cnt2 > P) o2.push_back(make_pair(0,i));
            else in2.push_back(make_pair(0,i));
        }

        assert(static_cast<int>(in1.size()) == P && static_cast<int>(in2.size() == P));

        // simulation
        for(int m = 1; m <= M; ++m){
            if(2*P < N){
                for(int i = 0; i < P; i++){
                    in1[i].first++;
                }
                sort(in1.begin(), in1.end());
                if(!o1.empty()){
                    sort(o1.begin(), o1.end());
                    swap(in1[P-1], o1[0]);
                }
            }

            if(2*P < N){
                for(int i = 0; i < P; i++){
                    in2[i].first++;
                }
                sort(in2.begin(), in2.end());
                if(!o2.empty()){
                    sort(o2.begin(), o2.end());
                    swap(in2[P-1], o2[0]);
                }
            }
        }
        vector<string> ans;
        for(int i = 0; i < P; i++){
            ans.push_back(names[in1[i].second]);
            ans.push_back(names[in2[i].second]);
        }
        sort(ans.begin(), ans.end());
        cout << "Case #" << t << ": ";
        for(int i = 0; i < 2*P-1; i++) cout << ans[i] << " ";
        cout << ans[2*P-1];
        if(t < T) cout << "\n";
    }

    return 0;
}
