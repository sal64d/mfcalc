#include "calc.h"
#include "parser.h"

int main(void){
    init_table();

    yyparse();
    return 0;
}