#ifndef PARSER_H
#define PARSER_H



#include "Program.h"
#include "NodeManager.h"
#include "Exceptions.h"

struct Token; //forward declaration of struct token


//Function object for program parsing
class P_Parser {
public:
	P_Parser(BlockManager& manager) : Bm{ manager } {};
	void safe_next(std::vector<Token>::const_iterator& itr) {
		if (itr == streamEnd) {
			throw ParseError("Unexpected end of input");
		}
		++itr;
	}

	
	//parsing function of the program
	Program* operator()(const std::vector<Token>& tokenStream);
private:
	BlockManager& Bm;
	std::vector<Token>::const_iterator streamEnd;
	//parsing function for the "components" of the program
	Block* Block_Parser(std::vector<Token>::const_iterator& Itr);
	NumExpr* NExpr_Parser(std::vector<Token>::const_iterator& Itr);
	Statement* S_Parser(std::vector<Token>::const_iterator& Itr);
	BoolExpr* BExpr_Parser(std::vector<Token>::const_iterator& Itr);

};


#endif // !PARSER_H

