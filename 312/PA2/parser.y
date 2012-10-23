%{
#include "parser-defs.h"

int yylex();
extern int yy_scan_string(const char* c);
int yyerror(const char* p)
{ 
  if(parser_error_fn != NULL) {
    parser_error_fn("At line " + int_to_string(curr_lineno) + ": " + string(p));
  }
  return 1;
};

 



%}
/* BISON Declarations */
%token 
TOKEN_READSTRING 
TOKEN_READINT 
TOKEN_PRINT 
TOKEN_ISNIL
TOKEN_HD 
TOKEN_TL 
TOKEN_CONS 
TOKEN_NIL 
TOKEN_DOT 
TOKEN_WITH 
TOKEN_LET 
TOKEN_PLUS 
TOKEN_MINUS 
TOKEN_IDENTIFIER 
TOKEN_TIMES 
TOKEN_DIVIDE 
TOKEN_INT 
TOKEN_LPAREN 
TOKEN_RPAREN 
TOKEN_AND 
TOKEN_OR 
TOKEN_EQ 
TOKEN_NEQ 
TOKEN_GT 
TOKEN_GEQ
TOKEN_LT 
TOKEN_LEQ 
TOKEN_IF 
TOKEN_THEN 
TOKEN_ELSE 
TOKEN_LAMBDA 
TOKEN_FUN 
TOKEN_COMMA 
TOKEN_STRING 
TOKEN_ERROR 
TOKEN_IN



%nonassoc EXPR
%left TOKEN_PRINT

%left TOKEN_EQ
%left TOKEN_NEQ
%left TOKEN_GT
%left TOKEN_GEQ
%left TOKEN_LT
%left TOKEN_LEQ

%left TOKEN_AND
%left TOKEN_OR

%left TOKEN_PLUS
%left TOKEN_MINUS

%left TOKEN_TIMES
%left TOKEN_DIVIDE

%left TOKEN_ISNIL

%right TOKEN_CONS

%left TOKEN_HD
%left TOKEN_TL

%right TOKEN_LET
%right TOKEN_IN
%left TOKEN_IDENTIFIER
%right TOKEN_LAMBDA
%right TOKEN_FUN
%right TOKEN_WITH
%%







program: expression
{
	res_expr = $$;
}



expression: TOKEN_INT 
{
  	string lexeme = GET_LEXEME($1);
  	long int val = string_to_int(lexeme);
  	Expression* e = AstInt::make(val);
  	$$ = e;
}
| TOKEN_LPAREN expression TOKEN_RPAREN
{
	$$ = $2;
} 
| TOKEN_LPAREN expression_application TOKEN_RPAREN
{
	$$ = $2;
}
|
TOKEN_FUN TOKEN_IDENTIFIER TOKEN_WITH id_list TOKEN_EQ expression TOKEN_IN expression %prec EXPR
{
	string lexeme = GET_LEXEME($2);
	AstIdentifier* id = AstIdentifier::make(lexeme);
	
	Expression* _l = $4;
	assert(_l -> get_type() == AST_IDENTIFIER_LIST);
	AstIdentifierList* i = static_cast<AstIdentifierList*>(_l);
	Expression* e = AstLambda::make(i, $6);

	AstLet* l = AstLet::make(id, e, $8);
	$$ = l;
}
|
TOKEN_FUN TOKEN_IDENTIFIER TOKEN_WITH TOKEN_IDENTIFIER TOKEN_EQ expression TOKEN_IN expression %prec EXPR
{
	string lexeme = GET_LEXEME($2);
	AstIdentifier* id = AstIdentifier::make(lexeme);
	
	string lexeme2 = GET_LEXEME($4);
	AstIdentifier* _l = AstIdentifier::make(lexeme2);
	Expression* e = AstLambda::make(_l, $6);

	AstLet* l = AstLet::make(id, e, $8);
	$$ = l;
}
| 
TOKEN_LAMBDA id_list TOKEN_DOT expression %prec EXPR
{
	Expression* _l = $2;
	assert(_l -> get_type() == AST_IDENTIFIER_LIST);
	AstIdentifierList* l = static_cast<AstIdentifierList*>(_l);

	Expression* e = AstLambda::make(l, $4);
	$$ = e;
} 
| 
TOKEN_LAMBDA TOKEN_IDENTIFIER TOKEN_DOT expression %prec EXPR
{
	string lexeme = GET_LEXEME($2);
	AstIdentifier* _l = AstIdentifier::make(lexeme);
	AstLambda* e = AstLambda::make(_l, $4);
	$$ = e;
}  
|
TOKEN_STRING 
{
	string lexeme = GET_LEXEME($1);
  	Expression* e = AstString::make(lexeme);
  	$$ = e;
}
|
TOKEN_IDENTIFIER
{
	string lexeme = GET_LEXEME($1);
	Expression* e = AstIdentifier::make(lexeme);
	$$ = e;
}
|
expression TOKEN_PLUS expression 
{
	$$ = AstBinOp::make(PLUS, $1, $3);
}
|
expression TOKEN_AND expression 
{
	$$ = AstBinOp::make(AND, $1, $3);
}
|
expression TOKEN_OR expression %prec TOKEN_AND
{
	$$ = AstBinOp::make(OR, $1, $3);
}
|
expression TOKEN_MINUS expression %prec TOKEN_PLUS
{
	$$ = AstBinOp::make(MINUS, $1, $3);
}
|
expression TOKEN_TIMES expression 
{
	$$ = AstBinOp::make(TIMES, $1, $3);
}
|
expression TOKEN_DIVIDE expression %prec TOKEN_TIMES
{
	$$ = AstBinOp::make(DIVIDE, $1, $3);
}
|
expression TOKEN_EQ expression 
{
	$$ = AstBinOp::make(EQ, $1, $3);
}
|
expression TOKEN_NEQ expression %prec TOKEN_EQ
{
	$$ = AstBinOp::make(NEQ, $1, $3);
}
|
expression TOKEN_GT expression %prec TOKEN_EQ
{
	$$ = AstBinOp::make(GT, $1, $3);
}
|
expression TOKEN_GEQ expression %prec TOKEN_EQ
{
	$$ = AstBinOp::make(GEQ, $1, $3);
}
|
expression TOKEN_LT expression %prec TOKEN_EQ
{
	$$ = AstBinOp::make(LT, $1, $3);
}
|
expression TOKEN_LEQ expression %prec TOKEN_EQ
{
	$$ = AstBinOp::make(LEQ, $1, $3);
}
|
TOKEN_READINT
{
	$$ = AstRead::make($1);
}
|
TOKEN_READSTRING
{
	$$ = AstRead::make($1);
}
|
TOKEN_PRINT expression
{
	$$ = AstUnOp::make(PRINT, $2);
}
|
TOKEN_ISNIL expression
{
	$$ = AstUnOp::make(ISNIL, $2);
}
|
TOKEN_HD expression
{
	$$ = AstUnOp::make(HD, $2);
}
|
TOKEN_TL expression %prec TOKEN_HD
{
	$$ = AstUnOp::make(TL, $2);
}
|
TOKEN_NIL
{
	$$ = AstNil::make();
}
|
expression TOKEN_CONS expression
{
	$$ = AstBinOp::make(CONS, $1, $3);
}
|
TOKEN_LET TOKEN_IDENTIFIER TOKEN_EQ expression TOKEN_IN expression
{
	string lexeme = GET_LEXEME($2);
	AstIdentifier* e = AstIdentifier::make(lexeme);
	Expression* l = AstLet::make(e, $4, $6);
	$$ = l;
}
|
TOKEN_IF expression TOKEN_THEN expression TOKEN_ELSE expression %prec EXPR //who knows what this will do
{
	Expression* l = AstBranch::make($2, $4, $6);
	$$ = l;
}
|
TOKEN_ERROR
{
   // do not change the error rule
   string lexeme = GET_LEXEME($1);
   string error = "Lexing error: ";
   if(lexeme != "") error += lexeme;
   yyerror(error.c_str());
   YYERROR;
}


id_list: TOKEN_IDENTIFIER TOKEN_COMMA TOKEN_IDENTIFIER
{
	string lexeme = GET_LEXEME($1);
	AstIdentifier* i = AstIdentifier::make(lexeme);
	AstIdentifierList *l = AstIdentifierList::make(i);

	string lexeme2 = GET_LEXEME($3);
	AstIdentifier* i2 = AstIdentifier::make(lexeme2);
	
	l = l->append_id(i2);
	$$ = l;
}
|
TOKEN_IDENTIFIER TOKEN_COMMA id_list
{
	string lexeme = GET_LEXEME($1);
	AstIdentifier* i = AstIdentifier::make(lexeme);

	Expression* _l = $3;
	assert(_l -> get_type() == AST_IDENTIFIER_LIST);
	AstIdentifierList* l = static_cast<AstIdentifierList*>(_l);

	$$ = l->append_id(i);
}


expression_application: expression expression
{
	AstExpressionList *l = AstExpressionList::make($1);
	l = l->append_exp($2);
	$$ = l;
}
|
expression_application expression
{
	Expression* _l = $1;
	assert(_l->get_type() == AST_EXPRESSION_LIST);
	AstExpressionList* l = static_cast<AstExpressionList*>(_l);
	$$ = l->append_exp($2);
}


  
