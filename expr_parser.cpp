#include<cstdio>
#include<iostream>
#include<cctype>
#include<cstdlib>

using namespace std;

#define DELIM 1
#define VAR 2
#define NUM 3
#define INVALID 4

char *expr;
char token[80];
char tok_type;
int vars[26]; /* 26 alphabetical variable A-Z */

bool is_white_space(char c){
    if(c == ' ' || c == '\t') return true;
    return false;
}

bool is_in(char c, const char *s){
    while(*s) if (*s++ == c) return true;
    return false;
}

bool is_delim(char c){
    if(is_in(c, " +-/*%^=()") || c == '\t' || c == '\r' || c == 0)
        return true;
    return false;
}

void get_token(){
    char *temp;
    tok_type = 0;

    temp = token;
    while(is_white_space(*expr)) expr++; /* skip over white space */
    if(is_in(*expr, "+-*/%^=()")){
        tok_type = DELIM;
        *temp++ = *expr++;
    }
    else if(isalpha(*expr)){
        while(!is_delim(*expr)) *temp++ = *expr++;
        tok_type = VAR;
    }
    else if(isdigit(*expr)){
        while(!is_delim(*expr)) *temp++ = *expr++;
        tok_type = NUM;
    }
    else{
        while(!is_delim(*expr)) *temp++ = *expr++;
        tok_type = INVALID;
    }
    *temp = 0; /* null-terminated */
}

void primitive(int *result){
    if(tok_type == NUM){
        *result = atoi(token);
        return get_token();
    }
    else if(tok_type == VAR){
        *result = find_var(token);
        return get_token();
    }
    serror(0); /* otherwise syntax error in expr */
}

void arith(char op, int *r, int *h){
    if(op == '-') *r = (*r) - (*h);
    else if(op == '+') *r = (*r) + (*h);
    else if(op == 'x') *r = (*r) * (*h);
    else if(op == '/') *r = (*r) / (*h);
    else if(op == '%') {
        t = (*r)/(*h);
        *r = (*r) - (t * (*h));
    }
    else if(op == '^'){
        int base = *r;
        if(*h == 0){
            *r = 1;
            return;
        }
        for(int t = *h-1; t > 0; t--) *r = (*r) * base; /* overflow bug? */
    }
}

void unary(char op, int *r){
    if(op == '-') *r = -(*r);
}

void putback(){
    char *t;
    t = token;
    for(; *t; t++)expr--;
}

void serror(int code_num){
    static char *code[] = {
        "syntax error",
        "unbalanced parentheses",
        "no expression available"
    };
    printf("%s", code[code_num]);
}

void find_var(char *s){
    if(!isalpha(*s)){
        serror(1);
        return 0;
    }
    return vars[toupper(*token)-'A'];
}


void level6(int *result){
    if((*token == '(') && (tok_type == DELIM)){
        get_token();
        level2(result); /* recursively evaluate expr inside parentheses */
        if(*token != ')') serror(1); /* unbalanced parentheses */
        get_token();
    }
    else{
        primitive(result);
    }
}


void level5(int *result){
    char op = 0;
    if((tok_type == DELIM) && *token == '+' || *token == '-'){
        op = *token;
        get_token();
    }
    level6(result);
    if(op) unary(op, result);
}

void level4(int *result){
    int hold;
    level5(result);
    if(*token == '^'){
        get_token();
        level4(&hold);
        arith('^', result, &hold);
    }
}

void level3(int *result){
    char op;
    int hold;
    level4(result);
    while((op = *token) == '*' || op == '/' || op == '%'){
        get_token();
        level4(&hold);
        arith(op, result, &hold);
    }
}

void level2(int *result){
    char op;
    int hold;
    level3(result);
    while((op = *token) == '+' || op == '-'){
        get_token();
        level3(&hold);
        arith(op, result, &hold);
    }
}

void level1(int *result){
    int hold;
    int slot, ttok_type;
    char temp_token[80];

    if(tok_type == VAR){ /* assignment */
        strcpy(temp_token, token); /* save old token */
        ttok_type = tok_type;
        slot = toupper(*token) - 'A';
        get_token();
        if(*token != '='){
            putback();
            strcpy(token, temp_token);
        }
        else{
            get_token();
            level2(result);
            vars[slot] = *result;
            return;
        }
    }
    level2(result);
}

void get_expr(int *result){
    get_token();
    if(!*token){
        serror(2);
        return;
    }
    level1(result);
    return result;
}


int main(){
    int answer;
    char *p;
    p = malloc(100);
    if(!p){
        printf("Allocation failure!\n");
        exit();
    }
    while(1){
        expr = p;
        printf("Enter expression: ");
        fgets(expr, 100, stdin);
        int len = strlen(expr);
        if(len >= 1) expr[len-1] = '\0';
        if(!*expr) break;
        get_expr(&answer);
        printf("Evaluated result: %d\n", answer);
    }

    return 0;
}
