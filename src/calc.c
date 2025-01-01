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
    { "log", log10 },
    { "sqrt", sqrt },
    { 0, 0 }
};

Symbol *symbolTable;

Symbol* allocateSymbol(){
    Symbol *symbol = (Symbol*) malloc(sizeof(Symbol));
    if(symbol == NULL){
        return NULL;
    }

    symbol->type = eVAR;
    symbol->value.number = 0;
    symbol->value.function = NULL;

    symbol->next = symbolTable;
    symbolTable = symbol;

    return symbol;
}

void init_table(void)
{
    symbolTable = NULL;
    for (int i = 0; funs[i].name; i++){
        Symbol *ptr = putsym(funs[i].name, eFUN);
        ptr->value.function = funs[i].fun;
    }
}

Symbol *putsym(char const *name, SymbolType symbolType)
{
    Symbol *symbol = allocateSymbol();
    
    if(symbol == NULL){
        return NULL;
    }

    symbol->name = strdup(name);
    symbol->type = symbolType;
    symbol->value.number = 0;
   
    return symbol;
}

Symbol *getsym(char const *name){
    // fprintf(stderr, "tring to find name: %s\n", name );
    for(Symbol *symbol = symbolTable; symbol != NULL; symbol = symbol->next){
        if(strcmp(symbol->name, name) == 0){
            // fprintf(stderr, "found name: %f\n", sym->value.var );
            return symbol;
        }
    }
    return NULL;
}

Expression* allocateExpression(){
    Expression *expression = (Expression*) malloc(sizeof(Expression));

    if(expression == NULL){
        return NULL;
    } 

    expression->first = NULL;
    expression->second = NULL;
    expression->symbol = NULL;
    expression->number = 0;
    expression->expressionType = eVAL;

    return expression;
}

Expression* createNumberExpression(double number){
    Expression *expression = allocateExpression();

    if(expression == NULL){
        return NULL;
    }

    expression->expressionType = eVAL;
    expression->number = number;

    return expression;
}

Expression* createVariableExpression(Symbol* symbol){
    Expression *expression = allocateExpression();

    if(expression == NULL){
        return NULL;
    } 

    expression->expressionType = eSYM;
    expression->symbol = symbol;

    return expression;
}

Expression* createSymbolExpression(Symbol* symbol, Expression* first){
    Expression *expression = allocateExpression();

    if(expression == NULL){
        return NULL;
    }

    expression->expressionType = eSYM;
    expression->symbol = symbol;
    expression->first = first;

    return expression;
}

Expression* createUnaryOperation(ExpressionType expressionType, Expression* first){
    Expression *expression = allocateExpression();

    if(expression == NULL){
        return NULL;
    } 

    expression->expressionType = expressionType;
    expression->first = first;
    
    return expression;
}

Expression* createBinaryOperation(ExpressionType expressionType, Expression* first, Expression* second){
    Expression *expression = allocateExpression();

    if(expression == NULL){
        return NULL;
    } 

    expression->expressionType = expressionType;
    expression->first = first;
    expression->second = second;

    return expression;
}


double evaluate(Expression* expression){
    switch(expression->expressionType){
        case eADD: 
            return evaluate(expression->first) + evaluate(expression->second);
        case eMUL: 
            return evaluate(expression->first) * evaluate(expression->second);
        case eSUB: 
            return evaluate(expression->first) - evaluate(expression->second);
        case eDIV: 
            return evaluate(expression->first) / evaluate(expression->second);
        case ePOW: 
            return pow(evaluate(expression->first), evaluate(expression->second));
        case eNEG:
            return - evaluate(expression->first);
        case eVAL:
            return expression->number;
        case eSYM:
            switch(expression->symbol->type){
                case eVAR:
                    if(expression->first){
                        expression->symbol->value.number = evaluate(expression->first);
                    }
                    return expression->symbol->value.number;
                case eFUN:
                    return expression->symbol->value.function(evaluate(expression->first));
            }
    }
}
