%{
    #include <stdio.h>
    #include <math.h>
    #include "calc.h"

    int yylex (void);
    void yyerror (char const *);
%}

%define api.value.type union
%output "parser.c"
%header "parser.h"

// terminals
%token <double> NUM
%token <symrec*> VAR FUN

// non-terminals
%nterm <double> exp

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
|   exp '\n'    { printf("=> %.10g\n", $1); }
|   error '\n'  { yyerrok; }
;

exp:
    NUM
|   VAR                 { $$ = $1->value.var; }
|   VAR '=' exp         { $$ = $3; $1->value.var = $3; }
|   FUN '(' exp ')'     { $$ = $1->value.fun ($3); }
|   exp '+' exp         { $$ = $1 + $3; }
|   exp '-' exp         { $$ = $1 - $3; }
|   exp '*' exp         { $$ = $1 * $3; }
|   exp '/' exp         { $$ = $1 / $3; }
|   '-' exp %prec NEG   { $$ = -$2; }
|   exp '^' exp         { $$ = pow($1, $3); }
|   '(' exp ')'         { $$ = $2; }
;

%%