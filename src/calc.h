#ifndef CALC_H
#define CALC_H

typedef enum ExpressionType {
    // Binary Op
    eADD,
    eMUL,
    eSUB,
    eDIV,
    ePOW,

    // Unary Op
    eNEG,

    // Val
    eVAL,
    eSYM,
} ExpressionType;

typedef enum SymbolType {
    eFUN,
    eVAR,
} SymbolType;

typedef double (func_t) (double);

typedef struct Expression {
    enum ExpressionType expressionType;

    double number;
    struct Symbol *symbol;
    struct Expression *first;
    struct Expression *second;
} Expression;

typedef struct Symbol
{
    char *name;
    SymbolType type;

    union 
    {
        double number;  // Some value
        func_t *function;    // Some function
    } value;

    struct Symbol *next;
    
} Symbol;

extern Symbol *symbolTable;

Symbol *putsym (char const *name, SymbolType sym_type);
Symbol *getsym (char const *name);

typedef struct init
{
    char const *name;
    func_t *fun;
} init;

void init_table(void);

Expression* createNumberExpression(double number);
Expression* createSymbolValueExpression(char const* identifier);
Expression* createSymbolAssignmentExpression(char const* identifier, Expression* first);
Expression* createSymbolFunctionExpression(char const* identifier, Expression* first);
Expression* createUnaryOperation(ExpressionType expressionType, Expression* first);
Expression* createBinaryOperation(ExpressionType expressionType, Expression* first, Expression* second);

double evaluate(Expression* expression);

#endif