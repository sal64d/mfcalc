#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "calc.h"
#include "parser.h"

void yyerror (char const *msg){
    fprintf(stderr, "ERROR: %s\n", msg);
}

int yylex (void)
{
    int c = getchar();

    while(c == ' ' || c == '\t')
        c = getchar();

    if(c == EOF)
        return YYEOF;

    if(c == '.' || isdigit(c))
    {
        ungetc(c, stdin);
        if(scanf("%lf", &yylval.NUM) != 1)
            abort();
        
        return NUM;
    }

    if(isalpha(c)){
        static ptrdiff_t bufsize = 0;
        static char *symbuf = 0;

        ptrdiff_t i = 0;

        do{
            if(bufsize <= i)
            {
                bufsize = 2 * bufsize + 40; // ?
                symbuf = realloc (symbuf, (size_t) bufsize);
            }
            symbuf[i++] = (char) c;

            c = getchar();
        } while(isalnum(c));

        ungetc (c, stdin);
        symbuf[i] = '\0';

        symrec *s = getsym(symbuf);

        if(s == NULL){
            s = putsym(symbuf, eVAR);
        }
        yylval.VAR = s;
        
        if(s->type == eVAR){
            return VAR;
        } else {
            return FUN;
        }
    }

    return c;
}