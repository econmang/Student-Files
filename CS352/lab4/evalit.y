/***************************************************
File: add.y
adder Yacc/Bison specification file         
Pete Nordquist
****************************************************/
%debug

%token 	NUM
%left 	MINUS PLUS
%left 	MULT
%left 	LPAREN RPAREN

%% /* Grammar */

input		: stmt
			;

stmt		: expr {$$ = $1; printf("%d\n",$1);}
			;

expr		: expr PLUS  term {$$ = $1 + $3;}
			| expr MINUS term {$$ = $1 - $3;}
			| term
			;

term		: term MULT factor {$$ = $1 * $3;}
			| factor {$$ = $1;}
			;

factor		: LPAREN expr RPAREN {$$ = $2;}
			| NUM {$$ = $1;}
			;

%%

main()
{
//  yydebug = 1;
  return yyparse();
}

/* called by yacc if there is an error */
int yyerror(char *s)
{
  printf( "?Parser Error: %s\n",s);
}