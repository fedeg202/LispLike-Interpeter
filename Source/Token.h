#ifndef TOKEN_H
#define TOKEN_H


//struct for tokens handling
struct Token {
	static constexpr int LP = 0; //(
	static constexpr int RP = 1; //)
	static constexpr int BLOCK = 2;
	static constexpr int SET = 3;
	static constexpr int PRINT = 4;
	static constexpr int INPUT = 5;
	static constexpr int IF = 6;
	static constexpr int WHILE = 7;
	static constexpr int ADD = 8;
	static constexpr int SUB = 9;
	static constexpr int MUL = 10;
	static constexpr int DIV = 11;
	static constexpr int NUM = 12;
	static constexpr int VID = 13;
	static constexpr int LT = 14;
	static constexpr int GT = 15;
	static constexpr int EQ = 16;
	static constexpr int AND = 17;
	static constexpr int OR = 18;
	static constexpr int NOT = 19;
	static constexpr int TRUE = 20;
	static constexpr int FALSE = 21;

	Token(int t, const char w) : tag{ t }, word { w } { }
	Token(int t, std::string w) : tag{ t }, word{ w } { }

	int tag;
	std::string word;

};

std::ostream& operator<<(std::ostream& os, const Token& t);

#endif