/**
    Simple snippet for KMP algorithm.
    @Todo: Test thoroughly
*/

#include<iostream>
#include<string>

// Build failure function for pattern
int *build_fail(const string& p) {
    size_t m = p.length();
    int *fail = new int[m+1];
    int j = fail[0] = -1;
    for(int i = 1; i <= m; i++){
        while(j >= 0 && p[j] != p[i-1]) j = fail[j];
        fail[i] = j++;
    }
    return fail;
}

/**
    Matching pattern against text in O(n+m) time.
    Return the number of matchs
*/
int match(const string& t, const string& p, int *fail){

    size_t n = t.length();
    size_t m = p.length();
    int cnt = 0;

    for(int i = 0, k = 0; i < n; i++){
        while(k >= 0 && p[k] != t[i]) k = fail[k];
        if(++k >= m){
            ++cnt; // found match at t[i-m+1 : i]
            k = fail[k];
        }
    }
    return cnt;
}

int main() {
    return 0;
}
