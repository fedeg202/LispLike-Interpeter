#include "BoolExpr.h"

std::string RelOp::RelOpcode_to_string()
{
	std::string tmp;
	switch (op)
	{
	case RelOp::LT:
		tmp = "LT";
		break;
	case RelOp::GT:
		tmp = "GT";
		break;
	case RelOp::EQ:
		tmp = "EQ";
		break;
	default:
		break;
	}
	return tmp;
}

void RelOp::accept(Visitor* v)
{
	v->visitRelOp(this);
}

std::string BoolOp::BoolOpcode_to_string()
{
	std::string tmp;
	switch (op)
	{
	case BoolOp::AND:
		tmp = "AND";
		break;
	case BoolOp::OR:
		tmp = "OR";
		break;
	default:
		break;
	}
	return tmp;
}

void BoolOp::accept(Visitor* v)
{
	
	v->visitBoolOp(this);
}

std::string BoolConst::BoolConst_to_string()
{
	std::string tmp;
	if (bool_const) tmp = "TRUE";
	else tmp = "FALSE";
	return tmp;
}

void BoolConst::accept(Visitor* v)
{
	v->visitBoolConst(this);
}

void NotOp::accept(Visitor* v)
{
	v->visitNotOp(this);
}


