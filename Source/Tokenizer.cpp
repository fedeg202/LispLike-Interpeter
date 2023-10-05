#include <string>
#include <sstream>
#include <iostream>

#include "Tokenizer.h"
#include "Exceptions.h"
#include "Token.h"

void Tokenizer::tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens) {

	char ch;
	ch = inputFile.get();
	int control = 0;
	while (!inputFile.eof()) {

		if (tokenizeControl(ch, inputTokens) == 0) {
			//if there is an empty space i proceed, if there is a parenthesis i create the token and proceed
			ch = inputFile.get();
		}
		else if (std::isdigit(ch)) {
			//if is a number, it can only be a NUM token, can only finish with a empty space or a parenthesis, it can't have a letter in it
			std::stringstream tmp{};
			while (std::isdigit(ch)) {
				tmp << ch;
				ch = inputFile.get();
			}
			tokenizeStringNum(tmp.str(), inputTokens);
			control = tokenizeControl(ch, inputTokens);
			if (control == 0) ch = inputFile.get();
			else if (control == -1) throw LexicalError("Error on character: " + ch);
		}

		else if (tokenizeControl(ch, inputTokens) == 2) {
			//if it has "-" must be a NUM token, and so it can not have something different from a digit after "-"
			ch = inputFile.get();
			if (tokenizeControl(ch, inputTokens) != 1) throw LexicalError("Error on character: " + ch);
			else {
				std::stringstream tmp{};
				tmp << "-";
				while (std::isdigit(ch)) {
					tmp << ch;
					ch = inputFile.get();
				}
				tokenizeStringNum(tmp.str(), inputTokens);
				control = tokenizeControl(ch, inputTokens);
				if (control == 0) ch = inputFile.get();
				else if (control == -1) {
					std::stringstream tmp;
					tmp << "Error on character: " << ch;
					throw LexicalError(tmp.str());
				}
				
			}
		}

		else if (std::isalpha(ch)) {
			//if it is a word, it can not have a digit in it
			std::stringstream tmp{};
			while (std::isalpha(ch)) {
				tmp << ch;
				ch = inputFile.get();
			}
			tokenizeStringChar(tmp.str(), inputTokens);
			control = tokenizeControl(ch, inputTokens);
			if (control == 0) ch = inputFile.get();
			else if (control == 1) {
				std::stringstream tmp;
				tmp << "Error on character: " << ch;
				throw LexicalError(tmp.str());
			}
		}

		
		
	
	}
}

//tokenizing a string, i check what tokens match the string
void Tokenizer::tokenizeStringChar(std::string str, std::vector<Token>& inputTokens)
{
	if (str == "BLOCK")       inputTokens.push_back(Token{ Token::BLOCK,str });
	else if (str == "SET")    inputTokens.push_back(Token{ Token::SET,str });
	else if (str == "PRINT")  inputTokens.push_back(Token{ Token::PRINT,str });
	else if (str == "INPUT")  inputTokens.push_back(Token{ Token::INPUT,str });
	else if (str == "IF")     inputTokens.push_back(Token{ Token::IF,str });
	else if (str == "WHILE")  inputTokens.push_back(Token{ Token::WHILE,str });
	else if (str == "ADD")    inputTokens.push_back(Token{ Token::ADD,str });
	else if (str == "SUB")    inputTokens.push_back(Token{ Token::SUB,str });
	else if (str == "MUL")    inputTokens.push_back(Token{ Token::MUL,str });
	else if (str == "DIV")    inputTokens.push_back(Token{ Token::DIV,str });
	else if (str == "LT")     inputTokens.push_back(Token{ Token::LT,str });
	else if (str == "GT")     inputTokens.push_back(Token{ Token::GT,str });
	else if (str == "EQ")     inputTokens.push_back(Token{ Token::EQ,str });
	else if (str == "AND")    inputTokens.push_back(Token{ Token::AND,str });
	else if (str == "OR")     inputTokens.push_back(Token{ Token::OR,str });
	else if (str == "NOT")    inputTokens.push_back(Token{ Token::NOT,str });
	else if (str == "TRUE")   inputTokens.push_back(Token{ Token::TRUE,str });
	else if (str == "FALSE")  inputTokens.push_back(Token{ Token::FALSE,str });
	else inputTokens.push_back(Token{ Token::VID, str });

}

//funzione di tokenizzazione per una stringa di numeri
void Tokenizer::tokenizeStringNum(std::string str, std::vector<Token>& inputTokens)
{
	inputTokens.push_back(Token{ Token::NUM,str });
}

//funzione di controllo di caratteri durante la tokenizzazione e di creazione di token ')' e '('
//restituisce un numero diverso da 0 se gli viene passato qualcosa che non � una parentesi tonda o uno spazio o la fine dello stream
//restituisce -1 se il carattere � una lettera dell'alfabeto
//restituisce 1 se il carattere � un numero
//restituisce 2 se il carattere � '-'
//restituisce -2 se il carattere non appartiene al linguaggio
//crea un errore lessicale se non � nessuna di queste e quindi non fa parte dei simboli terminali della grammatica
int Tokenizer::tokenizeControl(char c, std::vector<Token>& inputTokens)
{
	if (std::isalpha(c)) {
		return -1;
	}
	else if (std::isdigit(c)) {
		return 1;
	}
	else if (c == '-') {
		return 2;
	}
	else if (std::isspace(c)) return 0;
	else if (c == '(') {
		inputTokens.push_back(Token{ Token::LP,c });
		return 0;
	}
	else if (c == ')') {
		inputTokens.push_back(Token{ Token::RP,c });
		return 0;
	}
	else {
		std::stringstream tmp;
		tmp << "Error on character: " << c;
		throw LexicalError(tmp.str());
		return -2;
	}
}

