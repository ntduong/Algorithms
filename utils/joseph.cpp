
// J(n,k) = (J(n-1, k)+k-1) % n + 1
// J(1, k) = 1

//recursive version
int joseph(int n, int k){
  return n > 1 ? (joseph(n-1, k) + k - 1) % n + 1 : 1;
}

//non-recursive version
int joseph(int n, int k){
  int res = 0;
  for(int i = 1; i <= n; i++){
    res = (res+k) % i;
  }
  return res+1;
}


