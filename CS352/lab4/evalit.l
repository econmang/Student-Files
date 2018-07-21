/****************************************************
	Evan Conley
	Professor Nordquist
	CS352
	File: evalit.l
	2/20/16
****************************************************/
%option noyywrap

%{
	#include "evalit.tab.h" // get token definitions from yacc
%}

digit       [0-9]
number      {digit}+
newline	    \n
whitespace  [ \t]+

%%
"("             { return( LPAREN);}
")"				{ return( RPAREN);}
"+"             { return( PLUS);}
"-"             { return( MINUS);}
"*"				{ return( MULT);}
{number}        { yylval = atoi(yytext); return NUM;}
{newline}       {}
{whitespace}    {}
.               {printf("error: general lexer error\n");}
%%