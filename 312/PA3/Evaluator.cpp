
#include "Evaluator.h"
#include "ast/expression.h"

#include <cstdlib>




/*
 * This skeleton currently only contains code to handle integer constants, print and read. 
 * It is your job to handle all of the rest of the L language.
 */





/*
 * Call this function to report any run-time errors
 * This will abort execution.
 */
void report_error(Expression* e, const string & s)
{
	cout << "Run-time error in expression " << e->to_value() << endl;
	cout << s << endl;
	exit(1);

}



Evaluator::Evaluator()
{
	sym_tab.push();
	c = 0;

}

/*
UnOp Evaluator section
*/
Expression* Evaluator::eval_unop(AstUnOp* b)
{

	Expression* e = b->get_expression();
	Expression* eval_e = eval(e);

	if(b->get_unop_type() == PRINT) { //PRINT 
		if(eval_e->get_type() == AST_STRING) {
			AstString* s = static_cast<AstString*>(eval_e);
			cout << s->get_string() << endl;
		}//if
		else cout << eval_e->to_value() << endl;
		return AstInt::make(0);
	}else	if(b->get_unop_type() == HD) { //HD
		
		if(eval_e -> get_type() == AST_LIST){
			AstList* ret = static_cast<AstList*>(eval_e);
			return ret -> get_hd();
		}else
			return e;

	}else	if(b->get_unop_type() == TL) { //TL
		if(eval_e -> get_type() == AST_LIST){
			AstList* ret = static_cast<AstList*>(eval_e);
			return ret -> get_tl();
		}else
			return AstNil::make();

	}else	if(b->get_unop_type() == ISNIL) {//ISNIL
			//cout << "Within IsNil" << endl;
		
		if(eval_e -> get_type() == AST_NIL){
			//cout << "Within 1" << endl;
			return AstInt::make(1);
		}else{
			//cout << "Within 0" << endl;
			return AstInt::make(0);			
		}

	}else
  	assert(false);

//return 0;
}//eval_unop

/*
BinOp Evaluator section
*/
Expression* Evaluator::eval_binop(AstBinOp* b){

	Expression* f = b->get_first();
	Expression* s = b->get_second();

	//check that the expressions are BinOp's and then recurse if necessary
	Expression* e1 = eval(f);
	Expression* e2 = eval(s);

/*	if(e1->get_type() == AST_BINOP || e1->get_type() == AST_BINOP){
		if(e1->get_type() == AST_BINOP){
			AstBinOp* temp = static_cast<AstBinOp*>(e1);
			e1 = eval(temp);
		}
		if(e2->get_type() == AST_BINOP){
			AstBinOp* temp2 = static_cast<AstBinOp*>(e2);
			e2 = eval(temp2);
		}
	}
*/

	//take care of actual functions here
	if(b->get_binop_type() == PLUS) { //PLUS
			return AstInt::make( atoi(e1->to_value().c_str()) + atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == MINUS) { //MINUS
			return AstInt::make( atoi(e1->to_value().c_str()) - atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == TIMES) { //TIMES
			return AstInt::make( atoi(e1->to_value().c_str()) * atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == DIVIDE) {//DIVIDE
			return AstInt::make( atoi(e1->to_value().c_str()) / atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == AND) {//AND
			return AstInt::make( atoi(e1->to_value().c_str()) && atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == OR) {//OR
			return AstInt::make( atoi(e1->to_value().c_str()) || atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == EQ) {//EQ
			return AstInt::make( atoi(e1->to_value().c_str()) == atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == NEQ) {//NEQ
			return AstInt::make( atoi(e1->to_value().c_str()) != atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == LT) {//LT
			return AstInt::make( atoi(e1->to_value().c_str()) < atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == LEQ) {//LEQ
			return AstInt::make( atoi(e1->to_value().c_str()) <= atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == GT) {//GT
			return AstInt::make( atoi(e1->to_value().c_str()) > atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == GEQ) {//GEQ
			return AstInt::make( atoi(e1->to_value().c_str()) >= atoi(e2->to_value().c_str()) );

	}else	if(b->get_binop_type() == CONS) {//CONS
		Expression* ret = AstList::make(e1, e2);
		return ret;

	}else{
  	assert(false);
	}

//return 0;
}//eval_binop



Expression* Evaluator::eval(Expression* e)
{


	Expression* res_exp = NULL;
	switch(e->get_type())
	{
		case AST_BINOP:
		{
			AstBinOp* b = static_cast<AstBinOp*>(e);
			res_exp = eval_binop(b);
			break;
		}//binop

		case AST_BRANCH:
		{

			AstBranch* l = static_cast<AstBranch*>(e);
			Expression* pred = l -> get_pred();
			Expression* then = l -> get_then_exp();
			Expression* els = l -> get_else_exp();

			Expression* eval_pred = eval(pred);

			if(atoi(eval_pred->to_value().c_str()) != 0){
				res_exp = eval(then);
			}else{
				res_exp = eval(els);
			}

			break;
		}//branch

		case AST_EXPRESSION_LIST:
		{
			AstExpressionList* l = static_cast<AstExpressionList*>(e);
			vector<Expression*> vect = l -> get_expressions();
			Expression* eval_v= eval(vect[0]);
			AstLambda* bd;
			Expression* bZ;
			int i=1;
			int count=0;

			if(vect[0]->get_type()== AST_LAMBDA){ 

				AstLambda* v= static_cast<AstLambda*>(vect[0]);				
				Expression* b= v->get_body();	
				
				do{
					
					bd= static_cast<AstLambda*>(b);
					AstInt* temp= AstInt::make(atoi(vect[i]->to_value().c_str()));
					bZ= bd->substitute(v->get_formal(), temp);
					//cout << i << endl;
					i++;
					v= static_cast<AstLambda*>(bZ);
					b= v->get_body();
					//cout << e -> to_string() <<endl;
					count++;
					
				}while(i<vect.size());


		
			}else{
				//cout<<"printing here"<<endl;
				Expression* test = eval(vect[0]);

				AstExpressionList* test2 = AstExpressionList::make(test);
				AstExpressionList* test3 = static_cast<AstExpressionList*>(vect[1]);
				Expression* test4 = eval(test3 );
				
				test2 -> append_exp( test4 );
//cout<<test2->to_string() <<endl;
				Expression* test5 = eval(test2);
				res_exp = test5;
				return test5;
}


res_exp = eval(bZ);
break;
}



		/* 
		case AST_EXPRESSION_LIST:
		{
			//cast into expression list		
			AstExpressionList* l = static_cast<AstExpressionList*>(e);
			vector<Expression*> vect = l -> get_expressions();
			int counter = 0;

I was trying to use the counter again to block the while loop below from seg faulting. It hasn't been really useful
			for(int j = vect.size() -1; j > 0; j++){
				if(vect[j] -> get_type() == AST_INT){
					counter++;
				}else{
					break;
				}
			}


			Expression* eval_v = eval(vect[0]);
			if(eval_v -> get_type() == AST_LAMBDA){
				AstLambda* lamb = static_cast<AstLambda*>(eval_v);
				AstIdentifier* id = lamb -> get_formal();

				sym_tab.push();            //may or may not need this section
				sym_tab.add(id, vect[1]); //first vector section

				Expression* body = lamb -> get_body();
				Expression* eval_b = eval(body);
				
				int i = 2;
				while(eval_b -> get_type() == AST_LAMBDA /*&& i <= counter){ 
					/******need to deal with the (x + y + z  1 7) case***********************************
					AstLambda* lamb = static_cast<AstLambda*>(eval_b);

					AstIdentifier* id = lamb -> get_formal();
					sym_tab.add(id, vect[i]);
					Expression* body = lamb -> get_body();
					eval_b = eval(body);
					i++;
				}
				return eval_b;
			}

//get expre list
//eval list 0 to expression
//cast eval to lambda
//get id from formal
//add(id, list[1..etc])
//get body
//eval body
//while loop begins here
//repeat the cast, add, and shift to next lambda in body
//return eval of body

		
		}//expression list <(*_*<)*/

/*	case AST_IDENTIFIERLIST:
		{
			break;
		}//identifier list
*/


		case AST_IDENTIFIER:
		{
			AstIdentifier* l = static_cast<AstIdentifier*>(e);
			if (sym_tab.find(l) == NULL){
				report_error(e,"Identifier " + e->to_value() + " is not bound in current context");	
			}else{
				res_exp = sym_tab.find(l);
			}
				break;
		}//identifier


		case AST_INT:
		{
			res_exp = e;
			break;
		}//int

		case AST_LAMBDA:
		{						
			res_exp = e;
			break;
		}//lambda

		case AST_LET:
		{
			AstLet* l = static_cast<AstLet*>(e);
			
			Expression* id = l -> get_id();
			Expression* value = l -> get_val();
			Expression* eval_value = eval(value);
			Expression* body = l -> get_body();

			//cast here
			assert(id->get_type()  == AST_IDENTIFIER);
			AstIdentifier* i = static_cast<AstIdentifier*>(id);
			
			//add here
			sym_tab.push();
			sym_tab.add(i, eval_value);
			
			//eval and set to res_exp
			Expression* eval_body = eval(body);
			//sym_tab.print_contents();
			res_exp = eval_body;
			sym_tab.pop();

			break;
		}//let

		case AST_LIST:
		{
			AstList* l = static_cast<AstList*>(e);
			res_exp = l;
			break;
		}//list

		case AST_NIL:
		{
			return e;
			break;
		}//nil

		case AST_READ: 
		{
			AstRead* r = static_cast<AstRead*>(e);
			string input;
			getline(cin, input);
			if(r->read_integer()) {
				return AstInt::make(string_to_int(input));
			}
			return AstString::make(input);
			break;
		}//read

		case AST_STRING:
		{
			res_exp = e;
			break;
		}//string

		case AST_UNOP: //find out which unop it is, and then send to eval_unop()
	 	{
			AstUnOp* b = static_cast<AstUnOp*>(e);
			res_exp = eval_unop(b);
			break;
		}//unop

		default:
			assert(false);
		}//switch


		return res_exp;
}//eval
