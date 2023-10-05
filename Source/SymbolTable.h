#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <map>
#include <string>
#include <iostream>

#include "Exceptions.h"

//strucuture for handling the symbol table using std::map
struct SymbolTable {
	std::map <std::string, int64_t> variables;

	//method to add a variable to the symbol table
	void addVariable(const std::string& name, int64_t value) {
		variables[name] = value;
	}

	//access method
	int64_t getValue(const std::string& name) {
		return variables.at(name);
	}
	
	//method to check if the variable is in the table
	bool ThereIs(const std::string& name) {
		return variables.count(name) > 0;
	}
	
	//method to erase a variable from the table
	void erase(const std::string& name) {
		variables.erase(name);
	}

	//method to modify the value of a variable
	void setValue(const std::string& name, int64_t value){
		if (variables.count(name) > 0) variables[name] = value;
		else throw EvaluationError("Nessuna variabile " + name + " precedentemente definita ");
	}
};

#endif // !SYMBOLTABLE
