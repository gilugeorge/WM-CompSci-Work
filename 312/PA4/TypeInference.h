#ifndef TYPE_INFERENCE_H_
#define TYPE_INFERENCE_H_
#include "SymbolTable.h"

class Expression;

class TypeInference {
private:
	Expression* program;
public:
	Type* CompInt;
	Type* Failure;
	Type* CompString;
	Type* CompVars;
	Type* FunStr;
	Type* FunInt;
	Type* Success;
	vector<Type*> vS;
	vector<Type*> vI;
	TypeInference(Expression* p);
	Type* eval(Expression* p);

};

#endif /* TYPE_INFERENCE_H_ */
