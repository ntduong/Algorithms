// Geometry lib using complex 
#include<complex>
using namespace std;
typedef complex<double> point;

// z = a+bi, w = c+di then conjugate(z)*w = (ac+bd) + (ad-bc)i
//the real part is the dot product, and the imaginary part is the cross product
double dot(const point &a, const point &b){
  return real(conj(a) * b);
}
double cross(cosnt point &a, const point &b){
  return imag(conj(a) * b);
}

//reflection of p about a line a1-a2
point reflect(const point &p, const point &a1, const point &a2){
  point z = p-a1;
  point w = a2-a1;
  return conj(z/w)*w+a1;
}

// returns intersection of infinite lines ab, pq (undefined if they are parallel)
point intersect(const point &a, const point &b, const point &p, const point &q){
  double d1 = cross(p-a, b-a);
  double d2 = cross(q-a, b-a);
  return (d1*q-d2*p)/(d1-d2);
}

//rotation
point rotate_by(const point &p, const point &about, double radians){
  return (p-about) * exp(point(0, radians)) + about;
}

//length: we can use abs for length and norm for square length
