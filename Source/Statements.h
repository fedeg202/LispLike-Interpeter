#ifndef STATEMENTS_H
#define STATEMENTS_H



#include "NumExpr.h"
#include "BoolExpr.h"


class Visitor; //forward declaration of Visitor class
class Block;   //forward declaration of Block class

//abstract class for handling statement 
class Statement {
public:
	virtual ~Statement() {};
	virtual void accept(Visitor* v) = 0;

};

//concrete class for handling statement PRINT
class PrintStmt : public Statement {
public:
	PrintStmt(NumExpr* ne) : n_expr {ne} {}
	
	NumExpr* getNumExpr() {
		return n_expr;
	}
	//pattern visitor
	void accept(Visitor* v) override;

private:
	NumExpr* n_expr;
};

//concrete class for handling statement SET
class SetStmt : public Statement {
public:

	SetStmt(Variable* v,NumExpr* ne) : var {v}, n_expr{ne} {}
	
	//access methods
	Variable* getVar() {
		return var;
	}
	NumExpr* getNumExpr() {
		return n_expr;
	}
	//pattern visitor
	void accept(Visitor* v) override;

private:
	Variable* var;
	NumExpr* n_expr;
};

//concrete class for handling statement INPUT
class InputStmt : public Statement {
public:
	InputStmt(Variable* v) : var{v} {}
	
	//metodo di accesso
	Variable* getVar() {
		return var;
	}
	//pattern visitor
	void accept(Visitor* v) override;

private:
	Variable* var;
};

//concrete class for handling statement WHILE
class WhileStmt : public Statement {
public:
	WhileStmt(BoolExpr* be, Block* B) : bool_expr{ be } , stmt_block { B } {}
	
	//access methods
	BoolExpr* getBoolExpr() {
		return bool_expr;
	}
	Block* getBlock() {
		return stmt_block;
	}

	//pattern visitor
	void accept(Visitor* v) override;

private:
	BoolExpr* bool_expr;
	Block* stmt_block;

};

//concrete class for handling statement IF
class IfStmt : public Statement {
public:
	IfStmt(BoolExpr* be,Block* bs1,Block* bs2) : bool_expr {be}, block_stmt1 {bs1}, block_stmt2 {bs2} {}

	//access methods
	BoolExpr* getBoolExpr() {
		return bool_expr;
	}
	Block* getBlock1() {
		return block_stmt1;
	}
	Block* getBlock2() {
		return block_stmt2;
	}

	//pattern visitor
	void accept(Visitor* v) override;

private:
	BoolExpr* bool_expr;
	Block* block_stmt1;
	Block* block_stmt2;
};

#endif 

