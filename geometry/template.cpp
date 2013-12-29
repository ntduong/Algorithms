/**
    Simple Geometry Library
    (c) Duong Nguyen  ntduong268@gmail.com
    Note: Instead of pair<double, double> as Point ds,
    consider using complex<double> as Point ds if necessary.
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

// constants
const double EPS = 1e-8;
const double INF = 1e12;

// 2D Point (x,y)
typedef pair<double, double> P;
double cross(const P& a, const P& b){
    return a.first*b.second - a.second*b.first;
}

double dot(const P& a, const P& b){
    return a.first*b.first + a.second*b.second;
}

// a-b
P operator-(const P& a, const P& b){
    return P(a.first-b.first, a.second-b.second);
}

P operator+(const P& a, const P& b){
    return P(a.first+b.first, a.second+b.second);
}

double sqnorm(const P& a){
    return a.first*a.first + a.second*a.second;
}

// Line a-b
struct Line{
    P from, to;
    Line(const P& from, const P& to):from(from),to(to){}
};

// Polygon
typedef vector<P> Poly;

// Circle
struct Circle{
    P c; // center point
    double r; // radius
    Circle(const P& c, double r):c(c), r(r){}
};

int ccw(P a, P b, P c){
    b = b-a;
    c = c-a;
    if(cross(b,c) > 0) return +1; // ccw
    if(cross(b,c) < 0) return -1; // cw
    if(dot(b,c) < 0) return +2; // c-a-b
    if(sqnorm(b) < sqnorm(c)) return -2; // a-b-c
    return 0; // a-c-b (c==b case included)
}

// Check if two lines intersect
bool intersectLL(const Line& L1, const Line& L2){
    double t = cross(L1.to - L1.from, L2.to - L2.from);
    double same = cross(L1.to - L1.from , L2.from - L1.from);
    return abs(t) > EPS || abs(same) < EPS;
}

// Check if a line L intersects a segment S
bool intersectLS(const Line& L, const Line& S){
    return cross(L.to-L.from, S.from-L.from) *
            cross(L.to-L.from, S.to-L.from) < EPS;
}

// Check if a point p is on line L
bool point_on_line(const Line& L, const P& p){
    return abs(cross(L.from-p, L.to-p)) < EPS;
}

// Check if two segments S1, S2 intersect
bool intersectSS(const Line& s1, const Line& s2){
    return ccw(s1.from, s1.to, s2.from) * ccw(s1.from, s1.to, s2.to) <= 0 &&
           ccw(s2.from, s2.to, s1.from) * ccw(s2.from, s2.to, s1.to) <= 0;
}

bool point_on_seg(const Line& S, const P& p){
    return sqrt(sqnorm(S.from-p)) + sqrt(sqnorm(S.to-p)) -
            sqrt(sqnorm(S.from-S.to)) < EPS;
}

int main(){

    return 0;
}
