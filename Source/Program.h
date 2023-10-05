#ifndef PROGRAM_H
#define PROGRAM_H

#include "Block.h"
#include "Visitor.h"

class Block;   //forward declaration of class Block
class Visitor; //forward declaration of class Visitor

//concrete class for handling program
class Program {
public:
	Program(Block* bl) : stmt_block{ bl }  {}
	
	//access method
	Block* getBlock() {
		return stmt_block;
	}

	//pattern visitor
	void accept(Visitor* v) {
		v->visitProgram(this);
	}

private:
	Block* stmt_block;
};




#endif

