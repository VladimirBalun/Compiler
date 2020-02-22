# Implementation of the primitive compiler

##  🔴 Language BNF grammar

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

##  🔴 Example of the program with current grammar

    int value1;
    int value2;
    int result1;
    int result2;
    
    value1 = 5;
    value2 = 15;
    result1 = 0;
    result2 = 0;
    
    result1 = value1 * value2 - value2 / value1;
    result2 = value1 + value1 * value2 + value2;

## 🔴 How to build compiler

Current project uses CMake system for building application. You can build compiler by your platform, using the following commands:

    mkdir Build
    cd Build
    cmake ..

## 🔴 How to use compiler

List of arguments for compilation:

    Program usage:
      -h [ --help ]         Show help message.
      -i [ --input ] arg    Input source file.
      -o [ --output ] arg   Output executable file.

Example of usage compiler:

    ./Compiler -i SourceFile.as -o ExecutableFile      
