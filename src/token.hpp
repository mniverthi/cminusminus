#pragma ONCE
#ifndef TOKEN
#define TOKEN
#include <string>
class Token {
	private:
		std::string text;
		TokenType type;
	public:
		Token(TokenType which, std::string input) { }
		Token(TokenType which, char input) { }
		Token() { }
		TokenType getType() { }
		std::string getContent() { }
		void setType(TokenType which) { }
		void setContent(std::string input) { }
		void setContent(char input) { }
		bool isCharacter() { }
		bool isKeyword() { }
};
enum TokenType {
	ENDFILE = -1,
	NEWLINE = 0,
	NUMBER = 1,
	IDENT = 2,
	STRING = 3,
	// Keywords
	LABEL = 101,
	GOTO = 102,
	PRINT = 103,
	INPUT = 104,
	LET = 105,
	IF = 106,
	THEN = 107,
	ENDIF = 108,
	WHILE = 109,
	REPEAT = 110,
	ENDWHILE = 111,
	// Operators
	EQ = 201,
	PLUS = 202,
	MINUS = 203,
	ASTERISK = 204,
	SLASH = 205,
	EQEQ = 206,
	NOTEQ = 207,
	LT = 208,
	LTEQ = 209,
	GT = 210,
	GTEQ = 211
};

#endif