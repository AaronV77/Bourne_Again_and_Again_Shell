#include <stdio.h>
#include <stdlib.h>

int yy_scan_string(const char *);
int yylex_destroy(void);
void yyparse();

int main(int argc, char ** argv, char ** envp) {
  
  	printf("Starting to parse the incoming input...\n");
    for (int i = 0; i < 2; i++) {
        yy_scan_string("9\n9\n");
        yyparse();
        yylex_destroy();
    }
  	printf("Finished parsing the input...\n");
  	return 0;
  
}
