%{
    #include <stdio.h>
    #include <math.h>
    #include "../src/calc.h"

    int yylex (void);
    void yyerror (char const *);
%}

%define api.value.type union

// terminals
%token <double> NUM
%token <Symbol*> VAR FUN

// non-terminals
%nterm <Expression*> exp

%precedence '='
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'

%%

input:
    %empty
|   input line
;

line:
    '\n'
|   exp '\n'    { printf("=> %.10g\n", evaluate($1)); }
|   error '\n'  { yyerrok; }
;

exp:
    NUM                 { $$ = createNumberExpression($1); }
|   VAR                 { $$ = createVariableExpression($1); }
|   VAR '=' exp         { $$ = createSymbolExpression($1, $3); }
|   FUN '(' exp ')'     { $$ = createSymbolExpression($1, $3); }
|   exp '+' exp         { $$ = createBinaryOperation(eADD, $1, $3); }
|   exp '-' exp         { $$ = createBinaryOperation(eSUB, $1, $3); }
|   exp '*' exp         { $$ = createBinaryOperation(eMUL, $1, $3); }
|   exp '/' exp         { $$ = createBinaryOperation(eDIV, $1, $3); }
|   exp '^' exp         { $$ = createBinaryOperation(ePOW, $1, $3); }
|   '-' exp %prec NEG   { $$ = createUnaryOperation(eNEG, $2); }
|   '(' exp ')'         { $$ = $2; }
;

%%