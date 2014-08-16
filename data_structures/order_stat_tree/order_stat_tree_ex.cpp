/**
    Policy based DS in C++ STL
    Example with order statistic tree
    (Test under GNU C++)
    Ref: http://codeforces.com/blog/entry/11080
*/

#include<iostream>
#include<cassert>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;

//using namespace pb_ds; -> old version
using namespace __gnu_pbds;

typedef
tree<
    int,
    //null_mapped_type, -> old version
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> set_t;

int main(){

    set_t S;
    S.insert(1);
    S.insert(-5);
    S.insert(10);
    S.insert(4);
    S.insert(2);

    //for(const auto& it : S) cout << it << endl;
    /*
        Find_by_order returns the iterator to the k-th element (0-based),
        i.e., S.find_by_order(0) returns the iterator to the smallest number.
    */

    for(int i = 0; i < S.size(); ++i) {
        cout << *S.find_by_order(i) << "\n";
    }
    assert(S.find_by_order(S.size()) == S.end());

    cout << "------------------------------------\n";
    /*
        order_of_key returns # items that are stricly less than our item.
    */

    cout << S.order_of_key(4) << endl;

    return 0;
}
