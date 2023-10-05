#include <iostream>
#include <sstream>

#include "Visitor.h"
#include "Statements.h"
#include "Program.h"


void PrintVisitor::visitNumber(Number* num)
{
	std::cout << num->get_Value();
}

void PrintVisitor::visitOperator(Operator* op)
{
	std::cout << "(";
	std::cout << op->Opcode_to_string()<<" ";
	op->getNumExpr1()->accept(this);
	std::cout << " ";
	op->getNumExpr2()->accept(this);
	std::cout << " )";
}

void PrintVisitor::visitVariable(Variable* var)
{
	std::cout << var->getVariableId();
}



void PrintVisitor::visitProgram(Program* prog)
{
	std::cout << "Start of the program!" << std::endl;
	prog->getBlock()->accept(this);
}

void PrintVisitor::visitBlockStmt(Block* block)
{
	if (block->getSize() == 1) {
		block->getStatementI(0)->accept(this);
	}
	else {
		std::cout << "(BLOCK ";
		for (int i = 0; i < block->getSize(); i++) {
			block->getStatementI(i)->accept(this);
		}
		std::cout << ")"<<std::endl;
	}
}

void PrintVisitor::visitPrintStmt(PrintStmt* p_stmt)
{
	std::cout << "(PRINT ";
	p_stmt->getNumExpr()->accept(this);
	std::cout << ")"<<std::endl;
}

void PrintVisitor::visitSetStmt(SetStmt* s_stmt)
{
	std::cout << "(SET ";
	s_stmt->getVar()->accept(this);
	std::cout << " ";
	s_stmt->getNumExpr()->accept(this);
	std::cout << ")" << std::endl;
}

void PrintVisitor::visitInputStmt(InputStmt* in_stmt)
{
	std::cout << "(INPUT ";
	in_stmt->getVar()->accept(this);
	std::cout << ")" << std::endl;
}

void PrintVisitor::visitWhileStmt(WhileStmt* w_stmt)
{
	std::cout << "(WHILE ";
	w_stmt->getBoolExpr()->accept(this);
	std::cout << " ";
	w_stmt->getBlock()->accept(this);
	std::cout << ")" << std::endl;
}

void PrintVisitor::visitIfStmt(IfStmt* if_stmt)
{
	std::cout << "(IF ";
	if_stmt->getBoolExpr()->accept(this);
	std::cout << " ";
	if_stmt->getBlock1()->accept(this);
	std::cout << " ";
	if_stmt->getBlock2()->accept(this);
	std::cout << ")" << std::endl;
}

void PrintVisitor::visitRelOp(RelOp* rop)
{
	std::cout << "(" << rop->RelOpcode_to_string() <<" ";
	rop->getNumExpr1()->accept(this);

}

void PrintVisitor::visitBoolOp(BoolOp* bop)
{
	std::cout << "(" << bop->BoolOpcode_to_string();
	std::cout << " ";
	bop->getBoolExpr1()->accept(this);
	std::cout << " ";
	bop->getBoolExpr2()->accept(this);
	std::cout << ")";

}

void PrintVisitor::visitNotOp(NotOp* nop)
{
	std::cout << "(NOT ";
	nop->getBoolExpr()->accept(this);
	std::cout << ")";
}


void PrintVisitor::visitBoolConst(BoolConst* bc)
{
	std::cout<<std::to_string(bc->getBoolConst());
}

void EvaluationVisitor::visitProgram(Program* prog)
{
	prog->getBlock()->accept(this);
}

void EvaluationVisitor::visitBlockStmt(Block* block)
{
	for (int i = 0; i < block->getSize(); i++) {
		block->getStatementI(i)->accept(this);
	}
}

void EvaluationVisitor::visitPrintStmt(PrintStmt* p_stmt)
{
	p_stmt->getNumExpr()->accept(this);
	std::cout << accumulatorInt.back() << std::endl;
	accumulatorInt.pop_back();
}

void EvaluationVisitor::visitSetStmt(SetStmt* s_stmt)
{
	s_stmt->getNumExpr()->accept(this);
	ST.addVariable(s_stmt->getVar()->getVariableId(), accumulatorInt.back());
	accumulatorInt.pop_back();
}

void EvaluationVisitor::visitInputStmt(InputStmt* in_stmt)
{
	std::string s_tmp;
	if (std::cin >> s_tmp) {
		std::stringstream ss_tmp(s_tmp);
		char c = ss_tmp.get();
		int64_t tmp;
		//input number must be an integer, can't have a digit after 0
		if (c == '0') {
			//check that it doesn't have a digit after 0
			c = ss_tmp.get();
			if (c != 0) {
				throw EvaluationError("A number can not start with 0");
			}
			else tmp = 0;
		}
		else if (std::isdigit(c)){
			//check if is an integer
			while(!ss_tmp.eof()){
				if (std::isdigit(c)) c = ss_tmp.get();
				else throw EvaluationError("This is not a positive or negative integer number");
			}
			try {
				//std::stoll() generate an exception if the number is too big
				tmp = std::stoll(s_tmp);
			}
			catch (std::exception& exc) {
				throw EvaluationError("This number is too big");
			}
		}
		else if (c == '-') {
			//ckeck that actually is an negative integer
			c = ss_tmp.get();
			if (c != 0) {
				while (!ss_tmp.eof()) {
					if (std::isdigit(c)) c = ss_tmp.get();
					else throw EvaluationError("This is not a positive or negative integer number");
				}
			}
			else throw EvaluationError("This is not a positive or negative integer number");
			try {
				tmp = std::stoll(s_tmp);
			}
			catch (std::exception& exc) {
				throw EvaluationError("This number is too big");
			}
		}
		else throw EvaluationError("This is not a positive or negative integer number");
		ST.addVariable(in_stmt->getVar()->getVariableId(), tmp);
	}
	else throw EvaluationError("Errore durante l'inserimento");
}

void EvaluationVisitor::visitWhileStmt(WhileStmt* w_stmt)
{
	w_stmt->getBoolExpr()->accept(this);
	
	while (accumulatorBool.back()) {
		accumulatorBool.pop_back();
		w_stmt->getBlock()->accept(this);
		w_stmt->getBoolExpr()->accept(this);
	}
	accumulatorBool.pop_back();
}

void EvaluationVisitor::visitIfStmt(IfStmt* if_stmt)
{
	if_stmt->getBoolExpr()->accept(this);
	if (accumulatorBool.back()) if_stmt->getBlock1()->accept(this);
	else if_stmt->getBlock2()->accept(this);
	accumulatorBool.pop_back();
}

void EvaluationVisitor::visitNumber(Number* num)
{
	accumulatorInt.push_back(num->get_Value());
}

void EvaluationVisitor::visitOperator(Operator* op)
{
	op->getNumExpr2()->accept(this);
	op->getNumExpr1()->accept(this);

	int64_t val1 = accumulatorInt.back();
	accumulatorInt.pop_back();
	int64_t val2 = accumulatorInt.back();
	accumulatorInt.pop_back();
	switch (op->getOpcode()) {
	case Operator::ADD:
		accumulatorInt.push_back(val1 + val2);
		break;
	case Operator::SUB:
		accumulatorInt.push_back(val1 - val2);
		break;
	case Operator::MUL:
		accumulatorInt.push_back(val1 * val2);
		break;
	case Operator::DIV:
		if (val2 == 0) throw EvaluationError("Divison by 0.");
		accumulatorInt.push_back(val1 / val2);
		break;
	default:
		break;
	
	}
}

void EvaluationVisitor::visitVariable(Variable* var)
{
	if (ST.ThereIs(var->getVariableId())) {
		accumulatorInt.push_back(ST.getValue(var->getVariableId()));
	}
	else throw EvaluationError("Variable " + var->getVariableId() + " not defined");
}

void EvaluationVisitor::visitRelOp(RelOp* rop)
{
	rop->getNumExpr2()->accept(this);
	rop->getNumExpr1()->accept(this);

	int64_t val1 = accumulatorInt.back();
	accumulatorInt.pop_back();
	int64_t val2 = accumulatorInt.back();
	accumulatorInt.pop_back();

	switch (rop->getRelOpcode())
	{
	case RelOp::LT:
		accumulatorBool.push_back(val1 < val2);
		break;
	case RelOp::GT:
		accumulatorBool.push_back(val1 > val2);
		break;
	case RelOp::EQ:
		accumulatorBool.push_back(val1 == val2);
		break;
	default:
		break;
	}
}

void EvaluationVisitor::visitBoolOp(BoolOp* bop)
{
	bop->getBoolExpr1()->accept(this);

	bool boolval1 = accumulatorBool.back();
	accumulatorBool.pop_back();

	bool boolval2;
	

	switch (bop->getBoolOpcode())
	{
	case BoolOp::AND:
		if (!boolval1) accumulatorBool.push_back(false);
		else {
			bop->getBoolExpr2()->accept(this);
			boolval2 = accumulatorBool.back(); accumulatorBool.pop_back();
			accumulatorBool.push_back(boolval1 && boolval2);
		}
		break;
	case BoolOp::OR:
		if (boolval1) accumulatorBool.push_back(true);
		else {
			bop->getBoolExpr2()->accept(this);
			boolval2 = accumulatorBool.back(); accumulatorBool.pop_back();
			accumulatorBool.push_back(boolval1 || boolval2);
		}
		break;
	default:
		break;
	}
}

void EvaluationVisitor::visitNotOp(NotOp* nop)
{
	nop->getBoolExpr()->accept(this);
	bool val = accumulatorBool.back();
	accumulatorBool.pop_back();
	accumulatorBool.push_back(!val);
}

void EvaluationVisitor::visitBoolConst(BoolConst* bc)
{
	accumulatorBool.push_back(bc->getBoolConst());
}
