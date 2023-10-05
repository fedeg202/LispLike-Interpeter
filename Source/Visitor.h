
#ifndef VISITOR_H
#define VISITOR_H

#include <vector>

#include "SymbolTable.h"

class Program;	//forward declaration of class Program

class Block;	//forward declaration of class Block

//forward declaration of classes in the hierarchy Statement
class PrintStmt;
class SetStmt;
class InputStmt;
class WhileStmt;
class IfStmt;

//forward declaration of classes in the hierarchy NumExpr
class Number;
class Operator;
class Variable;

//forward declaration of classes in the hierarchy BoolExpr
class RelOp;
class BoolOp;
class BoolConst;
class NotOp;

//abstract class Visitor for the visit of the program
class Visitor {
public:
	virtual ~Visitor() {};
	
	//abstract method for the visit of the program
	virtual void visitProgram(Program* prog) = 0;

	//abstract method for the visit of the block statement
	virtual void visitBlockStmt(Block* block) = 0;

	//abstract method for the visit of concrete elements in the hierarchy Statement
	virtual void visitPrintStmt(PrintStmt* p_stmt) = 0;
	virtual void visitSetStmt(SetStmt* s_stmt) = 0;
	virtual void visitInputStmt(InputStmt* in_stmt) = 0;
	virtual void visitWhileStmt(WhileStmt* w_stmt) = 0;
	virtual void visitIfStmt(IfStmt* if_stmt) = 0;

	//abstract method for the visit of concrete elements in the hierarchy NumExpr
	virtual void visitNumber(Number* num) = 0;
	virtual void visitOperator(Operator* op) = 0;
	virtual void visitVariable(Variable* var) = 0;

	//abstract method for the visit of concrete elements in the hierarchy BoolExpr
	virtual void visitRelOp(RelOp* rop) = 0;
	virtual void visitBoolOp(BoolOp* bop) = 0;
	virtual void visitBoolConst(BoolConst* bc) = 0;
	virtual void visitNotOp(NotOp* nop) = 0;


private:
	
};

//concrete class for terminal printing the program, useful for debug
class PrintVisitor : public Visitor {
public:

	~PrintVisitor() {};
	
	//concrete method for terminal printing the Program
	void visitProgram(Program* prog) override;

	//concrete method for terminal printing statement block
	void visitBlockStmt(Block* block) override;

	//concrete method for terminal prinitng concrete elements in the hierarchy Statement
	void visitPrintStmt(PrintStmt* p_stmt) override;
	void visitSetStmt(SetStmt* s_stmt) override;
	void visitInputStmt(InputStmt* in_stmt) override;
	void visitWhileStmt(WhileStmt* w_stmt) override;
	void visitIfStmt(IfStmt* if_stmt) override;

	//concrete method for terminal prinitng concrete elements in the hierarchy NumExpr
	void visitNumber(Number* num) override;
	void visitOperator(Operator* op) override;
	void visitVariable(Variable* var) override;

	//concrete method for terminal prinitng concrete elements in the hierarchy BoolExpr
	void visitRelOp(RelOp* rop) override;
	void visitBoolOp(BoolOp* bop) override;
	void visitNotOp(NotOp* nop) override;
	void visitBoolConst(BoolConst* bc) override;
private:

};

//concrete class for evaluating program
class EvaluationVisitor : public Visitor {
public:

	~EvaluationVisitor() {};

	//concrete method for evaluating the program
	void visitProgram(Program* prog) override;

	//concrete method for evaluating block statement
	void visitBlockStmt(Block* block) override;

	//concrete method for evaluating concrete elements in the hierarchy statement
	void visitPrintStmt(PrintStmt* p_stmt) override;
	void visitSetStmt(SetStmt* s_stmt) override;
	void visitInputStmt(InputStmt* in_stmt) override;
	void visitWhileStmt(WhileStmt* w_stmt) override;
	void visitIfStmt(IfStmt* if_stmt) override;

	//concrete method for evaluating concrete elements in the hierarchy NumExpr
	void visitNumber(Number* num) override;
	void visitOperator(Operator* op) override;
	void visitVariable(Variable* var) override;

	//concrete method for evaluating concrete elements in the hierarchy BoolExpr
	void visitRelOp(RelOp* rop) override;
	void visitBoolOp(BoolOp* bop) override;
	void visitNotOp(NotOp* nop) override;
	void visitBoolConst(BoolConst* bc) override;

private:
	SymbolTable ST;

	std::vector<bool> accumulatorBool;
	std::vector<int64_t> accumulatorInt;
	
};
#endif // !VISITOR_H
