# Implementation of the primitive compiler

## Language BNF grammar

    program           -> declaration_lists | expression_lists
    declaration_lists -> declaration_lists var_declaration | var_declaration
    var_declaration   -> type_specifier identifier;
    type_specifier    -> byte | short | int | long
    
    expression_lists  -> expression_lists expression | expression
    expression        -> mutable = common_expression;
    common_expression -> sum_expression mul_operator mul_expression | mul_expression mul_operator sum_expression | 
                         sum_expression sum_operator mul_expression | mul_expression sum_operator sum_expression |   
                         sum_expression | mul_expression                     
    sum_expression    -> sum_expression sum_operator factor | factor sum_operator factor
    mul_expression    -> mul_expression mul_operator factor | factor mul_operator factor
    factor            -> mutable | imutable
    mutable           -> identifier
    imutable          -> expression | constant
    sum_operator      -> + | -
    mul_operator      -> * | / 
    constant          -> digit
    
    identifier  -> letter_listdigit_list | letter_list 
    letter_list -> letter_list letter | letter
    digit_list  -> digit_list digit | digit
    letter      -> a | ... | z | A | ... | Z
    digit       -> 0 | ... | 9

## Example of the program with current grammar

    int value_1;
    int value_2;
    int result_1;
    int result_2;
    
    value_1 = 5;
    value_2 = 15;
    result_1 = 0;
    result_2 = 0;
    
    result_1 = value_1 * value_2 - value_2 / value_1;
    result_2 = value_1 + value_1 * value_2 + value_2;
