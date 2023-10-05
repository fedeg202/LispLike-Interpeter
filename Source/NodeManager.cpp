#include "NodeManager.h"

Statement* StatementManager::makePrintStmt(NumExpr* num_expr)
{
    Statement* s = new PrintStmt(num_expr);
    stmt_allocated.push_back(s);
    return s;
}

Statement* StatementManager::makeSetStmt(Variable* v, NumExpr* num_expr)
{
    Statement* s = new SetStmt(v,num_expr);
    stmt_allocated.push_back(s);
    return s;
}

Statement* StatementManager::makeInputStmt(Variable* v)
{
    Statement* s = new InputStmt(v);
    stmt_allocated.push_back(s);
    return s;
}

Statement* StatementManager::makeWhileStmt(BoolExpr* bool_expr, Block* block_stmt)
{
    Statement* s = new WhileStmt (bool_expr,block_stmt);
    stmt_allocated.push_back(s);
    return s;
}

Statement* StatementManager::makeIfStmt(BoolExpr* bool_expr, Block* block_stmt1, Block* block_stmt2)
{
    Statement* s = new IfStmt(bool_expr, block_stmt1,block_stmt2);
    stmt_allocated.push_back(s);
    return s;
}

void StatementManager::clearMemoryStmt()
{
    auto i = stmt_allocated.begin();
    for (; i != stmt_allocated.end(); i++) {
        delete (*i);
    }
    stmt_allocated.resize(0);
}

Operator* NumExprManager::makeOperator(Operator::Opcode op, NumExpr* num_expr1, NumExpr* num_expr2)
{
    Operator* ne = new Operator(op, num_expr1, num_expr2);
    numexpr_allocated.push_back(ne);
    return ne;
}

Number* NumExprManager::makeNumber(int64_t value)
{
    Number* ne = new Number(value);
    numexpr_allocated.push_back(ne);
    return ne;
}

Variable* NumExprManager::makeVariable(std::string v_id)
{
    Variable* ne = new Variable(v_id);
    numexpr_allocated.push_back(ne);
    return ne;
}

void NumExprManager::clearMemoryNumExpr()
{
    auto i = numexpr_allocated.begin();
    for (; i != numexpr_allocated.end(); i++) {
        delete (*i);
    }
    numexpr_allocated.resize(0);
}

RelOp* BoolExprManager::makeRelOp(RelOp::RelOpcode op, NumExpr* num_expr1, NumExpr* num_expr2)
{
    RelOp* be = new RelOp(op, num_expr1, num_expr2);
    boolexpr_allocated.push_back(be);
    return be;
}

BoolConst* BoolExprManager::makeBoolConst(bool bool_const)
{
    BoolConst* be = new BoolConst(bool_const);
    boolexpr_allocated.push_back(be);
    return be;
}

BoolOp* BoolExprManager::makeBoolOp(BoolOp::BoolOpcode op, BoolExpr* Bool_expr1, BoolExpr* Bool_expr2)
{
    BoolOp* be = new BoolOp(op, Bool_expr1, Bool_expr2);
    boolexpr_allocated.push_back(be);
    return be;
}

NotOp* BoolExprManager::makeNotOp(BoolExpr* Bool_expr)
{
    NotOp* ne = new NotOp(Bool_expr);
    boolexpr_allocated.push_back(ne);
    return ne;

}

void BoolExprManager::clearMemoryBoolExpr()
{
    auto i = boolexpr_allocated.begin();
    for (; i != boolexpr_allocated.end(); i++) {
        delete (*i);
    }
    boolexpr_allocated.resize(0);
}

Block* BlockManager::makeBlock(std::vector<Statement*> stmt_vect)
{
    Block* B = new Block(stmt_vect);
    B_allocated.push_back(B);
    return B;
}

void BlockManager::clearMemoryBlock()
{
    auto i = B_allocated.begin();
    for (; i != B_allocated.end(); i++) {
        delete (*i);
    }
    B_allocated.resize(0);
}


