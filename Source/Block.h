#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Statements.h"

//concrete class for handling blocks
class Block {
public:
	Block (std::vector<Statement*> stv) : stmt_vect {stv} {}
	void add_Statement(Statement* stmt) {
		stmt_vect.push_back(stmt);
	}
	//access method
	Statement* getStatementI(int i) {
		return stmt_vect[i];
	}
	//utility method that return the size of the vector
	int getSize() {
		return stmt_vect.size();
	}

	//pattern visitor
	void accept(Visitor* v);

private:
	std::vector <Statement*> stmt_vect;


};

#endif

