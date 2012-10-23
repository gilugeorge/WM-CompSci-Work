%{
#include "parser-defs.h"
#include "parser.tab.h"

/*
 * You may want to use this string to assemble the lexeme
 * of string constants by adding the current matched character from yytext to it.
 * You can do this as buffer += yytext;
 */
string buffer;


/*
 * You may want to track the comment desting depth with this variable.
 */
int comment_depth = 0;

%}


%option noyywrap

WHITESPACE [ \t\f\r\v]+
NEWLINE [\n]
COMMA [,]
READSTRING [r][e][a][d][S][t][r][i][n][g]
READINT [r][e][a][d][I][n][t]
PRINT [p][r][i][n][t]
ISNIL [i][s][N][i][l]
HD [!]
TL [#]
CONS [@]
NIL [n][i][l]
WITH [w][i][t][h]
LET [l][e][t]
PLUS [+]
MINUS [-]
TIMES [*]
DIVIDE [/]
INT [0-9]+
LPAREN [(]
RPAREN [)]
AND [&]
OR [|]
EQ [=]
GT [>]
LT [<]
LEQ ["<="]
IF [i][f]
THEN [t][h][e][n]
ELSE [e][l][s][e]
LAMBDA [l][a][m][b][d][a]
FUN [f][u][n]
IN [i][n]
IDENTIFIER [_a-zA-Z]+[_a-zA-Z0-9]*
STR [a-z0-9]*
 
%x STRING
%x COMMENT 

%%


\" {
  BEGIN(STRING);
}

{WHITESPACE} {
  /* Do nothing */
}

{NEWLINE} {
/* Do nothing, but increment line numbers */
 curr_lineno++;
}

{COMMA} {
  return TOKEN_COMMA;
}

{READSTRING} {
	
  return TOKEN_READSTRING;
}

{READINT} {
	
  return TOKEN_READINT;
}

{PRINT} {
	
  return TOKEN_PRINT;
}

{ISNIL} {
	
  return TOKEN_ISNIL;
}

{HD} {
	return TOKEN_HD;
}

{TL} {
	return TOKEN_TL;
}

{CONS} {
	return TOKEN_CONS;
}

{NIL} {
	return TOKEN_NIL;
}

"." {
	return TOKEN_DOT;
}

{WITH} {
	return TOKEN_WITH;
}

{LET} {
	return TOKEN_LET;
}

{PLUS} {
	return TOKEN_PLUS;
}

{MINUS} {
	return TOKEN_MINUS;
}

{TIMES} {
	return TOKEN_TIMES;
}

{DIVIDE} {
	return TOKEN_DIVIDE;
}

{INT} {
	SET_LEXEME(yytext);
	buffer += yytext;
	return TOKEN_INT;
}

{LPAREN} {
	return TOKEN_LPAREN;
}

{RPAREN} {
	return TOKEN_RPAREN;
}

{AND} {
	return TOKEN_AND;
}

{OR} {
	return TOKEN_OR;
}

{EQ} {
	return TOKEN_EQ;
}

"<>" {
	return TOKEN_NEQ;
}

{GT} {
	return TOKEN_GT;
}

">=" {
	return TOKEN_GEQ;
}

{LT} {
	return TOKEN_LT;
}

"<=" {
	return TOKEN_LEQ;
}

IF {
	return TOKEN_IF;
}

{THEN} {
	return TOKEN_THEN;
}

{ELSE} {
	return TOKEN_ELSE;
}

{LAMBDA} {
	return TOKEN_LAMBDA;
}

{FUN} {
	return TOKEN_FUN;
}

{IN} {
	return TOKEN_IN;
}

{IDENTIFIER} {
	SET_LEXEME(yytext);
	return TOKEN_IDENTIFIER;
}

<STRING>\" {
	BEGIN(INITIAL);
}

<STRING>{STR}[^\"]* {
	SET_LEXEME(yytext);
  return TOKEN_STRING;
}

. {
  /* Leave this rule at the end of our lexer to "eat up" all illegal strings */
  SET_LEXEME("Unexpected character in input");
  return TOKEN_ERROR;
}



