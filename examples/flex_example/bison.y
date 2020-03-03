%{

    #include <stdio.h>
    #include <stdlib.h>

	void yyerror(const char* s);
    int yylex(void);
    
%}

%union {
    int integer;
    char character;
    char * string;
}

/* declare tokens */
%token <integer> INTEGER
%token <character> CHARACTER SYMBOL
%token <string> STRING
%token EXIT

%%
input:
    | input line
    ;
line: '\n'
	| STRING '\n' { printf("Here is the incoming string: %s\n", $1); }
    | INTEGER '\n' { printf("Here is the incoming number: %d\n", $1); }
    | CHARACTER '\n' { printf("Here is the incoming char: %c\n", $1); }
    | SYMBOL '\n' { printf("Here is a symbol: %c\n", $1); }
    | EXIT '\n' { YYACCEPT; }
    ;

%%

void yyerror(const char* s) { 
    fprintf (stderr, "%s\n", s);
	exit(-1);
}
