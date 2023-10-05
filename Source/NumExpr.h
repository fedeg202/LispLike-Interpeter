#ifndef NUMEXPR_H
#define NUMEXPR_H

#include <string>

class Visitor; //Forward declaration of class Visitor


//abstract class for handling the numeric expressions
class NumExpr {
public:
	virtual ~NumExpr() {};
	virtual void accept(Visitor* v) = 0;

};

//concrete class for handling numbers
class Number : public NumExpr {
public:
	Number(int64_t v) : value{ v } { }
	~Number() = default;

	Number(const Number& other) = default;
	Number& operator=(const Number& other) = default;

	int64_t get_Value() const {
		return value;
	}
	//pattern visitor
	void accept(Visitor* v) override;

private:
	int64_t value;
};

//concrete class for handling variables
class Variable : public NumExpr {
public:
	Variable(std::string v_id) : variable_id{ v_id } {};
	//access method
	std::string getVariableId() {
		return variable_id;
	}
	//pattern visitor
	void accept(Visitor* v) override;

private:
	std::string variable_id;
};

//concrete class for handling numeric operators
class Operator : public NumExpr {
public:
	enum Opcode { ADD, SUB, MUL, DIV };
	Operator(Opcode op, NumExpr* ne1, NumExpr* ne2) : op{ op }, num_expr1{ne1}, num_expr2{ne2} {}

	//access methods
	NumExpr* getNumExpr1() {
		return num_expr1;
	}
	NumExpr* getNumExpr2() {
		return num_expr2;
	}
	Opcode getOpcode() {
		return op;
	}

	//utility method to convert the operation code to a string, useful for terminal printing the program and debug
	std::string Opcode_to_string();
	//pattern visitor
	void accept(Visitor* v) override;

private:
	Opcode op;
	NumExpr* num_expr1;
	NumExpr* num_expr2;
};

#endif