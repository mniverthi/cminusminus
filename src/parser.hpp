#pragma ONCE
#ifndef PARSER
#define PARSER
#include <string>
#include <stack>
#include <iostream>
#include "lexer.hpp"
class Parser {
    private:
        Lexer lexer;
        Token* curr;
        Token* peek;
        std::stack<Token*> seen;
    public:
        Parser(Lexer lexer);
        void abort(std::string message);
        bool checkToken();
        bool checkPeek();
        void nextToken();
        void matchToken();
};
#endif