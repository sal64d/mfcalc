#ifndef CALC_H
#define CALC_H

typedef double (func_t) (double);

typedef enum symrec_type {
    eFUN,
    eVAR,
} symrec_type;

typedef struct symrec
{
    char *name;
    symrec_type type;

    union 
    {
        double var;
        func_t *fun;
    } value;

    struct symrec *next;
    
} symrec;

extern symrec *sym_table;

symrec *putsym (char const *name, symrec_type sym_type);
symrec *getsym (char const *name);

typedef struct init
{
    char const *name;
    func_t *fun;
} init;

void init_table(void);

#endif