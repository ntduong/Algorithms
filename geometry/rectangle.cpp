/**
    Check if two rectangles overlap and compute its total area
    For simplicity, assume no overflow and rectangles are axis-aligned.
    (c) Duong Nguyen
*/

#include<iostream>
#include<algorithm>
#include<cstdio>

using namespace std;
typedef pair<int,int> ii;

struct Rect{
    int lx, rx, dy, uy;
    // Initialization from lower-left to upper-right corners
    Rect(int lx, int dy, int rx, int uy):lx(lx), dy(dy), rx(rx), uy(uy){};
};

ostream& operator << (ostream& os, const Rect& R){
    os << "Left Lower Corner: (" << R.lx << ", " << R.dy << ")\n";
    os << "Right Upper Corner: (" << R.rx << ", " << R.uy << ")\n";
    return os;
}

bool is_overlap(const Rect& R1, const Rect& R2){
    return !((R1.rx < R2.lx) || (R1.lx > R2.rx) || (R1.dy > R2.uy) || (R1.uy < R2.dy));
}

// Return total area (overlap area counted only once), and overlap area
ii areas(const Rect& R1, const Rect& R2){
    int S1 = abs(R1.rx - R1.lx) * abs(R1.uy - R1.dy);
    int S2 = abs(R2.rx - R2.lx) * abs(R2.uy - R2.dy);
    int St = S1+S2, So = 0;

    if(is_overlap(R1,R2)){
        int dx = min(R1.rx, R2.rx) - max(R1.lx, R2.lx);
        int dy = min(R1.uy, R2.uy) - max(R1.dy, R2.dy);
        So = max(0, dx*dy);
        St -= So;
    }

    return ii(St, So);
}

int main(){
    freopen("rect_in.txt", "r", stdin);
    int lx1, dy1, rx1, uy1, lx2, dy2, rx2, uy2;
    cin >> lx1 >> dy1 >> rx1 >> uy1 >> lx2 >> dy2 >> rx2 >> uy2;
    Rect R1(lx1, dy1, rx1, uy1);
    Rect R2(lx2, dy2, rx2, uy2);
    cout << R1 << endl;
    cout << R2 << endl;
    auto ans = areas(R1, R2);
    cout << "Total Area: " << ans.first << '\n';
    cout << "Overlap Area: " << ans.second << '\n';
    return 0;
}
