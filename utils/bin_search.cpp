#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

int bin_search(int a[], int n, int x){
    int le = 0, ri = n-1;
    int mid = (le+ri)/2;
    while(le <= ri){
        if(a[mid] < x) le = mid+1;
        else if(a[mid] > x) ri = mid-1;
        else return mid;
    }
    return -1;
}

int bin_first_search(int a[], int n, int x){
    int le = 0, ri = n-1;
    int mid = (le+ri)/2;
    while(le+1 != ri){ // le+1 == ri, then x[le] < x, x[ri] >= x and le < ri
        if(a[mid] < x){
            le = mid;
        }
        else ri = mid;

        mid = (le+ri)/2;
    }
    if(ri > n || a[ri] != x) return -1;
    else return ri;
}

int bin_last_search(int a[], int n, int x){
    int le = 0, ri = n-1;
    int mid = (le+ri)/2;
    while(le+1 != ri){ // le+1 == ri, then a[le] <= x, a[ri] > x and le < ri
        if(a[mid] > x) ri = mid;
        else le = mid;
        mid = (le+ri)/2;
    }
    if(ri > n || a[le] != x) return -1;
    else return le;
}

int main(){
    int a[6] = {1,3,3,3,6,10};
    cout << bin_first_search(a, 6, 3) << endl;
    cout << lower_bound(a,a+6,3)-a << endl;
    cout << bin_last_search(a, 6, 3) << endl;
    //cout << upper_bound(a,a+6,3)-a << endl;
    //cout << bin_search(a, 6, 3) << endl;
    cout << "#.of.3 in array: " << upper_bound(a,a+6,3)-lower_bound(a,a+6,3) << endl;
    return 0;
}
