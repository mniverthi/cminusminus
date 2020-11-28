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
        int current_linepos;
        int current_line;
        std::stack<Token*> seen;
    public:
        Parser(Lexer lexer);
        void abort(std::string message);
        bool checkToken();
        bool checkPeek();
};
#endif