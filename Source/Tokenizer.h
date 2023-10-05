#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <fstream>

#include "Token.h"

//function object for tokenizing programs
class Tokenizer {
public:
	std::vector<Token> operator()(std::ifstream& inputFile) {
		std::vector<Token> inputTokens;
		tokenizeInputFile(inputFile, inputTokens);
		return inputTokens;
	}

private:
	//tokenizing and checking functions of the "components" of the character stream
	void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens);
	void tokenizeStringChar(std::string str, std::vector<Token>& inputTokens);
	void tokenizeStringNum(std::string str, std::vector<Token>& inputTokens);
	int tokenizeControl(char c, std::vector<Token>& inputTokens);
};

#endif