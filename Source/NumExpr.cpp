#include "NumExpr.h"

#include "Visitor.h"

void Number::accept(Visitor* v)
{
	v->visitNumber(this);
}

void Variable::accept(Visitor* v)
{
	v->visitVariable(this);
}

std::string Operator::Opcode_to_string()
{
	std::string tmp;
	switch (op)
	{
	case Operator::ADD:
		tmp = "ADD";
		break;
	case Operator::SUB:
		tmp = "SUB";
		break;
	case Operator::MUL:
		tmp = "MUL";
		break;
	case Operator::DIV:
		tmp = "DIV";
		break;
	default:
		
		break;
	}
	return tmp;

}

void Operator::accept(Visitor* v)
{
	v->visitOperator(this);
}

