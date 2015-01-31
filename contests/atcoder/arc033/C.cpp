/**
    Atcoder regular contest ARC#033 (2015/01/31)
    Test ordered stat DS -> AC
*/

#include<iostream>
#include<cassert>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef
tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> set_t;

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    set_t S;
    int Q;
    cin >> Q;
    for(int i = 1; i <= Q; ++i){
        int t, x;
        cin >> t >> x;
        if(t == 1) S.insert(x);
        else if(t == 2){
            int v = *S.find_by_order(x-1);
            cout << v << "\n";
            S.erase(v);
        } else {
            cerr << "Invalid query!"
        }
    }
    return 0;
}
