#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "Program.h"


//concrete class for handling the Statement nodes
class StatementManager {
public:
	StatementManager() = default;
	~StatementManager() {
		clearMemoryStmt();
	}

	StatementManager(const StatementManager& other) = delete;
	StatementManager& operator=(const StatementManager& other) = delete;
	//nodes creation methods
	Statement* makePrintStmt(NumExpr* num_expr);
	Statement* makeSetStmt(Variable* v, NumExpr* num_expr);
	Statement* makeInputStmt(Variable* v);
	Statement* makeWhileStmt(BoolExpr* bool_expr, Block* block_stmt);
	Statement* makeIfStmt(BoolExpr* bool_expr,Block* block_stmt1,Block* block_stmt2);
	//method for freeing the allocated memory
	void clearMemoryStmt();

private:
	std::vector<Statement*> stmt_allocated;
};

//concrete class for handling the NumExpr nodes
class NumExprManager {
public:
	NumExprManager() = default;
	~NumExprManager() {
		clearMemoryNumExpr();
	}

	NumExprManager(const NumExprManager& other) = delete;
	NumExprManager& operator=(const NumExprManager& other) = delete;
	
	//nodes creation methods
	Operator* makeOperator(Operator::Opcode op, NumExpr* num_expr1,NumExpr* num_expr2);
	Number* makeNumber(int64_t value);
	Variable* makeVariable(std::string v_id);

	//method for freeing the allocated memory
	void clearMemoryNumExpr();
private:
	std::vector<NumExpr*> numexpr_allocated;

};

//concrete class for handling the boolean expressions nodes
class BoolExprManager {
public:
	BoolExprManager() = default;
	~BoolExprManager() {
		clearMemoryBoolExpr();
	};

	BoolExprManager(const BoolExprManager& other) = delete;
	BoolExprManager& operator=(const BoolExprManager& other) = delete;
	
	//nodes creation methods
	RelOp* makeRelOp(RelOp::RelOpcode op, NumExpr* num_expr1, NumExpr* num_expr2);
	BoolConst* makeBoolConst(bool bool_const);
	BoolOp* makeBoolOp(BoolOp::BoolOpcode op,BoolExpr* Bool_expr1,BoolExpr* Bool_expr2);
	NotOp* makeNotOp(BoolExpr* Bool_expr);
	
	//method for freeing the allocated memory
	void clearMemoryBoolExpr();
private:
	std::vector <BoolExpr*> boolexpr_allocated;
};

//concrete class for handling the Block nodes
class BlockManager {
public:
	BlockManager() = default;
	~BlockManager() {
		clearMemoryBlock();
	}

	BlockManager(const BlockManager& other) = delete;
	BlockManager& operator=(const BlockManager& other) = delete;

	//node creation methods
	Block* makeBlock(std::vector <Statement*> stmt_vect);

	//access methods
	StatementManager& get_Sm() {
		return sm;
	}
	BoolExprManager& get_Bem() {
		return bem;
	}
	NumExprManager& get_Nem() {
		return nem;
	}
	
	//method for freeing the allocated memory
	void clearMemoryBlock();

private:
	std::vector<Block*> B_allocated;
	StatementManager sm;
	BoolExprManager bem;
	NumExprManager nem;

	
};

#endif // 

