%{
  #include <stdio.h>
  #include "bison.tab.h"

%}

%%

\n  { return *yytext; }
"exit" { return EXIT; }

[0-9]+		{ 
				yylval.integer = atoi(yytext);
				return INTEGER;
			}

[a-zA-Z]   {
				yylval.character = *yytext;
				return CHARACTER;
			}

[a-zA-Z0-9]+ {
				yylval.string = strdup(yytext);
				return STRING;
			 }

.			{   yylval.character = *yytext;
				return SYMBOL;
			}
%%


