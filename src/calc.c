#include <math.h>
#include "calc.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
init const funs[] = 
{
    { "atan", atan },
    { "cos", cos },
    { "sin", sin },
    { "ln", log2 },
    { "log", log10},
    { "sqrt", sqrt },
    { 0, 0}
};

symrec *sym_table;

void init_table(void)
{
    sym_table = NULL;
    for (int i = 0; funs[i].name; i++){
        symrec *ptr = putsym(funs[i].name, eFUN);
        ptr->value.fun = funs[i].fun;
    }
}

symrec *putsym(char const *name, symrec_type sym_type)
{
    symrec *sym = (symrec*) malloc(sizeof(symrec));
    sym->name = strdup(name);
    sym->type = sym_type;
    sym->value.var = 0;
    sym->next = sym_table;
    sym_table = sym;
    return sym;
}

symrec *getsym(char const *name){
    // fprintf(stderr, "tring to find name: %s\n", name );
    for(symrec *sym = sym_table; sym != NULL; sym = sym->next){
        if(strcmp(sym->name, name) == 0){
            // fprintf(stderr, "found name: %f\n", sym->value.var );
            return sym;
        }
    }
    return NULL;
}
