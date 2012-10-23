#include "ConstantType.h"
#include "VariableType.h"
#include "FunctionType.h"
#include "ast/expression.h"
#include "TypeInference.h"
#include "Expression.h"

//Global Variables to allow comparisons
Type* CompInt= ConstantType::make("Int");
Type* CompString= ConstantType::make("String");
Type* CompVars= VariableType::make("x");
SymbolTable sym;
vector<Expression*> lambIDS; //store ids
vector<Expression*> lambAssign; //store lambda assigned values


TypeInference::TypeInference(Expression * e)
{
	this->program = e;
	lambIDS = vector<Expression*>();
	lambAssign = vector<Expression*>();
	sym.push();
	eval(e);
}

/**Recursively evaluates expressions.

*/
Type* TypeInference::eval(Expression* e){

	//check if it is a basic type
	//if it is return the type or look up ID, otherwise go to else
	if(e->get_type_inference(e)!=NULL){
		if(e->get_type_inference(e)== VariableType::make("x")){
			AstIdentifier* t= static_cast<AstIdentifier*>(e);
			Expression* id= sym.find(t);
			if(id!= NULL){
				Type* idType= eval(id);
				return idType;
			} 	
		}
		//cout<< e->to_string()<< endl;	
		return e->get_type_inference(e);
	}	
	else{

		/*Check all BinOp Cases*/
		if(e -> get_type() == AST_BINOP){
			//retrieve Expression types within BinOP for comparison
			AstBinOp* bin= static_cast<AstBinOp*>(e);
			Expression* b1= bin->get_first();
			Expression* b2= bin->get_second();
			Type* tB1= eval(b1);
			Type* tB2= eval(b2);

			//In the case of a Cons
			if(bin -> get_binop_type()== CONS){ //check for all combinations of lists
				if(tB1==tB2 || (tB1== ConstantType::make("Int") &&  tB2==ConstantType::make("IntList")) 
						|| (tB1==ConstantType::make("IntList") && tB2==ConstantType::make("Int")) 
						|| (tB1==ConstantType::make("String") && tB2==ConstantType::make("StringList")) 
						|| (tB1==ConstantType::make("StringList") && tB2==ConstantType::make("String"))){
					
					if(tB1== ConstantType::make("Int") || tB1==ConstantType::make("IntList")){//return IntList
					//cout<< ConstantType::make("IntList")->to_string()<< endl;						
						return ConstantType::make("IntList");
					}
					else{ //return StringList
						//cout<< ConstantType::make("StringList")->to_string()<< endl;
						return ConstantType::make("StringList");
					}
				}//end giant if statement
			}//end cons section
			
			//Ensures that Strings are only used in Eq and Neq. Everything else fails
			else if(bin -> get_binop_type() != EQ && bin -> get_binop_type() != NEQ 
							&& (tB1==ConstantType::make("String") || tB2==ConstantType::make("String"))){
				cout<<"Invalid Typing "<<endl;
				return Failure;
			}

			//Types the String comparison to Int(for 1 or 0)
			else if((bin -> get_binop_type()== EQ || bin -> get_binop_type()== NEQ) 
								&& tB1==ConstantType::make("String") && tB2==ConstantType::make("String")){
				//cout<<ConstantType::make("Int")->to_string() <<endl;
				return ConstantType::make("Int");
			}		
			else{//covers all other cases
				if(tB1==tB2){
					cout<< "Type success "<< tB1->to_string()<< endl;				
					return tB2;
				}
				else{
					cout<< "Invalid Type" << endl;
					return Failure;
					exit(1);
				}
			}
		}//ASTBINOp

		//AST_BRANCH
		if(e->get_type()== AST_BRANCH){
			AstBranch* bra= static_cast<AstBranch*>(e);
			Type* predType= eval(bra->get_pred());

			if(predType == ConstantType::make("Int")){
				Type* thenType= eval(bra -> get_then_exp());
				Type* elseType = eval(bra -> get_else_exp());

				if(thenType != Failure && elseType != Failure){
					cout<< "Expressions are successfully typed" << endl;
					if(elseType == thenType){
						return elseType;
					}
					else{
						return Failure;
					}
				}
				else if(elseType == Failure && thenType !=Failure){
					cout<<"Else is not properly typed"<< endl;
					return Failure;
				}
				else if(thenType ==Failure && elseType !=Failure){
					cout<<"Then is not properly typed"<< endl;
					return Failure;
				}
				else{
					cout<<"None of this typed correctly"<< endl;
					return Failure;
				}
			}//end large if
		}//Branch

		//AST_EXPRESSION_LIST
		if(e -> get_type() == AST_EXPRESSION_LIST){
			AstExpressionList* eList= static_cast<AstExpressionList*>(e);
			vector<Expression*> exVector= eList -> get_expressions();

			//checks that there aren't more id's than lambda's
			if(lambIDS.size()+1 < exVector.size()){ 
				lambAssign.push_back(exVector[lambIDS.size()+1]);
			}
			//cout<< eList->to_string()<< endl;
			Type* lambdaType = eval(exVector[0]); //evaluate lambda
			//cout<< lambdaType -> to_string() << endl;
			return lambdaType;
		}//AST_EXPRESSION_LIST

		//checks that for ReadInt or ReadString
		if(e -> get_type() == AST_READ){
			AstRead* t= static_cast<AstRead*>(e);
			if(t->read_integer() == 1){
				//cout<<"Int"<<endl;
				return ConstantType::make("Int");
			}
			else{
				//cout<<"String"<<endl;
				return ConstantType::make("String");
			}
		}//AST_Read

		//AST_LET
		if(e -> get_type() == AST_LET){
			AstLet* l= static_cast<AstLet*>(e);
			if(l -> get_val()->get_type()== AST_LAMBDA){
					Type* letType = eval( l->get_body() );
				if(letType == ConstantType::make("Int")){
					AstInt* tempI= AstInt::make(1);				
					sym.add(l->get_id(), tempI);
				}
				else{
					AstString* tempS= AstString::make("1");
					sym.add(l->get_id(), tempS);
				}

				//check the body//
				Type* body= eval(l -> get_val());
				if(body == letType){
					return body;
				}
				else{
					return Failure;
				}
			}
			else{
				Type* letType = eval( l->get_val() );
				if(letType == ConstantType::make("Int")){
					AstInt* tempI= AstInt::make(1);				
					sym.add(l->get_id(), tempI);
				}
				else{
					AstString* tempS= AstString::make("1");
					sym.add(l->get_id(), tempS);
				}

				//check the body//
				Type* body= eval(l -> get_body());
				if(body == letType){
					return body;
				}
				else{
					return Failure;
				}
			}
		}//AST_LET

		//AST_LAMBDA	
		if(e -> get_type()== AST_LAMBDA){
			AstLambda* lambda= static_cast<AstLambda*>(e);
			lambIDS.push_back(lambda -> get_formal()); 
			AstIdentifier* tempLID; //create a temporary lambda ID

			if(lambda -> get_formal() -> get_type() == AST_IDENTIFIER){
				tempLID= static_cast<AstIdentifier*>(lambda->get_formal());
			}

			//equal lambdas, return the type
			if(lambAssign.size() > 0|| lambIDS.size() > 0){	
				Expression* tA= lambAssign.back();	
				sym.add(tempLID, tA);			
				Type* lambdaType = eval(lambda -> get_body());
				//cout<< tLAMB->to_string()<< endl;
				return lambdaType;
			}
			else{//doesn't evaluate fully, and needs to return type lambda
				vector<Type*> retL;
				retL.push_back(VariableType::make("x"));
				cout<< FunctionType::make("Lambda", retL)->to_string()<< endl;
				return FunctionType::make("Lambda", retL);
			}
		}//AST_LAMBDA	

		/*Checks for UnOps*/
		if(e -> get_type() == AST_UNOP){
			AstUnOp* u = static_cast<AstUnOp*>(e);
			Expression* f= u -> get_expression();
			Type* unType= eval(f);

			if(u -> get_unop_type()== ISNIL){ //make IsNil a type Int
				//cout<< ConstantType::make("Int")->to_string()<< endl; 						
				return ConstantType::make("Int");
			}
			else if(u -> get_unop_type()== PRINT){ //Make Print a type Int
				//cout<< ConstantType::make("Int")->to_string()<< endl; 						
				return ConstantType::make("Int");
			}//finish Print Check
			else if(u -> get_unop_type()== HD){ //Check HD type
				if(unType== ConstantType::make("Int") || unType== ConstantType::make("IntList")){
					//cout<< ConstantType::make("Int")->to_string()<< endl; 						
					return ConstantType::make("Int");
				}
				if(unType==ConstantType::make("String") || unType== ConstantType::make("StringList")){
					//cout<< ConstantType::make("String")->to_string()<< endl; 					
					return ConstantType::make("String");
				}
				else{
					return Failure;
				}
			}//finish HD check
			else if(u -> get_unop_type()== TL){
				if(unType== ConstantType::make("IntList")){
					//take list and convert from ASTList to Type*
					AstList* iList= static_cast<AstList*>(f);
					Expression* intTL= iList->get_tl();
					Type* iListType= eval(intTL);										
					//cout<< iListType->to_string()<< endl; 						
					return iListType;
				}
				else if(unType== ConstantType::make("Int")){
					//cout<< unType->to_string()<< endl; 						
					return unType;
				}
				else if(unType== ConstantType::make("StringList")){
					//cout<< unType -> to_string()<< endl; 					
					return unType;
				}
				else if(unType == ConstantType::make("String")){
					//cout<< unType ->to_string()<< endl; 					
					return unType;
				}
				else{
					return Failure;
				}
			}//finish TL check
		}//AST_UNOP
 	
	}//end of the else statements
	
	return Failure;
}//eval()
