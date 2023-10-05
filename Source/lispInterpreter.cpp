#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "Exceptions.h"
#include "Token.h"
#include "Tokenizer.h"
#include "NodeManager.h"
#include "Parser.h"
#include "Program.h"

constexpr auto DEBUG = 0;
constexpr auto VERBOSE = 0;

int main(int argc, char* argv[]) {
	//first error handling (unspecified file and problems when opening the file)
	if (argc < 2) {
		std::cerr << "(ERROR: Unspecified file!" << std::endl;
		std::cerr << "Help: use this syntax : " << argv[0] << " <file_name> ) " << std::endl;
		return EXIT_FAILURE;
	}
	std::ifstream inputFile;
	try {
		inputFile.open(argv[1]);
		if (!inputFile.is_open()) throw std::runtime_error("File not found!");
	}
	catch (std::exception& exc) {
		std::cerr << "(ERROR: I can not open " << argv[1]<<" ";
		std::cerr << exc.what() <<" )"<< std::endl;
		return EXIT_FAILURE;
	}
	
	//tokenizing stage
	Tokenizer tokenize;
	std::vector<Token> inputTokens;

	try {
		//If we are not sure that C++ optimize the return of the vector of tokens moving the content
		//instead of copying it, we can make explicit the use of the move constructor
		//using the primitive std::move
		inputTokens = std::move(tokenize(inputFile));
		inputFile.close();
	}
	catch (LexicalError& le) {
		//Catching errors during tokenizing
		std::cerr<<"(ERROR: ";
		std::cerr << "Lexical error: ";
		std::cerr << le.what();
		std::cerr <<" )" <<std::endl;
		return EXIT_FAILURE;
	}
	catch (std::exception& exc) {
		//Ciatching other generic errors
		std::cerr<<"(ERROR: ";
		std::cerr << "I can't read from: " << argv[1] << std::endl;
		std::cerr << exc.what();
		std::cerr <<" )" <<std::endl;
		return EXIT_FAILURE;
	}

	if (DEBUG){
		std::cout << "Tokens :" << std::endl;
		for (Token t : inputTokens) {
			std::cout << t << std::endl;
		}
	}
	
	//parsing stage

	//I create the manager for the nodes
	BlockManager manager;

	//I create the function object for parsing
	P_Parser parse{ manager };

	try {
		Program* program = parse(inputTokens);
		//Some instructions useful only for debug purpose
		if (DEBUG) {
			PrintVisitor* pv = new PrintVisitor();
			program->accept(pv);
		}
		if (DEBUG || VERBOSE) {
			std::cout << "Welcome to lispInterpreter by Federico Garau!" << std::endl;
			std::cout << "Execution of: " << argv[1] << std::endl;
		}
		//evaluation stage
		EvaluationVisitor* ev = new EvaluationVisitor();
		program->accept(ev);
		delete program;
	}
	catch (ParseError& pe) {
		//Catching errors during parsing
		std::cerr<<"(ERROR: ";
		std::cerr << "Parsing Error: ";
		std::cerr << pe.what();
		std::cerr <<" )" <<std::endl;
		return EXIT_FAILURE;
	}
	catch (EvaluationError& ee) {
		//Catching errors during evaluation
		std::cerr<<"(ERROR: ";
		std::cerr << "Evaluation error: ";
		std::cerr << ee.what();
		std::cerr <<" )" <<std::endl;
		return EXIT_FAILURE;
	}
	catch (std::exception& exc) {
		//Catching other generic exception
		std::cerr<<"(ERROR: ";
		std::cerr << "Generic error ";
		std::cerr << exc.what();
		std::cerr <<" )" <<std::endl;
		return EXIT_FAILURE;
	}
	if (VERBOSE || DEBUG) std::cout << "End of execution." << std::endl;
	
	return EXIT_SUCCESS;
  
}