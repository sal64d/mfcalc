#include "calc.h"
#include "../build/parser.h"

int main(void){
    init_table();

    yyparse();
    return 0;
}