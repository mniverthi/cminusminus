#pragma ONCE
#ifndef PARSER
#define PARSER
#include <string>
#include <stack>
#include <iostream>
#include "lexer.hpp"
class Parser {
    private:
        Lexer* lexer;
        Token* curr;
        Token* peek;
        stack<Token*> seen;
    public:
        Parser(Lexer* lexer);
        void abort(string message);
        bool checkToken();
        bool checkPeek();
        void nextToken();
        void matchToken(TokenType desired);
};
#endif