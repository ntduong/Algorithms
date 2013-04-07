#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#define tr(c,it) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)

using namespace std;

vector<string> splitAll(string s, string t){
  vector<string> v;
  for(int p = 0; (p = s.find(t)) != s.npos;){
    v.push_back(s.substr(0, p));
    s = s.substr(p+t.size());
  }
  v.push_back(s);
  return v;
}

vector<string> split(string s, string t){
  vector<string> v;
  int p = s.find(t);
  if(p != s.npos){
    v.push_back(s.substr(0, p));
    s = s.substr(p+t.size());
  }
  v.push_back(s);
  return v;
}

string replaceAll(string s, string f, string t){
  string r;
  for(int p = 0; (p = s.find(f)) != s.npos;){
    r += s.substr(0, p) + t;
    s = s.substr(p+f.size());
  }
  return r+s;
}

string replace(string s, string f, string t){
  string r;
  int p = s.find(f);
  if(p != s.npos){
    r += s.substr(0, p)+t;
    s = s.substr(p + f.size());
  }
  return r+s;
}

int main(){
  
  string s = "duong dep trai";
  vector<string> v = splitAll(s, " ");
  tr(v, it)
    cout << *it << endl;
    
  return 0;
}
