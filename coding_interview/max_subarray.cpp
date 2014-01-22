/**
    Given an array of integers A[0...n-1], find its maximum subarray.
    Three solutions are provided below with different complexities.
    Written by Duong Nguyen
*/

#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;

const int MAXN = 100;
typedef tuple<int,int,int> iii;

int s[MAXN+1]; // s[i] := sum of a[0...i-1] i.e., [0,i)
void precompute(const vector<int>& a){
    int n = static_cast<int>(a.size());
    s[0] = 0;
    for(int i = 1; i <= n; i++){
        s[i] = s[i-1] + a[i-1];
    }
}

/**
    Return a triple (i,j,s) s.t the maximum subarray is A[i...j-1] ( [i,j) )
    s = A[i] + ... + A[j-1] is the maximum sum.
    O(n^2) time and O(n) space
*/
iii solve1(const vector<int>& a){
    precompute(a);
    int n = static_cast<int>(a.size());
    int max_sum = 0, le = 0, ri = 0, tmp;

    for(int i = 0; i < n; i++){
        for(int j = i; j <= n; j++){
            tmp = s[j] - s[i]; // tmp = A[i...j-1]
            if(tmp > max_sum){
                max_sum = tmp;
                le = i, ri = j;
            }
        }
    }
    return make_tuple(le, ri, max_sum);
}

/**
    O(n) time and O(1) space DP solution.
*/
iii solve3(const vector<int>& a){
    int n = static_cast<int>(a.size());
    pair<int,int> range(0,0);
    int min_id = -1, min_sum = 0, sum = 0, max_sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
        if(min_sum > sum){
            min_sum = sum;
            min_id = i;
        }
        if(max_sum < sum - min_sum){
            max_sum = sum - min_sum;
            range = {min_id+1, i+1};
        }
    }

    return make_tuple(range.first, range.second,  max_sum);
}

/**
    O(nlogn) time divide and conquer solution
*/
iii solve2(const vector<int>& a, int le, int ri){
    if(ri-le+1 == 1){
        if(a[le] < 0) return make_tuple(le,le,0);
        else return make_tuple(le,le+1,a[le]);
    }

    iii le_t = solve2(a, le, (ri+le)/2);
    iii ri_t = solve2(a, (ri+le)/2+1, ri);
    int mid = (le+ri)/2;
    int sum1 = 0, tmp = 0;
    int id1 = mid;
    for(int i = mid; i >= le; i--){
        tmp += a[i];
        if(sum1 < tmp){
            sum1 = tmp;
            id1 = i;
        }
    }

    tmp = 0;
    int sum2 = 0, id2 = mid+1;
    for(int i = mid+1; i <= ri; i++){
        tmp += a[i];
        if(sum2 < tmp){
            sum2 = tmp;
            id2 = i;
        }
    }

    id2++;

    int ans_le, ans_ri, ans_sum;
    if(get<2>(le_t) > get<2>(ri_t)){
        ans_le = get<0>(le_t);
        ans_ri = get<1>(le_t);
        ans_sum = get<2>(le_t);
    }else{
        ans_le = get<0>(ri_t);
        ans_ri = get<1>(ri_t);
        ans_sum = get<2>(ri_t);
    }

    if(ans_sum < sum1 + sum2){
        ans_sum = sum1 + sum2;
        ans_le = id1;
        ans_ri = id2;
    }

    return make_tuple(ans_le, ans_ri, ans_sum);
}


int main(){
    vector<int> a = {-1,-4,5,2};
    iii ans = solve3(a);
    cout << get<0>(ans) << "-" << get<1>(ans)-1 << ": " << get<2>(ans) << endl;
    return 0;
}
