#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

//structure for handling errors during tokenizing
struct LexicalError : std::runtime_error {
	LexicalError(const char* msg) : std::runtime_error(msg) { }
	LexicalError(std::string msg) : std::runtime_error(msg.c_str()) { }
};

//structure for handling errors during parsing
struct ParseError : std::runtime_error {
	ParseError(const char* msg) : std::runtime_error(msg) { }
	ParseError(std::string msg) : std::runtime_error(msg.c_str()) { }
};

//structure for handling errors during evaluation
struct EvaluationError : std::runtime_error {
	EvaluationError(const char* msg) : std::runtime_error(msg) { }
	EvaluationError(std::string msg) : std::runtime_error(msg.c_str()) { }
};


#endif
