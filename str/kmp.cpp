//build failure function for pattern
int *build_fail(char *p){
  int m = strlen(p);
  int *fail = new int[m+1];
  int j = fail[0] = -1;
  for(int i = 1; i <= m; i++){
    while(j >= 0 && p[j] != p[i-1])
      j = fail[j];
    fail[i] = j++;
  }
  return fail;
}

int match(char *t, char *p, int *fail){
  int n = strlen(t);
  int m = strlen(p);
  int count = 0;
  for(int i = 0, k = 0; i < n; i++){
    while(k >= 0 && p[k] != t[i])
      k = fail[k];
    if(++k >= m){
      count++; //match at t[i-m+1...i]
      k = fail[k];
    }
  }
  return count;
}


