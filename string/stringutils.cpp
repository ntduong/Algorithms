/**
    String utility functions
    To be updated.
*/
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#define tr(c,it) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)

using namespace std;

// Split s by delimiter t
vector<string> splitAll(string s, string t){
    vector<string> v;
    for(int p = 0; (p = s.find(t)) != s.npos;){
        v.push_back(s.substr(0, p));
        s = s.substr(p + t.size());
    }
    v.push_back(s);
    return v;
}

// Split by the first occurence of t in s
vector<string> splitFirst(string s, string t){
    vector<string> v;
    int p = s.find(t);
    if(p != s.npos){
        v.push_back(s.substr(0, p));
        s = s.substr(p + t.size());
    }
    v.push_back(s);
    return v;
}


// Replace all the occurences of f in s with t
string replaceAll(string s, string f, string t){

    string r;
    for(int p = 0; (p = s.find(f)) != s.npos;){
        r += s.substr(0, p) + t;
        s = s.substr(p+f.size());
    }
    return r+s;
}

// Replace the first occurrence of f in s with t
string replaceFirst(string s, string f, string t){

    string r;
    int p = s.find(f);
    if(p != s.npos){
        r += s.substr(0, p)+t;
        s = s.substr(p + f.size());
    }
    return r+s;
}

int main(){

    string s = "have+a+nice+day";
    vector<string> v = splitAll(s, "+");
    for(const auto& t : v) cout << t << endl;
    s = replaceAll(s, "+", "->");
    cout << s << endl;

    return 0;
}
