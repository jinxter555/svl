%{
#include <iostream>
#include <string>
#include <cmath>
#include "Scanner1.hpp"

%}

%union {
  string str;
  int num;
}

%token <str> ID
%token <num> NUM
%token COMMA IADD MOV


%%
lines: %empty
  : lines line
  ;

line: EOL

program
  : instruction
  | program instruction
  ;

instruction
  : IADD ID "," ID "," ID { printf("iadd %s, %s, %s\n", $2, $4, $6); }
  | MOV ID, NUM { printf ("mov %s, %d\n", $2, $4); }
  ;
%%


int main() {
  yyparse();
}
