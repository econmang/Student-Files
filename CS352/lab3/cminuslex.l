/* 
	Evan Conley
	CS 352
	Lab 3
*/

%option noyywrap
%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	int lineNo = 1;
	int position = 0;
	

	struct Node
{
	int line;
	int pos;
	char* lexeme;
	struct Node* next;
};

struct Node* head;
Insert(int li, char* id, int p)
{
	if (head == NULL)
	{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		char* a = (char*)malloc(sizeof(*id));
		strcpy(a,id);
		temp->line   = li;
		temp->lexeme = a;
		temp->pos    =  p;
		temp->next = head;
		head = temp;
	}
	else
	{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		char* a = (char*)malloc(sizeof(*id));
		strcpy(a,id);;
		temp->line   = li;
		temp->lexeme = a;
		temp->pos    =  p;
		struct Node* temp1 = head;
		while(temp1->next != NULL)
		{
			temp1 = temp1->next;
		}
		temp1->next = temp;
	}
}
SymbolTable()
{
	printf("SYMBOL TABLE ENTRIES:\n");
	struct Node* temp = head;
	while(temp != NULL)
	{
		printf("%d: %s (%d)", temp->line, temp->lexeme, temp->pos);
		temp = temp->next;
		printf("\n");
	}
}

%}

%x COMMENT

WHITESPACE					[ \t]+
LINE 						\n
DIGIT						[0-9]
NUM 						{DIGIT}{DIGIT}*
LETTER						[A-Za-z]
ID 							{LETTER}{LETTER}*
%%

				{
					if(lineNo == 1)
					{
						printf("%d:\n",lineNo);
						lineNo++;
					}
				}
{LINE}			{
					printf("%d:\n",lineNo);
					lineNo++;
					position = 0;
				}
{NUM} 			printf("found NUM token\n");
{WHITESPACE}	{;}
"while"			printf("found WHILE token\n");
"+"				printf("found PLUS token\n");
"if"			printf("found IF token\n");
"else"			printf("found ELSE token\n");
"int"			printf("found INT token\n");
"return"		printf("found RETURN token\n");
"void"			printf("found VOID token\n");
"-"				printf("found MINUS token\n");
"*"				printf("found TIMES token\n");
"/"				printf("found OVER token\n");
"<"				printf("found LT token\n");
"<="			printf("found LTEQ token\n");
">"				printf("found GT token\n");
">="			printf("found GTEQ token\n");
"=="			printf("found EQ token\n");
"!="			printf("found NEQ token\n");
"="				printf("found ASSIGN token\n");
";"				printf("found SEMI token\n");
","				printf("found COMMA token\n");
"("				printf("found LPAREN token\n");
")" 			printf("found RPAREN token\n");
"["				printf("found LBRACKET token\n");
"]"				printf("found RBRACKET token\n");
"{"				printf("found LBRACE token\n");
"}"				printf("found RBRACE token\n");
{ID}			{
					Insert(lineNo-1,yytext,position);
					printf("found ID token\n");
					position++;
				}

"/*"         			BEGIN(COMMENT);
<COMMENT>[^*\n]*
<COMMENT>"*"+[^*/]*
<COMMENT>\n 			{
							printf("%d:\n",lineNo);
							lineNo++;
						}
<COMMENT><<EOF>>		{
							printf("error: EOF in comment");
							BEGIN(INITIAL);
						}
<COMMENT>"*"+"/"	 	BEGIN(INITIAL);

%%
int main(void)
{
	yylex();
	printf("\n");
	SymbolTable();
	return 0;
}