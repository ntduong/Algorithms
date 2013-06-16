#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cctype>
#include<string>
#include<cstring>

using namespace std;

#define DELIM 1
#define VAR 2
#define NUM 3
#define INVALID 4

const int EXP_MAX_SIZE = 100;
const int TOKEN_MAX_SIZE = 80;

char *expr;
char token[TOKEN_MAX_SIZE+1];
char tok_type;
int vars[26]; // 26 alphabetical variables (A-Z)

/**************************
*  FUNCTION PROTOTYPES    *
**************************/

void get_expr(int*);
void level1(int*);
void level2(int*);
void level3(int*);
void level4(int*);
void level5(int*);
void level6(int*);
void primitive(int*);
void serror(int);
void get_token();
void arith(char, int*, int*);
void unary(char, int*);
void putback();
int find_var(char*);
bool is_delim(char);
bool is_white_space(char);
bool is_in(char, const char*);
/** END **/

int main(){
    int answer;
    char *p = (char*)calloc(EXP_MAX_SIZE+1, sizeof(char));
    if(!p){
        printf("Allocation failure!\n");
        exit(1);
    }
    while(1){
        expr = p;
        cout << "Enter your expression: ";
        fgets(expr, EXP_MAX_SIZE, stdin);
        int len = (int)strlen(expr);
        if(len >= 1 && expr[len-1] == '\n') expr[len-1] = '\0';
        if(!*expr) break;
        else if(strcmp(expr, "exit") == 0) break;
        get_expr(&answer);
        cout << "Evaluation: " << answer << "\n";
    }
    return 0;
}

/******************************
*  FUNCTION IMPLEMENTATIONS   *
*******************************/

void get_expr(int *result){
    get_token();
    if(!*token){
        serror(2); // no expr
        return;
    }
    level1(result);
}

void level1(int *result){
    int hold, var_ind, ttok_type;
    char temp_token[TOKEN_MAX_SIZE+1];
    if(tok_type == VAR){ // assignment
        strcpy(temp_token, token); // save old token: token -> temp_token
        ttok_type = tok_type; // save old token type
        var_ind = toupper(*token) - 'A'; // index in var table
		get_token();
        if(*token != '='){ // no assigment
            putback();
            strcpy(token, temp_token);
			tok_type = ttok_type;
        }
        else{
            get_token();
            level2(result);
            vars[var_ind] = *result;
            return;
        }
    }
	level2(result);
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

void level4(int *result){
    int hold;
    level5(result);
    if(*token == '^'){
        get_token();
        level4(&hold);
        arith('^', result, &hold);
    }
}

void level5(int *result){
    char op = 0;
    if((tok_type == DELIM) && (*token == '+' || *token == '-')){
        op = *token;
        get_token();
    }
    level6(result);
    if(op) unary(op, result);
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

void serror(int code_num){
    const char *code[] = {
        "syntax error",
        "unbalanced parentheses",
        "no expression available"
    };
    cerr << code[code_num] << "\n";
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
    *temp = '\0'; /* null-terminated */
}

void arith(char op, int *r, int *h){
    if(op == '-') *r = (*r) - (*h);
    else if(op == '+') *r = (*r) + (*h);
    else if(op == '*') *r = (*r) * (*h);
    else if(op == '/') *r = (*r) / (*h);
    else if(op == '%') {
        int t = (*r)/(*h);
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
    for(; *t; t++) expr--;
}

int find_var(char *s){
    if(!isalpha(*s)){
        serror(0);
        return 0;
    }
    return vars[toupper(*token)-'A'];
}

bool is_white_space(char c){
    if(c == ' ' || c == '\t') return true;
    return false;
}

bool is_delim(char c){
    if(is_in(c, " +-/*%^=()") || c == '\t' || c == '\r' || c == 0) return true;
    return false;
}

bool is_in(char c, const char *s){
    while(*s) if (*s++ == c) return true;
    return false;
}
