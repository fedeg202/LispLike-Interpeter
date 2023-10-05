
#ifndef BOOLEXPR_H
#define BOOLEXPR_H

#include "Visitor.h"
#include "NumExpr.h"

//abstract class for handling the boolean expression
class BoolExpr {
public:
	virtual ~BoolExpr() {};
	virtual void accept(Visitor* v) = 0;
};

//concrete class for handling the relational operators
class RelOp : public BoolExpr {
public:
	enum RelOpcode {LT,GT,EQ};
	RelOp(RelOpcode op, NumExpr* ne1, NumExpr* ne2) : op{ op }, num_expr1{ ne1 }, num_expr2{ ne2 } {}
	//access methods
	NumExpr* getNumExpr1() {
		return num_expr1;
	}
	NumExpr* getNumExpr2() {
		return num_expr2;
	}
	RelOpcode getRelOpcode() {
		return op;
	}

	//utility method to convert the operator code to a string, useful for debugging and printing the program
	std::string RelOpcode_to_string();

	//pattern visitor
	void accept(Visitor* v) override;

private:
	RelOpcode op;
	NumExpr* num_expr1;
	NumExpr* num_expr2;
};

//concrete class for handling the boolean operators
class BoolOp : public BoolExpr {
public:
	enum BoolOpcode {AND, OR};
	BoolOp(BoolOpcode op, BoolExpr* be1, BoolExpr* be2) : op{op}, Bool_expr1{be1}, Bool_expr2{be2} {}

	BoolExpr* getBoolExpr1() {
		return Bool_expr1;
	}
	BoolExpr* getBoolExpr2() {
		return Bool_expr2;
	}
	BoolOpcode getBoolOpcode() {
		return op;
	}

	//utility method to convert the operator code to a string, useful for debugging and printing the code
	std::string BoolOpcode_to_string();

	//pattern visitor
	void accept(Visitor* v) override;

private:
	BoolOpcode op;
	BoolExpr* Bool_expr1;
	BoolExpr* Bool_expr2;

 };

//concrete class for handling the boolean operator NOT
class NotOp : public BoolExpr {
public:
	NotOp(BoolExpr* b_expr) : bool_expr{ b_expr } {}
	 
	//access method
	BoolExpr* getBoolExpr() {
		return bool_expr;
	}

	//pattern visitor
	void accept(Visitor* v) override;

private:
	BoolExpr* bool_expr;
};

//concrete class for handling the bool constant
class BoolConst : public BoolExpr {
public:
	BoolConst(bool bc) : bool_const{bc} {}

	//access method
	bool getBoolConst() {
		return bool_const;
	}

	//utlity method to convert the bool constant to a string, useful for debugging and printing the porgram
	std::string BoolConst_to_string();

	//pattern visitor
	void accept(Visitor* v) override;
	
private:
	bool bool_const;
};
#endif // !BOOLEXPR_H
